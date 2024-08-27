#include <configuration.h>
#include <stdexcept>
Configuration* Configuration::_instance = nullptr;
Configuration::Configuration()
{

}

Configuration *Configuration::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Configuration();
    }
    return _instance;
}

void Configuration::PutData(const std::map<std::string, std::string>& valuesList)
{
    if (!SetData(valuesList, "DownloadURL", &_downloadURL)) throw std::invalid_argument("Configuration file has no DownloadURL");
    if (!SetData(valuesList, "FileNameInArchive", &_dBFileNameInArchive)) throw std::invalid_argument("Configuration file has no FileNameInArchive");
}

bool Configuration::SetData(const std::map<std::string, std::string>& valuesList, const std::string& key, std::string* dataToSet)
{
    auto value = valuesList.find(key);
    if (value == valuesList.end()) return false;
    *dataToSet = value->second;
    return true;
}
