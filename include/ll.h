#ifndef LL_H
#define LL_H

/*
The Node structure for the person - basic linked list info
*/
typedef struct person
{
  char name[120];
  int idx;
  struct person* next_person;
} Person;

/*
The linked list struct
*/
typedef struct list
{
  unsigned int num_nodes;
  Person* node;
} LinkedList;

// ---------------------------------
// ---------------------------------
// ----- Function Declarations -----
// ---------------------------------
// ---------------------------------

LinkedList* get_list();

Person* traverse_till_null(LinkedList* list);
Person* traverse_till_index(LinkedList* list, const int index);

unsigned int get_size(LinkedList* list);
unsigned int get_length(LinkedList* list);

void print_person(Person* person);
void print_person_pointer(Person* person);
void print_list(LinkedList* list);

unsigned int add_person_begin(LinkedList* list, const char* name);
unsigned int add_person_end(LinkedList* list, const char* name);
unsigned int add_person_index(LinkedList* list, const char* name, const int index);

unsigned int remove_before(LinkedList* list);
unsigned int remove_after(LinkedList* list);
unsigned int remove_person_index(LinkedList* list, const int index);

Person* reverse_list(LinkedList** list);
int free_list(LinkedList** list);

#endif // LL_H
