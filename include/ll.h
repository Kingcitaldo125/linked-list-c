#ifndef MAIN_H
#define MAIN_H

/*
The Node structure for the person - basic linked list info
*/
typedef struct person
{
  char name[120];
  int idx;
  struct person* next_person;
} Person;

// ---------------------------------
// ---------------------------------
// ----- Function Declarations -----
// ---------------------------------
// ---------------------------------

Person* traverse_till_null(Person* list);
Person* traverse_till_index(Person* list, const int index);

void print_person(Person* person);
void print_person_pointer(Person* person);
void print_list(Person* list);

int add_person_begin(Person** list, const char* name);
int add_person_end(Person** list, const char* name);
int add_person_index(Person** list, const char* name, const int index);

int remove_before(Person** p_list);
int remove_after(Person** p_list);
int remove_person_index(Person** list, const int index);

int free_list(Person** list);

#endif
