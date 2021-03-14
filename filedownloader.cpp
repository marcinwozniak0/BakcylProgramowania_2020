#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <curl/curl.h>

#include "filedownloader.h"

using namespace fd;
namespace fs = std::filesystem;

FileDownloader::FileDownloader()
{ 
    folderName = "downloaded_files";
    fs::create_directory("../../" + folderName);
    
    links[0] = "https://dd.b.pvp.net/latest/set1/en_us/data/set1-en_us.json";
    fileNames[0] = "set1-en_us.json";
    
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
    
    if(res == CURLE_OK)
    {
        printf("SUCCES! " + fileNames[0] + " DOWNLOADED");
    } 
    else 
    {
        printf("ERROR IN DOWNLOADING : \n", curl_easy_strerror(res));
    }
    
    if(rename("set1-en_us.json", "../../downloaded_files/set1-en_us.json.json") < 0)
    {
        printf("ERROR! There's probly no folder 'downloaded_files'. \n");
    }
    else 
    {
        printf("SUCCES! \n");
    }

    fclose(fp);
    
    curl_easy_cleanup(curl);
}
