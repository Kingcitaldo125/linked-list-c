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
###########################################
##########                       ##########
##########  TRAVERSAL FUNCTIONS  ##########
##########                       ##########
###########################################
*/


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

    n = n->next_person;
  }
  
  return n;
}

/*
Traverse the existing nodes looking for the end of the list
Return a pointer to the last element in the list (Item that points to NULL)
*/
Person* traverse_till_index(Person* list, const int index)
{
  Person* n = list;

  if(index == 0)
  {
    printf("TTI: Start of list.\n");
    return n;
  }

  int idx = 0;
  while(1)
  {
    if (n->next_person == NULL)
    {
      printf("Reached end of the list. Returning.\n");
      break;
    }

    if (idx == index - 1)
    {
      break;
    }

    n = n->next_person;
    ++idx;
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
    if(*list == NULL)
      (*list) = (Person*) malloc(sizeof(Person));

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
  new_person->idx = 0;

  new_person->next_person = holder;
  (*list) = new_person;

  // Update the upstream index numbers
  Person* p = *list;
  while(1)
  {
    if(p->next_person == NULL)
      break;

    p = p->next_person;
    ++p->idx;
  }

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
  
  // Update index of the new person
  new_person->idx = last_person->idx + 1;
  
  new_person->next_person = NULL;

  // Point the previous list node to the new node
  last_person->next_person = new_person;

  ++number;
}


/*
Add a new node to a particular index.
*/
void add_person_index(Person** list, const char* name, const unsigned int index)
{  
  if(number == 0 && index != 0)
  {
    printf("Index does not line up with number of elements. Returning\n");
    return;
  }

  if(index == 0)
  {
    add_person_begin(list, name);
    return;
  }
  else if(index == number - 1)
  {
    add_person_end(list, name);
    return;
  }
  
  // Carve out space on the heap for the new person's node
  Person* new_person = (Person*) malloc(sizeof(Person));
  Person* last_person = traverse_till_index((*list), index);

  printf("last_person:");
  print_person(last_person);

  strcpy(new_person->name, name);
  
  // Update index of the new person
  new_person->idx = index;

  // rewire the pointers
  printf("Rewiring\n");
  new_person->next_person = last_person->next_person == NULL ? NULL : last_person->next_person;
  last_person->next_person = new_person;

  // Handle incrementing
  Person* p = traverse_till_null(*list);

  if(p->next_person == NULL)
    return;

  p = p->next_person;
  ++p->idx;

  printf("Incrementing latter\n");
  while(1)
  {
    if(p->next_person == NULL)
      break;

    ++p->idx;
    p = p->next_person;
  }

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
  
  // Update the upstream index numbers
  Person* p = *p_list;
  --p->idx;
  while(1)
  {
    if(p->next_person == NULL)
      break;

    p = p->next_person;
    --p->idx;
  }
  
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
  
  add_person_begin(&list, "Peter");
  add_person_end(&list, "James");
  add_person_index(&list, "Paul", 0);
  
  print_list(list);
  
  free_list(&list);
  
  return 0;
}

