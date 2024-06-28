#include "main.hpp"
#ifdef __TEST__

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

void print_vve(const std::vector<std::vector<Entry>>& vve)
{
    std::cout << "{ \n";
    for (size_t i = 0; i < vve.size(); i++)
    {
        std::cout << "\t{ \n";
        for (size_t j = 0; j < vve[i].size(); j++)
        {
            std::cout << "\t\t{ " << vve[i][j].doc_id << ", " << vve[i][j].count << " }";
            if (j != vve[i].size() - 1 and vve[i].size() > 0) 
            {
                std::cout << ",";
            }
        }
        std::cout << "\n\t}";
        if (i != vve.size() - 1 and vve.size() > 0) 
        {
            std::cout << ",";
        }
    }
    std::cout << "\n}\n";
}

void TestInvertedIndexFunctionality(const std::vector<std::string>& docs,
                                    const std::vector<std::string>& requests,
                                    const std::vector<std::vector<Entry>>& expected)
{
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;

    idx.UpdateDocumentBase(docs);
    
    for (auto& request : requests)
    {
        result.push_back(idx.GetWordCount(request));
    }

    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic)
{
    const std::vector<std::string> docs =
    {
        "london is the capital of great britain",
        "big ben is the nickname for the Great bell of the striking clock"
    };
    const std::vector<std::string> requests = { "london", "the" };
    const std::vector<std::vector<Entry>> expected = 
    {
        {
            { 0, 1 },
        },
        {
            { 0, 1 },
            { 1, 3 }
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestBasic2)
{
    const std::vector<std::string> docs =
    {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const std::vector<std::string> requests = { "milk", "water", "cappuccino" };
    const std::vector<std::vector<Entry>> expected = 
    {
        {
            { 0, 4 },
            { 1, 1 },
            { 2, 5 }
        },
        {
            { 0, 2 },
            { 1, 2 },
            { 2, 5 }
        },
        {
            { 3, 1 }
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord)
{
    const std::vector<std::string> docs =
    {
        "a b c d e f g h i j k l",
        "statement"
    };
    const std::vector<std::string> requests = { "m", "statement" };
    const std::vector<std::vector<Entry>> expected = 
    {
        {
            
        },
        {
            { 1, 1 }
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

void TestConverterJSONFunctionality()
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
}

TEST(TestCaseSearchServer, TestSimple)
{
    const std::vector<std::string> docs =
    {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const std::vector<std::string> request = { "milk water", "sugar" };
    const std::vector<std::vector<RelativeIndex>> expected =
    {
        {
            { 2, 1 },
            { 0, 0.7 },
            { 1, 0.3 }
        },
        {

        }
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestTop5)
{
    const std::vector<std::string> docs =
    {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisboa is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow the capital of russia the third rome",
        "amsterdam is the capital of netherlands",
        "helsinki is the capital of finland",
        "oslo is the capital of norway",
        "stockholm is the capital of sweden",
        "riga is the capital of latvia",
        "tallinn is the capital of estonia",
        "warsaw is the capital of poland"
    };
    const std::vector<std::string> request = { "moscow is the capital of russia" };
    const std::vector<std::vector<RelativeIndex>> expected =
    {
        {
            { 7, 1 },
            { 14, 1 },
            { 0, 0.666666687 },
            { 0, 0.666666687 },
            { 0, 0.666666687 }
        }
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}

#endif /* __TEST__ */
