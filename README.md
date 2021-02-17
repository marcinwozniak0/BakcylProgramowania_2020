# BakcylProgramowania_2020

## Dependencies
You must install these dependencies on your own: sqlite3, jsoncpp, qt5

### All-in-one
#### apt-get
> ```sh
> sudo apt-get install libsqlite3-dev libjsoncpp-dev qt5-default
> ```
### JsonCpp

#### apt-get
> ```sh
> sudo apt-get install libjsoncpp-dev
> ```
#### Meson
> ```sh
> meson wrap install jsoncpp
> ```

#### vcpkg
Windows
> ```bat
> @rem if you don't have vcpkg
>   git clone https://github.com/microsoft/vcpkg.git
>   .\vcpkg\bootstrap-vcpkg.bat
> @rem Install JsonCpp
>   .\vcpkg\vcpkg install jsoncpp
> @rem Or if you have vcpkg in PATH
>   vcpkg install jsoncpp
> ```
Linux, Unix and other OSs which are using bash
> ```sh
> # If you don't have vcpkg
>   git clone https://github.com/microsoft/vcpkg.git
>   ./vcpkg/bootstrap-vcpkg.sh
> # Install JsonCpp
>   ./vcpkg/vcpkg install jsoncpp
> # Or if you have vcpkg in PATH
>   vcpkg install jsoncpp
> ```
#### conan
> ```sh
> conan install jsoncpp
> ```
#### GitHub
> [JsonCpp Releases | GitHub](https://github.com/open-source-parsers/jsoncpp/tags)
#### Git
> ```sh
> git clone https://github.com/open-souce-parsers/jsoncpp.git
> ```
### SQLite
#### conan
> ```sh
> conan install sqlite3
> ```
#### apt-get
> ```sh
> sudo apt-get install libsqlite3-dev
> ```
#### official site
> [SQLite](https://www.sqlite.org)
### Qt5
#### apt-get
> ```sh
> sudo apt-get install qt5-default
> ```sh
#### oficial site
> [Qt](https://www.qt.io/download)
### Installation problems
If you had any problems with installing dependencies, you would
have tried updating your package manager and tried installing again.