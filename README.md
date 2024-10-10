OpenVDB Boilerplate
===================
This is a simple boilerplate for OpenVDB. It is a simple CMake project that opens a VDB file and prints all grids with
name and type.

# Ubuntu
Install the required dependencies
```bash
apt-get install -y libboost-iostreams-dev
apt-get install -y libtbb-dev
apt-get install -y libblosc-dev
```
> Note: There exists also a package for OpenVDB (`libopenvdb-dev`), but haven't got it to work yet. `find_package` is
> not working properly, cloning the package from GitHub and building it manually works but is more expensive I think.

Build the project
```bash
cmake -S . -B build

cmake --build build
```

To speed up building, you can use the `-j` flag to specify the number of threads to use. For example, to use 4 threads:
```bash
cmake --build build -j 4
```
> Warning: Building OpenVDB is very expensive, especially when using many threads. 4 threads require about 12GB of RAM,
> 8 threads peek at around 15GB. Build might fail if you run out of memory.


# Windows
> This is a work in progress. I have not yet been able to build OpenVDB on Windows. However there seems to be 
> precompiled binaries at https://www.msys2.org/, see this 
> [repo](https://github.com/msys2/MINGW-packages/tree/master/mingw-w64-openvdb). Did not have time to test this yet.

## Install vcpkg
Inside the target directory for vcpkg (e.g. `C:\Programs` or `C:\tools`), clone the vcpkg repository
```bash
git clone https://github.com/microsoft/vcpkg.git
```

Run the bootstrap script
```bash
cd vcpkg
.\bootstrap-vcpkg.bat
```

## Install dependencies
Install all required dependencies (this will take a while)
```bash
vcpkg install zlib:x64-windows
vcpkg install blosc:x64-windows
vcpkg install tbb:x64-windows
vcpkg install boost-iostreams:x64-windows
vcpkg install boost-any:x64-windows
vcpkg install boost-algorithm:x64-windows
vcpkg install boost-interprocess:x64-windows
```

# CLion Setup
## Windows Only
To use this project in CLion, you need to set the CMake profile to use the correct toolchain file. 
Go to `File -> Settings -> Build, Execution, Deployment -> CMake` and select your profile (or create a new one). Add
the following line to the `CMake options` field:
```
-DCMAKE_TOOLCHAIN_FILE=C:\Programs\vcpkg\scripts\buildsystems\vcpkg.cmake
```
Also make sure to limit the number of threads used by the build system to prevent running out of memory. You can do 
this by setting the `Build options` field to `-j 4` (or any other number of threads you want to use).

However I have not yet been able to build OpenVDB on Windows, compiling fails with MinGW.
The OpenVDB binary are getting to large and the assembler fails. I haven't tested the current version (which is using
the `-Os` flag to optimize for size) yet.

But even if this work, this will be on the cost of performance as the compiler will not optimize for speed.

## WSL
To open the project in WSL, clone this repository in your WSL environment. Then open the project in CLion by using
the `Remote Development...` option. Select WSL and press the `+` to open a folder. Select the folder where you cloned
the repository and open it. CLion will now open the project in WSL and you can build and run the project from there.
You will be able to use the full functions of CLion, including debugging. However it might be slower than running it
natively on Windows.

Go to `File -> Settings -> Build, Execution, Deployment -> CMake` and select your profile (or create a new one). To
limit the number of threads used by the build system, set the `Build options` field to `-j 4` (or any other number).
4 Threads require about 12GB of RAM. 8 Threads peek at around 15GB.