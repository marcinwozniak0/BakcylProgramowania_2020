#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <curl/curl.h>

#include "filedownloader.h"

using namespace fd;
namespace fs = std::filesystem;

FileDownloader::FileDownloader(std::string directoryPath_)
{ 
    directoryPath = directoryPath_;
    if(fs::exists(directoryPath))
    {
        printf("Directory already exists! \n");
    }
    else 
    {
        fs::create_directory(directoryPath);
    }
    
    //https://dd.b.pvp.net/latest/core/en_us/data/globals-en_us.json
    links.push_back("https://dd.b.pvp.net/latest/set1/en_us/data/set1-en_us.json");
    fileNames.push_back("set1-en_us.json");
    
    //initializing curl
    curl = curl_easy_init();
}

void FileDownloader::downloadFiles()
{   
    CURLcode res;
    fp = fopen(fileNames[0].c_str(), "wb");
    
    curl_easy_setopt(curl, CURLOPT_URL, links[0].c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    
    res = curl_easy_perform(curl);
    
    //checking if everything went well
    if(res == CURLE_OK)
    {
        printf("SUCCES! FILE DOWNLOADED \n");
    } 
    else 
    {
        printf("ERROR IN DOWNLOADING : \n", curl_easy_strerror(res));
    }
    
    //moving downloaded file to folder created with folderPath 
    std::string newPath = directoryPath + "/" + fileNames[0];
    if(rename("set1-en_us.json", newPath.c_str()) < 0)
    {
        printf("ERROR! There's probly no directory 'data'. \n");
    }
    else 
    {
        printf("SUCCES! \n");
    }

    fclose(fp);
    curl_easy_cleanup(curl);
}
