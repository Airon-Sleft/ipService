#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include <utils.h>

class GeoBase
{
public:
    GeoBase();
    bool LoadBase(const std::string& pathToFile);
    std::string GetCountry(const std::string& ip) const;
private:
    struct IPRow
    {
        uint64_t start_;
        uint64_t end_;
        std::string country_;
        bool IsInRange(const uint64_t value) const
        {
            return value >= start_ && value <= end_;
        }
    };
    struct IPNode
    {
        std::unordered_map<int, IPNode> linkToNode_;
        std::vector<IPRow> listRow_;
    };
    struct IPData
    {
        // std::string stringParts[4];
        u_int8_t intParts[4];
    };
    union IP {
        unsigned int ip;
        struct {
        unsigned char d;
        unsigned char c;
        unsigned char b;
        unsigned char a;
        } ip2;
    };
    IPNode ipStorage_;
    void ClearRow(std::string& row, const char* delimiter);
    uint64_t ConvertIPToNumber(const std::string& ip) const;
    uint64_t ConvertIPToNumber(const IPData& ip) const;
    IPData ParseIP(const std::string& ip) const;
    bool LoadBaseFastNoSafety(const std::string& pathToFile);
    bool LoadBaseSlowSafety(const std::string& pathToFile);
    void PutToStorage(const IPRow& ipRow);
    uint64_t CharToUInt(const char* chararray, int charSize) const ;
};