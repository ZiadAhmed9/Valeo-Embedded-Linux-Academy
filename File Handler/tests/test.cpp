#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST( TestName, Subtest_1)
{
    
}


int main(int argc, char*argv[])
{
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}