/*! \file main.cpp */
/*! \brief В этом файле объявлена главная функция проекта */

#include "main.hpp"
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

/*! \brief Главная функция проекта */
/*! \returns 0 */
int main(void)
{
    std::cout << "Hello, world!" << std::endl;

    // ::testing::InitGoogleTest();

    // return RUN_ALL_TESTS();
    return 0;
}
