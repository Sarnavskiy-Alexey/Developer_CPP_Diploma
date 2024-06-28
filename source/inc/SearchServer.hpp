#pragma once

#include <iostream>
#include "InvertedIndex.hpp"

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank > (other.rank - 0.000001) && rank < (other.rank + 0.000001));
    }
};

/*! \class SearchServer */
/*! \brief Класс позволяет определять наиболее релевантные, соответствующие поисковому запросу, документы по прочитанным из файла requests.json поисковым запросам */
class SearchServer {
public:
    /*! \brief Конструктор */
    /*! \param idx ссылка на класс InvertedIndex, чтобы SearchServer мог узнать частоту слов встречаемых в запросе */
    SearchServer(InvertedIndex& idx) : _index(idx) {};

    /*! \brief Метод обработки поисковых запросов */
    /*! \param queries_input поисковые запросы, взятые из файла requests.json */
    /*! \returns Возвращает отсортированный список релевантных ответов для заданных запросов */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
private:
    InvertedIndex _index;
};
