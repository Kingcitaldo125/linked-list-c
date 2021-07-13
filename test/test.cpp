#include <gtest/gtest.h>

extern "C" {
    #include "main.h"
}

static Person* person_list = NULL;


TEST(BasicTest, MyTestName1)
{
  EXPECT_EQ(0,0);
}

TEST(LList, AddPersonPass)
{
  add_person_index(&person_list, "Person1", 0);
}
