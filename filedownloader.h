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
        std::string directoryPath;                                                               
        
        public:  
        FileDownloader(); 
        void download();                                                                        // downloads and moves files to a directory    
        void addLinks(std::string links_[], std::string fileNames_[], int numberOfLinks);       // adds links for the program to download
        void createDirectory(std::string directoryPath_);                                       // creates directory for downloaded files
    };
}

#endif
