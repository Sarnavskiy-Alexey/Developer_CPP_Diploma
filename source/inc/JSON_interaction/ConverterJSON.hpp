/*! \file ConverterJSON.hpp */
/*! \brief Заголовочный файл для взаимодействия с JSON-файлами */
/*! \details В данном файле объявлен класс для взаимодействия с JSON файлами: */
/*! - для считывания конфигурационных данных из JSON */
/*! - для преобразования запросов в формате JSON */
/*! - для формирования ответов в заданном формате JSON */

#pragma once

#include <filesystem>  // path
#include <nlohmann/json.hpp>

/*! \class ConverterJSON */
/*! \brief Класс для взаимодействия с файлами JSON */
/*! \details В качестве path должен быть передан абсолютный или относительный путь до файлов answers.json, config.json или request.json */
class ConverterJSON {
private:
    nlohmann::json data;
public:
    ConverterJSON() = default;
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};
