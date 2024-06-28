/*! \file InvertedIndex.hpp */
/*! \brief Заголовочный файл для инвертированных индексов документов */
/*! \details В данном файле объявлен класс для создания инвертированного индекса для документов */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Entry {
    /*! \brief Номер элемента в векторе docs, по которому хранится текст */
    size_t doc_id;

    /*! \brief Число, которое обозначает, сколько раз ключевое слово встретилось в документе doc_id */
    size_t count;

    /*! \brief Метод для сравнения двух структур Entry */
    /*! \details Данный оператор необходим для проведения текстовых сценариев */
    bool operator==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.doc_id);
    }
};

/*! \class InvertedIndex */
/*! \brief Класс для создания инвертированных индексов для документов */
class InvertedIndex {
public:
    /*! \brief Конструктор по умолчанию */
    InvertedIndex() = default;

    /*! \brief Метод для обновления или заполнения базы документов, по которой будет совершаться поиск */
    /*! \param input_docs содержимое документов */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    /*! \brief Метод для определения количества вхождений слова word в загруженной базе документов */
    /*! \param word слово, частоту вхождений которого необходимо определить */
    /*! \returns Возвращает подготовленный список с частотой слов */
    std::vector<Entry> GetWordCount(const std::string& word);

    /*! \brief Метод для возвращения количества файлов */
    size_t GetFilesCount() const;
private:
    /*! \brief Список содержимого документов */
    /*! \details Коллекция для хранения текстов документов, в которой номер элемента в векторе определяет doc_id для формирования результата запроса */
    std::vector<std::string> docs;
    
    /*! \brief Частотный словарь */
    /*! \details Коллекция для хранения частоты слов, встречаемых в тексте */
    std::map<std::string, std::vector<Entry>> freq_dictionary;

    /*! \brief количество файлов */
    size_t files_count = 0;
};
