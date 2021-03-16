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
        std::string folderPath;  //folderPath is folder path plus folders name
        
        public:
        FileDownloader(std::string folderPath_); 
        void downloadFiles();
    };
}

#endif
