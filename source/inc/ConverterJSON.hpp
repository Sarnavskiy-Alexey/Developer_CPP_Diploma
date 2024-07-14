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
    
    /*! \brief Метод кладет в файл answers.json результаты поисковых запросов */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

    /*! \brief Метод для получения названия движка */
    const std::string GetEngineName();

    /*! \brief Метод для получения версии движка */
    const std::string GetEngineVersion();
private:
    /*! \brief Метод для проверки содержимого файла config.json */
    bool CheckConfigJSON();
    
    /*! \brief Метод для проверки содержимого файла requests.json */
    bool CheckRequestsJSON();

    /*! \brief Копия данных из файла конфигурации для более простого доступа */
    nlohmann::json config_json_data;

    /*! \brief Копия данных из файла запросов для более простого доступа */
    nlohmann::json requests_json_data;
};
