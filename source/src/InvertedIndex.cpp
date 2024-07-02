/*! \file InvertedIndex.cpp */
/*! \brief Заголовочный файл для инвертированных индексов документов */
/*! \details В данном файле объявлен класс для создания инвертированного индекса для документов */

#include "InvertedIndex.hpp"
#include <algorithm>
#include <sstream>
#include <thread>
#include <mutex>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    std::mutex freq_dictionary_mutex;
    /* очистка имеющихся данных */
    this->docs.clear();
    freq_dictionary.clear();

    this->docs.resize(input_docs.size());
    this->files_count = input_docs.size();
    
    /* заполнение новыми данными файла docs */
    std::copy(input_docs.begin(), input_docs.end(), this->docs.begin());

    /* лямбда-функция для добавления в поток */
    auto func = [&](size_t i){
        std::stringstream buffer_stream(input_docs[i]);
        std::string word;
        int word_count = 1;
        while (buffer_stream >> word && word_count < 1000)
        {
            /* если в буфере встретится пустое слово, то закончить обработку буфера */
            if (word.size() < 1)
            {
                break;
            }
            else if (word.size() > 100)
            {
                word.resize(100);
            }
            word_count++;

            freq_dictionary_mutex.lock();

            /* если ключевое слово имеется в словаре, то... */
            if (this->freq_dictionary.find(word) != this->freq_dictionary.end())
            {
                bool flag = false;

                /* ... обновить значение count для существующего doc_id, ... */
                for (size_t j = 0; j < this->freq_dictionary[word].size(); j++)
                {
                    if (this->freq_dictionary[word][j].doc_id == i)
                    {
                        this->freq_dictionary[word][j].count++;
                        flag = true;
                        break;
                    }
                }
                /* ... иначе добавить новый doc_id в вектор */
                if (!flag)
                {
                    this->freq_dictionary[word].push_back({ .doc_id = i, .count = 1});
                }
            }
            else
            {
                this->freq_dictionary[word] = {};
                this->freq_dictionary[word].push_back({ .doc_id = i, .count = 1 });
            }

            freq_dictionary_mutex.unlock();
        }
    };

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 8; i++)
    {
    }

    /* заполнение словаря */
    for (size_t i = 0; i < input_docs.size(); i++)
    {
        threads.push_back(std::thread(func, i));
    }
    for (size_t i = 0; i < input_docs.size(); i++)
    {
        threads[i].join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    if (this->freq_dictionary.find(word) != this->freq_dictionary.end())
    {
        return this->freq_dictionary[word];
    }

    return std::vector<Entry>(0);
}

size_t InvertedIndex::GetFilesCount() const
{
    return this->files_count;
}
