/*! \file ConverterJSON.hpp */
/*! \brief Заголовочный файл для взаимодействия с JSON-файлами */
/*! \details В данном файле объявлен класс для взаимодействия с JSON файлами: */
/*! - для считывания конфигурационных данных из JSON */
/*! - для преобразования запросов в формате JSON */
/*! - для формирования ответов в заданном формате JSON */

#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <exception>

const std::string relative_path = "../../";
const std::string relative_path_config = relative_path + "appendix/config.json";
const std::string relative_path_requests = relative_path + "appendix/requests.json";
const std::string relative_path_answers = relative_path + "appendix/answers.json";

/*! \class ConverterJSON */
/*! \brief Класс для работы с JSON-файлами */
class ConverterJSON {
public:
    /*! \brief Конструктор по умолчанию */
    ConverterJSON() = default;

    /*! \brief Метод получения содержимого файлов */
    /*! \returns Возвращает список с содержимым файлов, перечисленных в config.json */
    std::vector<std::string> GetTextDocuments();
    
    /*! \brief Метод считывает поле max_responses для определения предельного количества ответов на один запрос */
    /*! \returns Предельное количество ответов на один запрос */
    int GetResponsesLimit();
    
    /*! \brief Метод получения запросов из файла requests.json */
    /*! \returns Возвращает список запросов из файла requests.json */
    std::vector<std::string> GetRequests();
    
    /*! \brief Положить в файл answers.json результаты поисковых запросов */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};

class ConfigJSONNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "File config.json does not exists!";
    }
};

class RequestsJSONNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "File requests.json does not exists!";
    }
};

class AnswersJSONNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "File answers.json does not exists!";
    }
};

class FileNotExistsException : std::exception {
private:
    std::filesystem::path file_path;
public:
    FileNotExistsException(std::filesystem::path p) : file_path(p) {}
    const char * what() const noexcept override {
        std::string result = std::string("File \"") + std::filesystem::absolute(file_path).string() + std::string("\" does not exists!");
        return result.c_str();
    }
};
