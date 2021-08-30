#include <gtest/gtest.h>


extern "C" {
    #include "ll.h"
}


TEST(LList, AddPersonPass1)
{
  LinkedList* list = get_list();

  add_person_index(list, "Person1", 0);

  free_list(&list);

  EXPECT_EQ(get_size(list), 0);
}


TEST(LList, AddPersonPass2)
{
  LinkedList* list = get_list();

  auto p = add_person_begin(list, "Person1");

  EXPECT_EQ(p, 1);

  p = add_person_end(list, "Person2");

  EXPECT_EQ(p, 2);

  auto f = free_list(&list);

  EXPECT_EQ(f, 0);

  EXPECT_EQ(get_size(list), 0);
}


TEST(LList, RemovePersonPass)
{
  LinkedList* list = get_list();

  auto p = add_person_begin(list, "Person1");

  auto f = free_list(&list);

  EXPECT_EQ(f, 0);

  EXPECT_EQ(get_size(list), 0);
}


TEST(LList, RemovePersonFail)
{
  LinkedList* list = get_list();

  printf("Free");
  auto p = free_list(&list);

  EXPECT_EQ(p, 1);
  EXPECT_EQ(get_size(list), 0);

  printf("NULL LIST");
  list = NULL;
  printf("ADD");
  add_person_begin(list, "Person1");
  add_person_begin(list, "Person2");
  add_person_begin(list, "Person3");

  printf("REMOVE");
  remove_before(list);
  remove_before(list);
  remove_before(list);
  auto r = remove_before(list);

  EXPECT_EQ(r, -1);
  EXPECT_EQ(get_size(list), 0);
}


TEST(LList, FreePass)
{
  LinkedList* list = get_list();

  EXPECT_EQ(get_size(list), 0);

  add_person_begin(list, "Person1");
  add_person_begin(list, "Person2");
  add_person_begin(list, "Person3");

  EXPECT_EQ(get_size(list), 3);
  EXPECT_NE(list, nullptr);

  free_list(&list);

  EXPECT_EQ(get_size(list), 0);
  EXPECT_EQ(list, nullptr);
}


int main()
{
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
