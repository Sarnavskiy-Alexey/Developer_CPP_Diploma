/*! \file ConverterJSON.cpp */
/*! \brief Файл с определением класса для взаимодействия с JSON-файлами */
/*! \details В данном файле определены методы класса для взаимодействия с JSON файлами: */
/*! - для считывания конфигурационных данных из JSON */
/*! - для преобразования запросов в формате JSON */
/*! - для формирования ответов в заданном формате JSON */

#include <fstream>
#include <filesystem>
#include "ConverterJSON.hpp"
#include "exceptions.hpp"

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::vector<std::string> result;

    if (CheckConfigJSON())
    {
        std::vector<std::string> files = this->config_json_data["files"];
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
    }

    return result;
}

int ConverterJSON::GetResponsesLimit()
{
    std::filesystem::path config_path = relative_path_config;

    if (CheckConfigJSON())
    {
        if (this->config_json_data["config"].contains("max_responses"))
        {
            return this->config_json_data["config"]["max_responses"];
        }
        else
        {
            return 5;
        }
    }
    return 0;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::vector<std::string> result;
    if (CheckRequestsJSON())
    {
        return this->requests_json_data["requests"];
    }
    else
    {
        return result;
    }
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

bool ConverterJSON::CheckConfigJSON()
{
    std::filesystem::path config_path = relative_path_config;

    /* проверка на существование файла конфигурации */
    if (std::filesystem::exists(config_path))
    {
        std::ifstream config_file(std::filesystem::absolute(config_path).string());
        config_file >> this->config_json_data;
        config_file.close();

        /* проверка на существование полей в файле конфигурации */

        if (this->config_json_data.contains("config"))
        {
            if (!this->config_json_data["config"].contains("name"))
            {
                throw NameFieldNotExistsException();
            }

            if (!this->config_json_data["config"].contains("version"))
            {
                throw VersionFieldNotExistsException();
            }
        }
        else
        {
            throw ConfigFieldNotExistsException();
        }

        if (!this->config_json_data.contains("files"))
        {
            throw FilesFieldNotExistsException();
        }
    }
    else
    {
        throw ConfigJSONNotExistsException();
    }

    return true;
}

bool ConverterJSON::CheckRequestsJSON()
{
    std::filesystem::path requests_path = relative_path_requests;
    if (std::filesystem::exists(requests_path))
    {
        std::ifstream requests_file(std::filesystem::absolute(requests_path).string());
        requests_file >> this->requests_json_data;
        requests_file.close();

        if (!this->requests_json_data.contains("requests"))
        {
            throw RequestsFieldNotExistsException();
        }
    }
    else
    {
        throw RequestsJSONNotExistsException();
    }

    return true;
}

const std::string ConverterJSON::GetEngineName()
{
    std::filesystem::path config_path = relative_path_config;

    if (CheckConfigJSON())
    {
        if (this->config_json_data["config"].contains("name"))
        {
            return this->config_json_data["config"]["name"];
        }
        else
        {
            return "no name";
        }
    }
    return "no name";
}

const std::string ConverterJSON::GetEngineVersion()
{
    std::filesystem::path config_path = relative_path_config;

    if (CheckConfigJSON())
    {
        if (this->config_json_data["config"].contains("version"))
        {
            return this->config_json_data["config"]["version"];
        }
        else
        {
            return " no version";
        }
    }
    return " no version";
}
