#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Keeps track of the number of elements in the list
static unsigned int number = 0;


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
Traverse the existing nodes looking for the end of the list
Return a pointer to the last element in the list (Item that points to NULL)
*/
Person* traverse_till_null(Person* list)
{
  Person* n = list;

  while(1)
  {
    if (n->next_person == NULL)
      break;
      
//    printf("traversing...\n");

    n = n->next_person;
  }
  
  return n;
}


/*
#######################################
##########                   ##########
##########  PRINT FUNCTIONS  ##########
##########                   ##########
#######################################
*/


/*
Print person information (The node's payload)
*/
void print_person(Person* person)
{
  printf("%s : %d ", person->name, person->idx);
  
  if(person->next_person != NULL)
    printf("-> %s : %d ", person->next_person->name, person->next_person->idx);
  else
      printf("-> NULL");
    
  printf("\n");
}


/*
Print the pointer information (addresses) associated with the person(node)
*/
void print_person_pointer(Person* person)
{
  printf("(Current:%p)(Next:%p))\n", person, person->next_person);
}


/*
Print the list contents with barriers (makes the list contents easier to read),
and pointers from each node
(print the memory contents what the current node points to)
*/
void print_list(Person* list)
{
  Person* n = list;
  
  if (n == NULL)
  {
    puts("No contents in list.");
    return;
  }

  printf(number == 1 ? "\n%d individual\n" : "\n%d individuals\n", number);
  
  printf("---------------- ### BEGIN PRINT LIST ### ----------------\n");
  while(1)
  {
    if (n == NULL)
      break;

    // Print person info and divider(if necessary)
    print_person(n);
    
    if(n->next_person != NULL)
      printf("----------------------------------------------------------\n");

    n = n->next_person;
  }
  printf("----------------- ### END PRINT LIST ### -----------------\n\n");
}


/*
#######################################
##########                   ##########
##########   ADD FUNCTIONS   ##########
##########                   ##########
#######################################
*/

/*
Add a person to the start of the list
*/
void add_person_begin(Person** list, const char* name)
{
  if(number == 0)
  {
    strcpy((*list)->name, name);
    (*list)->idx = number;
    (*list)->next_person = NULL;
    
    ++number;
    return;
  }
  
  // Carve out space on the heap for the new person's node
  Person* new_person = (Person*) malloc(sizeof(Person));
  Person* holder = (*list);

  strcpy(new_person->name, name);
  new_person->idx = number;

  new_person->next_person = holder;
  (*list) = new_person;

  ++number;
}


/*
Add a person to the end of the list
*/
void add_person_end(Person** list, const char* name)
{  
  if(number == 0)
  {
    (*list) = (Person*)malloc(sizeof(Person));
    strcpy((*list)->name, name);
    (*list)->idx = number;
    (*list)->next_person = NULL;
    
    ++number;
    return;
  }
  
  // Carve out space on the heap for the new person's node
  Person* new_person = (Person*) malloc(sizeof(Person));
  Person* last_person = traverse_till_null((*list));

  strcpy(new_person->name, name);
  new_person->idx = number;
  new_person->next_person = NULL;

  // Point the previous list node to the new node
  last_person->next_person = new_person;

  ++number;
}


/*
#######################################
##########                   ##########
########## REMOVAL FUNCTIONS ##########
##########                   ##########
#######################################
*/


/*
*/
void remove_before(Person** p_list)
{
  Person* list = *p_list;
  
  if(list == NULL)
  {
    printf("Cannot remove from an empty list.\n");
    return;
  }
  
  printf("Removing Before.\n");
  Person* next = list->next_person;
  
  free(list);
  list = NULL;
  
  *p_list = next;
  
  --number;
}


/*
*/
void remove_after(Person** p_list)
{
  Person* list = *p_list;
  
  if(list == NULL)
  {
    printf("Cannot remove from an empty list.\n");
    return;
  }
  
  Person* ptr = list;
  
  while(1)
  {
    if(ptr == NULL || ptr->next_person == NULL)
    {
      printf("WARNING: Cannot locate the current pointer's neighbor. Returning.\n");
      return;
    }

    if(ptr->next_person->next_person == NULL)
      break;

    ptr = ptr->next_person;
  }
  
  printf("Removing After.\n");

  free(ptr->next_person);
  ptr->next_person = NULL;

  --number;
}


/*
Clear out the list, and free the nodes.
Set the number to 0 and leave the list pointer
in a NULL state.
*/
void free_list(Person** list)
{
  Person* n = *list;
  Person* nxt;
  
  if(number == 0)
  {
    printf("List already empty.\n");
    *list = NULL;
    return;
  }
  
  while(1)
  {
    if (n == NULL)
      break;
      
    nxt = n->next_person;
    free(n);
    n = nxt;
  }
  
  number = 0;
  *list = NULL;
  printf("Emptied List.\n");
}


/*
Entrypoint.
*/
int main()
{
  // The global holder/reference point for all list nodes
  Person* list = NULL;
  
  add_person_end(&list, "Paul");
  add_person_begin(&list, "Peter");
  add_person_end(&list, "John");
  
  print_list(list);
  
  remove_after(&list);
  remove_after(&list);
  
  add_person_end(&list, "Paul");
  
  print_list(list);
  
  free_list(&list);
  
  return 0;
}

