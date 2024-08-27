#pragma once
#include <string>
#include <map>

class Configuration {
private:
    static Configuration* _instance;    
    std::string _downloadURL;
    std::string _dBFileNameInArchive;
    Configuration();
    bool SetData(const std::map<std::string, std::string>& valuesList, const std::string& key, std::string* dataToSet);
public:
    Configuration(const Configuration& obj) = delete; 
    static Configuration* getInstance();
    void PutData(const std::map<std::string, std::string>& valuesList);
};