# Минимально требуемая версия CMake
cmake_minimum_required(VERSION 3.17)

# Название и версия проекта
project("search_engine" VERSION 1.0)

# Применяемый стандарт C++
set(CMAKE_CXX_STANDARD 20)

# Включение своих директорий
include_directories(
    ../inc
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

# Открытие доступности скаченных из GitHub репозитория данных
FetchContent_MakeAvailable(json)

# Добавление своих файлов в проект
add_executable(
    search_engine

    main.cpp

    ../inc/ConverterJSON.hpp
    ConverterJSON.cpp

    ../inc/InvertedIndex.hpp
    InvertedIndex.cpp

    ../inc/SearchServer.hpp
    SearchServer.cpp
    )

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
