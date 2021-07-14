#include <gtest/gtest.h>


extern "C" {
    #include "ll.h"
}


TEST(LList, AddPersonPass1)
{
  Person* list = NULL;
  add_person_index(&list, "Person1", 0);
  free_list(&list);
}


TEST(LList, AddPersonPass2)
{
  Person* list = NULL;

  auto p = add_person_begin(&list, "Person1");

  EXPECT_EQ(p, 1);

  p = add_person_end(&list, "Person2");

  EXPECT_EQ(p, 2);

  free_list(&list);
}


int main()
{
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
