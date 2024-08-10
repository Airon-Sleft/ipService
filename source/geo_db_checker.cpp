#include <geo_db_checker.h>
#include <filesystem>

GeoDBChecker::GeoDBChecker(const Logger *logger) : _logger(logger) , _downloader(logger) , _unpacker(logger)
{
}

bool GeoDBChecker::Start(u_int16_t timeOutInMiliseconds)
{
    if (!DoesHaveDBFile() || !IsDBFileActual())
    {
        if (!DownloadDBFile(timeOutInMiliseconds)) return false;
    }
    return true;
}

bool GeoDBChecker::DoesHaveDBFile() const
{
    return std::filesystem::exists(_fileFullPath);
}

bool GeoDBChecker::IsDBFileActual() const
{
    using namespace std;
    filesystem::file_time_type ftime = filesystem::last_write_time(_fileFullPath);
    const auto toNow = filesystem::file_time_type::clock::now() - ftime;
    const auto elapsedHours = chrono::duration_cast<chrono::hours>(toNow).count();
    return elapsedHours/24 < _dayToUpdateDBFile;
}

bool GeoDBChecker::DownloadDBFile(u_int32_t timeOutInMiliseconds)
{
    const std::string tempArchiveName{"archive.zip"};
    if(!std::filesystem::exists(_fileDirectory)) 
    {
        std::filesystem::create_directory(_fileDirectory);
    }
    if (!_downloader.Load(_urlPath, _fileDirectory + tempArchiveName, timeOutInMiliseconds)) return false;
    _unpacker.Do(tempArchiveName, _fileNameInArchive, _fileDirectory);
    std::filesystem::remove(_fileDirectory + tempArchiveName);
    return false;
}
