#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <curl/curl.h>
#include <iostream>
#include <string>

namespace fd
{
    class FileDownloader
    {
        CURL *curl;
        FILE *fp;
        std::string links[10];
        std::string fileNames[10];
        //folder name for downloaded files;
        std::string folderPath;
        
        public:
        FileDownloader(std::string folderPath_);
        void downloadFiles();
    };
}

#endif
