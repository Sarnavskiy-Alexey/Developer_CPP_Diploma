# Минимально требуемая версия CMake
cmake_minimum_required(VERSION 3.17)

# Название и версия проекта
project("search_engine" VERSION 1.0)

# Применяемый стандарт C++
set(CMAKE_CXX_STANDARD 20)

# Включение своих директорий
include_directories(
    inc
    inc/Main
)

# Добавление сторонних библиотек
include(FetchContent)

# Отключение модульных тестов для библиотеки json
set(JSON_BuildTests OFF CACHE INTERNAL "")

# Скачивание nlohmann json из GitHub репозитория
FetchContent_Declare(
    json
    URL
    https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

# Скачивание google test из GitHub репозитория
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)




#----------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)





# Открытие доступности скаченных из GitHub репозитория данных о json
FetchContent_MakeAvailable(json googletest)



#----------
enable_testing()




# Добавление своих файлов в проект
add_executable(
    search_engine
        
    inc/Main/main.hpp
    src/Main/main.cpp
)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)




#----------
target_link_libraries(search_engine PRIVATE gtest_main)
include(googletest)
gtest_discover_tests(search_engine)
