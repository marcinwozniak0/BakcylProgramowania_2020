#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>

namespace fd
{
    class FileDownloader
    {
        CURL *curl;
        FILE *fp;
        std::vector <std::string>links;
        std::vector <std::string>fileNames;
        std::string directoryPath;  //folderPath is folder path plus folders name
        
        public:  
        FileDownloader(std::string directoryPath_); 
        void downloadFiles();     
    };
}

#endif
