# Требуемая минимальная версия CMake
cmake_minimum_required(VERSION 3.30)

# Название и версия основного проекта
project("search_engine" VERSION 1.0)

# Создаем переменную, хранящую пути к файлам
file(
    GLOB TARGET_SRC
    main.cpp
    ../inc/main.hpp
)

# Создаем переменную, хранящую пути к заголовочным файлам библиотеки
file(
    GLOB HEADER_LIB
    ../inc/*.hpp
)

# Создаем переменную, хранящую пути к файлам реализации библиотеки
file(
    GLOB SOURCE_LIB
    ../inc/*((?!main))*.cpp
)

# Создаем библиотеку для последующего использования (например, в тестах)
add_library(MySearchEngineLib ${HEADER_LIB} ${SOURCE_LIB})

# Добавляем сторонние библиотеки
include(FetchContent)

# Отключаем модульные тесты для библиотеки json
set(JSON_BuildTests OFF CACHE INTERNAL "")

# Скачиваем nlohmann json из GitHub репозитория (если еще не скачан)
FetchContent_Declare(
    json
    URL
    https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

# Открываем доступность скачанных из GitHub репозитория данных
FetchContent_MakeAvailable(json)

# Добавляем в проект задачу собрать исполняемый файл
add_executable(
    search_engine
    ${TARGET_SRC}
)

# Добавляем в библиотеку MySearchEngineLib библиотеку json
target_link_libraries(
    MySearchEngineLib
    nlohmann_json::nlohmann_json
)

# Добавляем библиотеку MySearchEngineLib в проект
target_link_libraries(
    search_engine
    MySearchEngineLib
)
