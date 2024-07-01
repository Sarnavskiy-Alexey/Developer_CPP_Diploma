/*! \file main.cpp */
/*! \brief В этом файле объявлена главная функция проекта */

#include "main.hpp"

/*! \brief Главная функция проекта */
/*! \returns 0 */
int main(void)
{
    std::filesystem::path answers_file_path = relative_path_answers;
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
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
