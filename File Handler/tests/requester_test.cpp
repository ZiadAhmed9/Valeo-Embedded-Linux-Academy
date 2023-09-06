#include <gtest/gtest.h>
#include "Requester_functions.hpp"
using namespace std;

//Testing the is_file() function used in my requester app

TEST(is_file_test, file_extension_present)
{
    EXPECT_EQ(is_file("file.txt"), 1);
    EXPECT_EQ(is_file("example.txt"), 1);
    EXPECT_EQ(is_file("Directory"),0);
    EXPECT_EQ(is_file("/Example/Path"),0);
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}