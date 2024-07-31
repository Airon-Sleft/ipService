# ipService
Fast service for get information about IP address.

Build on Linux:

0. You need install curl,libzip (and maybe other depencies for last one). apt-get install curl, apt-get install libzip
1. cmake --build debug
2. If there are errors with cmake, install depencies printed in console.

Build on Windows:

1. Install VCPKG.
2. In directory of project: vcpkg new --application
3. vcpkg add port curl
4. vcpkg add port libzip
5. cmake --preset=default
6. cmake --build build
