#include "geoBase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>

void CustomSplit(const char* sourceString, std::size_t stringSize, std::string* outString, const char delimiter)
{
    int startIndex = 0;
    char temp[256];
    memset(temp, '\0', sizeof(temp));
    for (int i = 0; i < stringSize; i++)
    {
        if (sourceString[i] == delimiter || i+1 == stringSize)
        {
            outString->assign(temp+1, temp+(i-startIndex-1));
            // std::cout << *outString << ' ';
            outString++;
            // memset(temp, '\0', sizeof(temp));
            startIndex = i+1;
        }
        else if(sourceString[i] != '\t' && sourceString[i] != '"' && sourceString[i] != '\r')
        {
            temp[i-startIndex] = sourceString[i];
            // outString->push_back(sourceString[i]);
        }
    }
    // std::cout << std::endl;
}

GeoBase::GeoBase()
{
}

bool GeoBase::LoadBase(const std::string& pathToFile)
{
    return LoadBaseFastNoSafety(pathToFile); // ~30% faster than slow method, but its not safety (i could made mistakes)
    // return LoadBaseSlowSafety(pathToFile);
}

bool GeoBase::LoadBaseFastNoSafety(const std::string &pathToFile)
{
    using namespace std;
    ifstream baseFile(pathToFile);
    if (baseFile.is_open())
    {
        const int charArraySize = 2048;
        char oneCharRow[charArraySize];
        memset(oneCharRow, 0, sizeof(oneCharRow));
        while(baseFile.getline(oneCharRow, charArraySize))
        {
            int size = 0;
            for (int i = 0; i < charArraySize; i++)
            {
                if (oneCharRow[i] == '\r')
                {
                    size = i;
                    break;
                }
            }
            const int partsCount = 5;
            string parts[partsCount];
            CustomSplit(oneCharRow, size, parts, ',');
            IPRow ipRow{stoull(parts[0]), stoull(parts[1]), parts[2]};
            PutToStorage(ipRow);

            memset(oneCharRow, 0, sizeof(oneCharRow));
        }
        baseFile.close();
        return true;
    }
    return false;
}

bool GeoBase::LoadBaseSlowSafety(const std::string &pathToFile)
{
    using namespace std;
    ifstream baseFile(pathToFile);
    if (baseFile.is_open())
    {
        std::string oneRow;
        while(getline(baseFile, oneRow))
        {
            ClearRow(oneRow, "\r");
            const int partsCount = 4;
            stringstream streamString(oneRow);
            string parts[partsCount];
            for (int i =0; i < partsCount; ++i)
            {
                getline(streamString, parts[i], ',');
                ClearRow(parts[i], "\"");
            }           
            IPRow ipRow{stoull(parts[0]), stoull(parts[1]), parts[2]};
            PutToStorage(ipRow);
            /*
                [0] - start Range
                [1] = end Range
                [2] - country Name 
            */
        }
        baseFile.close();
        return true;
    }
    return false;
}

void GeoBase::PutToStorage(const IPRow &ipRow)
{
    IP ipParsed{(unsigned int)ipRow.start_};
    // int value = floor((double)ipRow.start_/0x1000000);
    std::unordered_map<int, GeoBase::IPNode>::iterator nodeIterator;
    IPNode* ipCurrentNode = &ipStorage_;
    nodeIterator = ipStorage_.linkToNode_.find(ipParsed.ip2.a);
    if (nodeIterator == ipStorage_.linkToNode_.end())
    {
        IPNode ipNode;
        ipStorage_.linkToNode_.insert({ipParsed.ip2.a, std::move(ipNode)});
        nodeIterator = ipStorage_.linkToNode_.find(ipParsed.ip2.a);
        nodeIterator->second.listRow_.reserve(1000);
    }                
    nodeIterator->second.listRow_.push_back(std::move(ipRow));
}

std::string GeoBase::GetCountry(const std::string& ip) const
{
    using namespace std;

    IPData ipData = ParseIP(ip);
    uint64_t ipNumber = ConvertIPToNumber(ipData);
    // uint64_t ipNumber = ConvertIPToNumber(ip);
    // unsigned int ipCopy = static_cast<unsigned int>(ipNumber);
    // unsigned int parts[4] = {
    //     (unsigned int)ipNumber >> 24 & 0xFF,
    //     (unsigned int)ipNumber >> 16 & 0xFF,
    //     (unsigned int)ipNumber >> 8  & 0xFF,
    //     (unsigned int)ipNumber & 0xFF,
    // };

    // IP ipParsed{(unsigned int)ipNumber};

    auto it = ipStorage_.linkToNode_.find(ipData.intParts[0]);
    if (it != ipStorage_.linkToNode_.end())
    {
        const auto& listRow = it->second.listRow_;
        for (const IPRow& ipRow : listRow)
        {
            if (ipRow.IsInRange(ipNumber))
            {
                return ipRow.country_;
            }            
        }
    }
    return "-";
}

void GeoBase::ClearRow(std::string& row, const char* delimiter)
{
    using namespace std;
    size_t position = row.find(delimiter);    
    while (position != std::string::npos)
    {
        row.erase(position, 1);
        position = row.find(delimiter);    
    }
}

uint64_t GeoBase::ConvertIPToNumber(const std::string &ip) const
{
    const IPData ipData = ParseIP(ip);
    return ConvertIPToNumber(ipData);
}

uint64_t GeoBase::ConvertIPToNumber(const IPData& ipData) const
{
    return (uint64_t)ipData.intParts[0] * 16777216 + (uint64_t)ipData.intParts[1] * 65536 + (u_int64_t)ipData.intParts[2] * 256 + ipData.intParts[3];
}

GeoBase::IPData GeoBase::ParseIP(const std::string &ip) const
{
    IPData ipData{}; // required null initialization to aviod error when ip isnt correct
    int ind = 0;
    char part[3];
    char charIndex = 0;
    for (int i = 0; i <= ip.size(); i++)
    {
        if(i == ip.size() || ip[i] == '.')
        {
            // ipData.intParts[ind] = stoull(ipData.stringParts[ind]);
            ipData.intParts[ind] = CharToUInt(part, charIndex);
            ind++;
            charIndex = 0;
        }
        else
        {
            if (charIndex > 2) break;
            part[charIndex] = ip[i];
            charIndex++;
            // ipData.stringParts[ind].push_back(ip[i]);
        }
    }   

    return ipData;
}

uint64_t GeoBase::CharToUInt(const char *chararray, int charSize) const
{
    uint64_t res = 0;
    for (int i =0; i < charSize; i++)
    {
        res = res*10 + (chararray[i] - '0');
    }
    return res;
}