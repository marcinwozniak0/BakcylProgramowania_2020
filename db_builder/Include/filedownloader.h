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
        void addDirectoryPath(std::string directoryPath_);
        void createDirectory(std::string directoryPath_);
        void addLinks(std::vector <std::string> links_, std::vector <std::string> fileNames_, int numberOfLinks);
        bool isFileDownloaded(std::string fileName_);
        void download(int i);
        // performDownloading checks if file is already downloaded (if checkIfExists if TRUE)
        // if file doesn't already exists performDownloading calls download for the actual downloading 
        void performDownloading(bool checkIfExists);
    };
}
