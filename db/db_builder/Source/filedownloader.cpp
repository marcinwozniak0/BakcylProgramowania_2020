#include "filedownloader.h"

using namespace fd;
namespace fs = std::filesystem;

FileDownloader::FileDownloader()
{ 
    curl = curl_easy_init();
}

bool FileDownloader::isFileDownloaded(std::string fileName_)
{  
    std::string c = directoryPath + "/" + fileName_;
    std::ifstream ifexfile(c.c_str()); 
    if(ifexfile)
    {
        std::string msg = fileName_ + " already exists!";
        std::cout<<msg<<std::endl;
        
        return true;        
    }
    else 
    {
        return false;
    }
}

void FileDownloader::addDirectoryPath(std::string directoryPath_)
{
    directoryPath = directoryPath_;
}

void FileDownloader::createDirectory(std::string directoryPath_)
{
    directoryPath = directoryPath_;
    
    if(fs::exists(directoryPath))
    {
        //printf("Directory already exists! \n");
    }
    else 
    {
        fs::create_directory(directoryPath);
    }
}

void FileDownloader::addLinks(std::vector <std::string> links_, std::vector <std::string> fileNames_)
{
    links = links_;
    fileNames = fileNames_;
    
    for(unsigned int i = 0; i < fileNames.size(); i++)
    {
        std::string newName = fileNames[i];
        newName.erase(newName.end() - 4, newName.end());
        std::string statusFileName = newName + ".txt";
        statusFileNames.push_back(statusFileName);
    }
}

void FileDownloader::download(int i)
{   
    CURLcode res;

    std::string msg = "Downloading " + fileNames[i] + ", please be patient";
    std::cout<<msg<<std::endl;
    
    //some curl setup     
    fp = fopen(fileNames[i].c_str(), "wb");
    
    curl_easy_setopt(curl, CURLOPT_URL, links[i].c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    
    res = curl_easy_perform(curl);
    
    //checking if everything went well
    if(res == CURLE_OK)
    {
        std::string msg = "Succes! " + fileNames[i] + " downloaded";
        std::cout<<msg<<std::endl;
    }   
    else 
    {
        std::cout<<curl_easy_strerror(res)<<std::endl;
    }
    
    //moving downloaded file to folder created with folderPath 
    std::string newPath = directoryPath + "/" + fileNames[i];
    if(rename(fileNames[i].c_str(), newPath.c_str()) < 0)
    {
        printf("ERROR! There's probly no directory 'data'. \n");
    } 
        
    fclose(fp);
    curl_easy_cleanup(curl);
}

void FileDownloader::createFileForChecking(int i)
{
    std::ofstream statusFile(statusFileNames[i]);
    statusFile << ".";
    statusFile.close();
    
    std::string newPath = directoryPath + "/" + statusFileNames[i];
    if(rename(statusFileNames[i].c_str(), newPath.c_str()) < 0)
    {
        printf("ERROR! There's probly no directory 'data'. \n");
    }
}

void FileDownloader::performDownloading(bool checkIfExists)
{
    for(unsigned int i = 0; i < links.size(); i++)
    {
        if(checkIfExists)
        {    
            if(isFileDownloaded(statusFileNames[i]))
            {            
                continue;
            }
            else
            {
                download(i);
                createFileForChecking(i);
            }
        }
        else 
        {
            download(i);
        }
    }
}


void extractZipFolders() {
    std::vector<std::string> linksToZip = {"set1-lite-en_us.zip", "set2-lite-en_us.zip", "set3-lite-en_us.zip", "set4-lite-en_us.zip"};
    for (auto &link : linksToZip ) {
        std::cout << "Unzipping " << link << "..."; 
        system((std::string("unzip -qo ./data/") + link + " -d data").c_str());
        std::remove((std::string("./data/") + link).c_str());
    }
}

