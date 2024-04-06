/*! \file InvertedIndex.hpp */
/*! \brief Заголовочный файл для инвертированных индексов документов */
/*! \details В данном файле объявлен класс для создания инвертированного индекса для документов */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Entry {
    size_t doc_id;
    size_t count;
    bool operator==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.doc_id);
    }
};

/*! \class InvertedIndex */
/*! \brief Класс для создания инвертированного индекса для документов */
/*! \details  */
class InvertedIndex {
public:
    InvertedIndex() = default;
    void UpdateDocumentBase(std::vector<std::string> input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};
