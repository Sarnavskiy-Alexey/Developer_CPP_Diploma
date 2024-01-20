# Для модуля 32
cmake_minimum_required(VERSION 3.17)
project("search_engine" VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(
    search_engine
        
    src/Main/main.cpp
    inc/Main/main.hpp
)
        
target_include_directories(search_engine
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/Main>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/inc/Main>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

# set_target_properties(search_engine
#     PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ../bin
# )

# Настройка GTest
# копирование gtest из репозитория
include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# добавление include_directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# для корректной работы библиотеки с компилятором MinGW
set(gtest_disable_pthreads on)
# выставка динамического подключения библиотеки к проекту
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# сделать все настройки доступными для проекта
FetchContent_MakeAvailable(googletest)
# в проекте будут применяться тесты
enable_testing()
# добавление библиотеки gtest_main
target_link_libraries(search_engine PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(search_engine)
