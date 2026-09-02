cmake_minimum_required(VERSION 3.4.1)

add_library(TestJni SHARED src/main/cpp/TestJni.cpp)

find_library(log-lib log)

# 链接库
target_link_libraries(TestJni ${log-lib})