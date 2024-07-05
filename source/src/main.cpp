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
    return RUN_ALL_TESTS();
#else /* __TEST_SEARCH_ENGINE__ */
    try
    {
        /* создать объект-конвертер */
        ConverterJSON converter;

        /* создать объект-индекс */
        InvertedIndex idx;

        /* считать содержимое всех документов из файла конфигурации */
        std::vector<std::string> documents = converter.GetTextDocuments();

        /* Обновить базу данных документов в объекте-индексе */
        idx.UpdateDocumentBase(documents);

        /* создать объект-сервер */
        SearchServer server(idx);

        /* получить все запросы из файла запросов */
        std::vector<std::string> requests = converter.GetRequests();

        /* получить результаты поиска (в файл answers.json) */
        std::vector<std::vector<RelativeIndex>> search_result = server.search(requests);
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
#endif /* __TEST_SEARCH_ENGINE__ */
}
