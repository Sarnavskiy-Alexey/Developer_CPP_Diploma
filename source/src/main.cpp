/*! \file main.cpp */
/*! \brief В этом файле объявлена главная функция проекта */

#include "main.hpp"

/*! \brief Статическая функция для очистки/создания файла ответов */
static void clearAnswersJSON()
{
    std::filesystem::path answers_file_path = relative_path_answers;
    std::ofstream answers_file(std::filesystem::absolute(answers_file_path).string());
    answers_file.close();
}

/*! \brief Главная функция проекта */
/*! \returns 0 */
int main(void)
{
    clearAnswersJSON();
    
#ifdef __TEST_SEARCH_ENGINE__
    ::testing::InitGoogleTest();
    if (RUN_ALL_TESTS() == 0)
    {
        std::cout << "Tests competed succesfully!\n";
    }
    else
    {
        std::cout << "Some errors occured while testing!\n";
    }
    system("pause");
    clearAnswersJSON();
#endif /* __TEST_SEARCH_ENGINE__ */

    try
    {
        ConverterJSON converter;
        InvertedIndex idx;
        idx.UpdateDocumentBase(converter.GetTextDocuments());
        
        SearchServer server(idx);
        server.search(converter.GetRequests());
    }
    catch (const ConfigJSONNotExistsException& X)
    {
        std::cerr << X.what() << '\n';
    }
    catch (const ConfigFieldNotExistsException& X)
    {
        std::cerr << X.what() << '\n';
    }
    catch (const NameFieldNotExistsException& X)
    {
        std::cerr << X.what() << '\n';
    }
    catch (const VersionFieldNotExistsException& X)
    {
        std::cerr << X.what() << '\n';
    }
    catch (const RequestsJSONNotExistsException& X)
    {
        std::cerr << X.what() << '\n';
    }
    catch (const RequestsFieldNotExistsException& X)
    {
        std::cerr << X.what() << '\n';
    }

    return 0;
}
