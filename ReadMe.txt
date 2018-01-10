
Installing boost libraries for GCC (MinGW) on Windows

GCC 7.2: MinGW-w64-for32bit-64bitx86_64-7.2.0-release-win32-sjlj-rt_v5-rev0
Boost 1.67: boost_1_67_0-snapshot at https://dl.bintray.com/boostorg/master/boost_1_67_0-snapshot.7z

Folder setup
	Extract downloaded boost source, e.g. H:\boost\boost_1_67_0.
	Create a folder for Boost.Build installation, e.g. H:\boost\boost_1_67_0\boost-build.
	Create a folder within for building, i.e. H:\boost\boost_1_67_0\build.
	Create a folder for installation, e.g. H:\boost\boost_1_67_0-build-gcc_7_2.
	
GCC setup
	Open Command Prompt.
	Run g++ --version.
	If the output contains g++ version number then GCC should be set up properly to run from command line and you can continue.
	
Boost.Build setup
	Open Command Prompt and navigate to H:\boost\boost_1_67_0\tools\build.
	Run bootstrap.bat gcc.
	Run b2 install --prefix="H:\boost\boost_1_67_0\boost-build"
	Add H:\boost\boost_1_67_0\boost-build\bin to Windows PATH.

Boost building
	Open Command Prompt and navigate to H:\boost\boost_1_67_0.
	Run
	b2 --build-dir="H:\boost\boost_1_67_0\build" --prefix="H:\boost\boost_1_67_0-build-gcc_7_2" toolset=gcc
 
Project setup
	Add include folder, i.e. H:\boost\boost_1_67_0-build-gcc_7_2\include\boost-1_60.
	Add linker folder, i.e. H:\boost\boost_1_67_0-build-gcc_7_2\lib.
	Link required libraries, e.g. libboost_regex-mgw48-mt-1_60.a.
 
=========================================
mingw-w64-x86_64-gcc4.8.1-win32-sjlj

git clone https://github.com/google/protobuf.git
cd protobuf
mkdir install_dir
mkdir cmake_build
cd cmake_build
cmake -DCMAKE_INSTALL_PREFIX=../install_dir -DCMAKE_INSTALL_LIBDIR=lib -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_CXX_FLAGS="-std=c++11" -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ../cmake
mingw32-make
mingw32-make install

g++ -I"C:/C++/protobuf/protobuf.3.5.1-gcc.5.1.0/include" -L"C:/C++/protobuf/protobuf.3.5.1-gcc.5.1.0/lib" main.cpp addressbook.pb.cc -lprotobuf -pthread -static-libgcc -std=c++11


