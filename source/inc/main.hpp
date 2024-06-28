/*! \file main.hpp */
/*! \brief Подключаемый в главный файл проекта заголовочный файл */

#pragma once
#include <iostream>
#ifdef __TEST__
#include <gtest/gtest.h>
#endif /* __TEST__ */
#include <fstream>
#include "ConverterJSON.hpp"
#include "InvertedIndex.hpp"
#include "SearchServer.hpp"

void TestConverterJSONFunctionality();
void TestSearchServerFunctionality();
