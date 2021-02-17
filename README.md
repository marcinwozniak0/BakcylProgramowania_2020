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
> ```sh
> # If you don't have vcpkg
> git clone https://github.com/microsoft/vcpkg.git
> cd vcpkg
> # Windows
> .\vcpkg\bootstrap-vcpkg.bat
> # Linux/Unix/(Mac OS)?
> ./vcpkg/bootstrap-vcpkg.sh
> # Install JsonCpp
> # Windows
> .\vcpkg\vcpkg install jsoncpp
> # Linux/Unix/(Mac OS)?
> ./vcpkg/vcpkg install jsoncpp
> # Or if you have vcpkg in PATH
> vcpkg install jsoncpp
> ```
#### conan
> ```sh
> conan install jsoncpp
> ```

#### SQLite

### Installation problems
If you had any problems with installing dependencies, you would 
have tried updating your package manager and tried installing again.