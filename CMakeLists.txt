cmake_minimum_required(VERSION 3.0)
project(MyTest)

include_directories(motorscontrolLib)
include_directories(motorscontrolLib/include)
include_directories(motorscontrolLib/include/QtCore)
include_directories(motorscontrolLib/include/QtNetwork)
link_directories(motorscontrolLib/lib)
add_compile_options(-std=c++11)
add_compile_options(-fPIC)
add_compile_options(-DQT_NO_VERSION_TAGGING)
add_compile_options(-pthread)

add_executable(MyTest main.cpp test.cpp)

target_link_libraries(MyTest
 motorsControll
 pthread
 )