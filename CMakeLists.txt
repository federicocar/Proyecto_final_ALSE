cmake_minimum_required(VERSION 3.1)

project(proy_final)
add_executable(${PROJECT_NAME} main.cpp sensor.h sensor.cpp mediciones.h mediciones.cpp )
target_link_libraries (${PROJECT_NAME} sqlite3 )