/*! \file main.cpp */
/*! \brief В этом файле объявлена главная функция проекта */

#include "main.hpp"

/*! \brief Главная функция проекта */
/*! \returns 0 */
int main(void)
{
#ifdef __TEST__
    TestConverterJSONFunctionality();
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
    // return 0;
#else
    return 0;
#endif /* __TEST__ */
}
