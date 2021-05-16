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
        bool isFileDownloaded(std::string fileName_);                                           
        void addDirectoryPath(std::string directoryPath_);                                      
        void download(bool checkIfExists);                                                       
        void addLinks(std::vector <std::string> links_, std::vector <std::string> fileNames_, int numberOfLinks);       
        void createDirectory(std::string directoryPath_);                                       
    };
}

