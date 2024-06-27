/*! \file main.cpp */
/*! \brief В этом файле объявлена главная функция проекта */

#include "main.hpp"
#include "ConverterJSON.hpp"
#include <fstream>

// TEST(sample_test_case, sample_test)
// {
//     EXPECT_EQ(1, 1);
// }

const std::vector<std::vector<std::pair<int, float>>> K_answers_example =
{
    {
        { 0, 0.989 },
        { 1, 0.897 },
        { 2, 0.750 },
        { 3, 0.670 },
        { 4, 0.561 }
    },
    {
        { 0, 0.769 }
    },
    { }
};

/*! \brief Главная функция проекта */
/*! \returns 0 */
int main(void)
{
    /* пример работы всех методов класса ConverterJSON */

    ConverterJSON converter;
    try
    {
        std::cout << converter.GetResponsesLimit() << std::endl;
        std::vector<std::string> c = converter.GetTextDocuments();
        for (const std::string &s : c)
        {
            std::cout << s << std::endl;
        }
        std::vector<std::string> r = converter.GetRequests();
        for (const std::string &s : r)
        {
            std::cout << s << std::endl;
        }
        std::filesystem::path answers_file_path = "../appendix/answers.json";
        if (std::filesystem::exists(answers_file_path))
        {
            std::ifstream answers_file(std::filesystem::absolute(answers_file_path).string(), std::ios_base::trunc);
            answers_file.close();
        }
        else
        {
            std::ifstream answers_file(std::filesystem::absolute(answers_file_path).string());
            answers_file.close();
        }
        converter.putAnswers(K_answers_example);
    }
    catch (const ConfigJSONNotExistsException& X)
    {
        std::cout << X.what() << "\n";
        exit(-1);
    }
    catch (const RequestsJSONNotExistsException& X)
    {
        std::cout << X.what() << "\n";
        exit(-2);
    }
    catch (const AnswersJSONNotExistsException& X)
    {
        std::cout << X.what() << "\n";
        exit(-3);
    }
    catch (const nlohmann::json_abi_v3_11_3::detail::type_error& X)
    {
        std::cerr << X.what();
        exit(-4);
    }

    return 0;
}
