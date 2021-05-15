#pragma once

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>

namespace fd
{
    class FileDownloader
    {
        //for jsons
        CURL *curl;
        FILE *fp;
             
        std::vector <std::string> links;
        std::vector <std::string> fileNames;
        std::string directoryPath = "";
                                                                                
        public:
        FileDownloader();
        bool isFileDownloaded(std::string fileName_);                                           // checks if file is already downloaded (checks in directory given in directoryPath)
        void addDirectoryPath(std::string directoryPath_);                                      
        void download(bool checkIfExists);                                                      // downloads and moves files to a directory 
        void addLinks(std::vector <std::string> links_, std::vector <std::string> fileNames_, int numberOfLinks);       // adds links for the program to download
        void createDirectory(std::string directoryPath_);                                       // creates directory for downloaded files
        
        
    };
}

