/*! \file ConverterJSON.cpp */
/*! \brief Файл с определением класса для взаимодействия с JSON-файлами */
/*! \details В данном файле определены методы класса для взаимодействия с JSON файлами: */
/*! - для считывания конфигурационных данных из JSON */
/*! - для преобразования запросов в формате JSON */
/*! - для формирования ответов в заданном формате JSON */

#include "ConverterJSON.hpp"
#include <fstream>
#include <filesystem>

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::vector<std::string> result;
    std::filesystem::path config_path = relative_path_config;

    /* проверка на существование файла конфигурации */
    if (std::filesystem::exists(config_path))
    {
        std::ifstream config_file(std::filesystem::absolute(config_path).string());
        nlohmann::json config_data;
        config_file >> config_data;
        std::vector<std::string> files = config_data["files"];
        std::vector<std::filesystem::path> file_paths;
        
        for (const std::string &f : files)
        {
            std::filesystem::path p = f;
            file_paths.push_back(p);
        }
        
        for (const std::filesystem::path &p : file_paths)
        {
            try
            {
                /* проверка на существование файла из конфигурации */
                if (std::filesystem::exists(p))
                {
                    std::string tmp;
                    std::ifstream file(std::filesystem::absolute(p).string());
                    result.push_back("");
                    while (getline(file, tmp))
                    {
                        *(result.end() - 1) += (tmp);
                        if (!file.eof())
                        {
                            *(result.end() - 1) += '\n';
                        }
                    }
                }
                else
                {
                    throw FileNotExistsException(p);
                }
            }
            catch (const FileNotExistsException& X)
            {
                std::cout << X.what() << std::endl;
            }
        }

        config_file.close();
    }
    else
    {
        throw ConfigJSONNotExistsException();
    }
    return result;
}

int ConverterJSON::GetResponsesLimit()
{
    std::filesystem::path config_path = relative_path_config;
    if (std::filesystem::exists(config_path))
    {
        std::cout << "here3\n";
        std::ifstream config_file(std::filesystem::absolute(config_path).string());
        nlohmann::json config_data;
        config_file >> config_data;
        config_file.close();

        return config_data["config"]["max_responses"];
    }
    else
    {
        std::cout << "here4\n";
        throw ConfigJSONNotExistsException();
    }
    return 0;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::vector<std::string> result;
    std::filesystem::path requests_path = relative_path_requests;
    if (std::filesystem::exists(requests_path))
    {
        std::ifstream requests_file(std::filesystem::absolute(requests_path).string());
        nlohmann::json requests_data;
        requests_file >> requests_data;
        result = requests_data["requests"];
        requests_file.close();
    }
    else
    {
        throw RequestsJSONNotExistsException();
    }

    return result;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
    std::filesystem::path answers_path = relative_path_answers;
    std::ofstream answers_file;
    nlohmann::json answers_data;
    nlohmann::json requests;
    nlohmann::json rel;
    if (std::filesystem::exists(answers_path))
    {
        answers_file.open(std::filesystem::absolute(answers_path).string(), std::ios_base::ate);

        for (size_t i = 0; i < answers.size(); i++)
        {
            std::vector<nlohmann::json> relevance;
            nlohmann::json request;
            if (answers[i].size() > 1)
            {
                request["result"] = "true";
                for (size_t j = 0; j < answers[i].size(); j++)
                {
                    rel["docid"] = answers[i][j].first;
                    rel["rank"] = answers[i][j].second;
                    relevance.push_back(rel);
                }
                request["relevance"] = relevance;
            }
            else if (answers[i].size() == 1)
            {
                request["result"] = "true";
                request["docid"] = answers[i][0].first;
                request["rank"] = answers[i][0].second;
            }
            else
            {
                request["result"] = "false";
            }
            requests["request" + std::string(i + 1 < 10 ? "00" : (i + 1 < 100 ? "0" : "")) + std::to_string(i + 1)] = request;
        }
        answers_data["answers"] = requests;
        answers_file << answers_data;

        answers_file.close();
    }
    else
    {
        throw AnswersJSONNotExistsException();
    }
}
