## Linux
### Debian Testing and above
This program has only been tested on Debian Testing and above.
It requires the following packages to be installed:
- cmake
- gcc (version 10 or higher)
- g++ (version 10 or higher)
- libboost-dev (version 1.71 or above)
- libboost-program-options-dev
- libncurses-dev
- libpcap-dev
- libpthread-stubs0-dev
- libnl-3-dev
- libnl-genl-3-dev
- libnl-nf-3-dev
- libnl-route-3-dev

### Arch Linux
- libnl
- cmake
- boost
- boost-libs
- libpcap
- ncurses
- ncurses5-compat-libs
- gcc
- libpthread-stubs

If those packages are installed, you can compile the program using the following command (from the project's root):
```bash
mkdir build && cd build && cmake .. && cmake --build . -- -j`nproc`
``` 

## Windows
### Ansible
There is an ansibile playbook `install.yml` avaiable in Resources/Ansible_Windows. 
The playbook needs a vaulted ssh private key to be availabe as `id_rsa.vault`. 
This script will update your computer and install all the required tools to build xlinkhandheldassistant. It will install everything in `build_tools`, 
on the root of your harddrive except for 7-zip and git, as those don't have configurable install paths using chocolatey.
After the script has ran you should immediately be able to check out xlinknhandheldassistant using git, create a build folder and run in an MingW32 terminal:
```bash
cmake .. -G "MinGW Makefiles" \
-DBOOST_ROOT=/c/build_tools/boost \
-DPDCURSES_ROOT_DIR=/c/build_tools/pdcurses \
-DPCAP_ROOT_DIR=/c/build_tools/npcapsdk \
-DNPCAP_DLL_PATH=/c/build_tools/npcapsdk \
-DBUILD_X32=ON
```

If you are unfamiliar with ansible, information to use ansible at all can be found [here](https://docs.ansible.com/ansible/latest/user_guide/windows.html): 

### Manually
Releases on Windows are compiled using MSYS2. Visual Studio should also work, but it might need some small fixing.

**Note:** Monitor mode is not available on Windows. NPcap does not support packet injection, see: https://github.com/nmap/npcap/issues/85 .

The following programs are needed:
- MSYS2 with a GCC version of atleast 10. (Visual Studio 2019 or higher is also possible) 
  The official releases use the MSYS2 Mingw32 Command-Line to compile XLHA. 
  Installed in MSYS2:
  - bison
  - mingw-w64-i686-cmake
  - mingw-w64-i686-gcc
  - mingw-w64-i686-make
  - mingw-w64-i686-tools-git

- CMake, if using Visual Studio 2019/2022, this is built into it.

The following libraries are needed:
- Boost 0.7.1 or higher https://www.boost.org/users/download/ (system and program_options required 
  (Visual Studio also wants date-time for some reason)).  
  Commands used (from root of boost dir (in MSYS2 MINGW32)): 
  - cd tools/build
  - ./bootstrap.bat mingw
  - cp b2 ../..
  - cd ../..
  - For 64-bit:
    ```
    ./tools/build/b2.exe --build-type=minimal --toolset=gcc variant=release link=static runtime-link=static
    threading=multi --with-system --with-program_options stage
    ```
    
    Or for 32-bit:
    ```
    ./tools/build/b2.exe --build-type=minimal --toolset=gcc variant=release link=static runtime-link=static
    address-model=32 threading=multi --with-system --with-program_options stage
    ```
    
- PDCurses or other ncurses compatible library (only pdcurses tested) https://github.com/Bill-Gray/PDCursesMod
  Commands used (from root of pdcurses dir)
  - cd wincon
  - mingw32-make -j3 WIDE=Y CHTYPE_32=Y
- NPcap and NPcap SDK \
  https://nmap.org/npcap/dist/npcap-1.60.exe \
  https://nmap.org/npcap/dist/npcap-sdk-1.06.zip

After installing these, open the CMakeLists.txt and set the paths to the libraries to the paths you installed these libraries to. \
By default it looks in the following paths:
- c:\boost\
- c:\pdcurses\
- c:\npcapsdk\

If that is all in order you should be able to compile the program using Visual Studio 2019 or higher, by opening the project using it and then pressing the compile button.

For MSYS2 you should be able to run the following commands:
```batch
mkdir build 
cd build 
```

For 64-bit:

```
cmake .. -G "MinGW Makefiles"
```

Or for 32-bit:

```
cmake .. -G "MinGW Makefiles" -DBUILD_X32=1
```

And lastly:

```
mingw32-make -j`nproc`
``` 

## MacOS
For MacOS you need Brew and XCode.
You need the following packages:
- boost
- ncurses
- libpcap
- cmake

If those packages are installed, you can compile the program using the following command (from the project's root):
```bash
mkdir build && cd build && cmake .. -G"XCode" && cmake --build . -- -j`nproc`
``` 

Then you can optionally sign the executable with the following command  
(**Note:** you need to be in the Apple Developer
Program for this or have AMFI disabled).

```bash
codesign --force --sign --deep --entitlements ./entitlements.plist -s "NAME-OF-CERT" ./xlinkhandheldassistant
```

And to check if that command did its job:

```bash
codesign -d --entitlements - ./xlinkhandheldassistant
```

After that the program should be able to run.


## Building Statically
For Linux and MacOS a static build can be done by adding the following to the cmake command:  
```-DBUILD_STATIC=1```

The libraries should be statically compiled and put in the parent folder above XLHA.
Then compiling should be done in the same way as described above for your Operating System.

The Windows version is always statically compiled!

### Compile instructions used for building statically

### Linux

#### Using Docker
In Resources/Docker is a file name release-runner.Dockerfile.
- Rename this file to Dockerfile
```bash
docker build -t xlha_release_builder ../Docker
docker run -it --name xlha_release_builder su -c /bin/bash runner
cd ~
git clone git@github.com:codedwrench/xlinkhandheldassistant.git
cd xlinkhandheldassistant
mkdir build
cd build
cmake .. -DBUILD_STATIC=1
make -j`nproc`
```

#### Manually
- NCurses
```bash
./configure --with-terminfo-dirs="/etc/terminfo:/lib/terminfo:/usr/share/terminfo:/usr/lib/terminfo" --without-debug --enable-widec
make -j`nproc`
```

- Boost 
```bash
./bootstrap.sh 
./b2 link=static variant=release threading=multi runtime-link=static --with-system --with-program_options
```

- LibPCAP 
```bash
./configure --enable-ipv6 --disable-usb --disable-dbus --without-libnl --disable-universal
make -j`nproc`
```

- LibNL 
```bash
./configure
make -j`nproc`
```

#### MacOS

- NCurses
```bash
export MACOSX_DEPLOYMENT_TARGET=10.11
./configure CFLAGS="-isysroot /path/to/MacOSX10.11.sdk -arch x86_64" CXXFLAGS="-isysroot /path/to/MacOSX10.11.sdk -arch x86_64" --with-terminfo-dirs="/etc/terminfo:/lib/terminfo:/usr/share/terminfo:/usr/lib/terminfo" --without-debug --enable-widec
make -j`nproc`
```

- Boost 
```bash
export MACOSX_DEPLOYMENT_TARGET=10.11
./bootstrap.sh clang
./b2 cxxflags="-stdlib=libc++ -std=c++11 -mmacosx-version-min=10.11 -isysroot /path/to/MacOSX10.11.sdk"  link=static variant=release threading=multi runtime-link=static --with-system --with-program_options
```

- LibPCAP 
```bash
export MACOSX_DEPLOYMENT_TARGET=10.11
./configure CFLAGS="-isysroot /path/to/MacOSX10.11.sdk -arch x86_64" CXXFLAGS="-isysroot /path/to/MacOSX10.11.sdk -arch x86_64" --enable-ipv6 --disable-usb --disable-dbus --without-libnl --disable-universal
make -j`nproc`
```
