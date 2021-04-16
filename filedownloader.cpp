#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <curl/curl.h>

#include "filedownloader.h"

using namespace fd;
namespace fs = std::filesystem;

FileDownloader::FileDownloader()
{ 
    curl = curl_easy_init();
}

void FileDownloader::createDirectory(std::string directoryPath_)
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
}

void FileDownloader::addLinks(std::string links_[], std::string fileNames_[], int numberOfLinks)
{
    for(int i = 0; i < numberOfLinks; i++)
    {
        std::string l = links_[i];
        links.push_back(l);
        
        std::string n = fileNames_[i];
        fileNames.push_back(n);
    }
}

void FileDownloader::download()
{   
    CURLcode res;
    
    long unsigned int i = 0;
    while(i < links.size())
    {  
        //checking if file already exists    
        std::string fileDirectory = directoryPath + "/" + fileNames[i];
        
        FILE *fileToTest = fopen(fileDirectory.c_str(), "r"); 
        
        if(fileToTest)
        {
            std::string msg = fileNames[i] + " already exists!";
            std::cout<<msg<<std::endl;
            
            fclose(fileToTest);
            i++;
            continue;            
        }
        
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
        i++;
    }
    
    curl_easy_cleanup(curl);
}
