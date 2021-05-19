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
        FILE *fp;
             
        std::vector <std::string> links;
        std::vector <std::string> fileNames;
        std::string directoryPath = "";
                                         
        public:
        std::vector <std::string> statusFileNames;
        
        void addDirectoryPath(std::string directoryPath_);
        void createDirectory(std::string directoryPath_);
        void addLinks(std::vector <std::string> links_, std::vector <std::string> fileNames_);
        bool isFileDownloaded(std::string fileName_); 
        void download(int i);
        // this funtction creates a .txt file for a downloaded file
        // the .txt file is empty and it exists just so we can check if the file 
        //has been already downloaded (the .zip is deleted after unpacking)
        void createFileForChecking(int i);
        // performDownloading checks if file is already downloaded (if checkIfExists if TRUE)
        // if file doesn't already exists performDownloading calls download for the actual downloading 
        void performDownloading(bool checkIfExists);
    };
}
