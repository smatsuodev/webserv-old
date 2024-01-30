# Webserv

## Structure

```
.
├── CMakeLists.txt
├── README.md
├── bin                         # Executables
├── cmd                         # Program entry point
│   └── webserv.cpp
├── internal                    # Internal libraries
│   ├── CMakeLists.txt
│   └── hello
│       ├── hello.cpp
│       └── hello.hpp
└── tests                       # Unit tests 
    ├── CMakeLists.txt
    ├── hello_test.cpp
    └── utils
        └── assert_output.hpp
```

## Build

This project uses CMake as build system.

```bash
cmake -B build
cd build && make -j
```

For release build, please execute `cmake` command as follows.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

The executable are built in the `bin/` directory.

```bash
bin/webserv
```

## Test

After building, you can run the unit tests with `ctest`.

```bash
cd build && ctest -j
```

By using `-R` option, you can filter the tests to run. Please refer to the command's help for more details.

```
ctest -R <regex>
```