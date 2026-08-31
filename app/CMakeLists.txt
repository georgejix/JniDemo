cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
        TestJni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/TestJni.cpp)

find_library( # Sets the name of the path variable.
        log-lib

        log)

# 链接库
target_link_libraries( # Specifies the target library.
        TestJni
        ${log-lib})