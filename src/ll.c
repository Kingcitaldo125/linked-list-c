#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"

/*
###########################################
##########                       ##########
##########  FACTORY FUNCTION     ##########
##########                       ##########
###########################################
*/

/*
Factory function to instantiate a new LinkedList.
Should be cleaned up with the 'free()' function after it's done being used.
*/
LinkedList* get_list()
{
  LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
  list->num_nodes = 0;
  return list;
}

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
Person* traverse_till_null(LinkedList* list)
{
  if(get_size(list) == 0)
  {
    printf("Cannot traverse an empty list.\n");
    return NULL;
  }

  Person* n = list->node;

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
Person* traverse_till_index(LinkedList* list, const int index)
{
  if(get_size(list) == 0)
  {
    printf("Cannot traverse an empty list.\n");
    return NULL;
  }

  Person* n = list->node;

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

    if (idx == index)
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
##########  SIZE FUNCTIONS   ##########
##########                   ##########
#######################################
*/


/*
Return the size of the llist (return num_nodes)
*/
unsigned int get_size(LinkedList* list)
{
  return list == NULL ? 0 : list->num_nodes;
}


/*
Return the size of the llist (return get_size() - see above)
*/
unsigned int get_length(LinkedList* list)
{
  return get_size(list);
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
Print the pointer information (addresses) associated with the person(node).
Mostly for debugging.
*/
void print_person_pointer(Person* person)
{
  printf("(Current:%p)(Next:%p))\n", person, person->next_person);
}


/*
Print the list contents with barriers (makes the list contents easier to read),
and pointers from each node
(print the memory contents what the current node points to).
*/
void print_list(LinkedList* list)
{
  Person* n = list->node;
  
  if (n == NULL)
  {
    puts("No contents in list.");
    return;
  }

  printf(list->num_nodes == 1 ? "\n%d individual\n" : "\n%d individuals\n", list->num_nodes);
  
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
unsigned int add_person_begin(LinkedList* list, const char* name)
{
  if(list == NULL)
  {
    printf("Cannot add to a NULL list\n");
    return -1;
  }

  // Create/allocate the base list if we have not already done so
  printf("check_nodes\n");
  if(list->num_nodes == 0)
  {
    printf("malloc\n");
    list->node = (Person*) malloc(sizeof(Person));

    printf("copy\n");
    strcpy(list->node->name, name);
    list->node->idx = list->num_nodes;
    list->node->next_person = NULL;

    printf("increment\n");
    ++list->num_nodes;
    return list->num_nodes;
  }
  
  // Carve out space on the heap for the new person's node
  Person* new_person = (Person*) malloc(sizeof(Person));
  Person* holder = list->node;

  strcpy(new_person->name, name);
  new_person->idx = 0;

  new_person->next_person = holder;
  list->node = new_person;

  // Update the upstream index numbers
  Person* p = list->node;
  while(1)
  {
    if(p->next_person == NULL)
      break;

    p = p->next_person;
    ++p->idx;
  }

  ++list->num_nodes;

  return list->num_nodes;
}


/*
Add a person to the end of the list
*/
unsigned int add_person_end(LinkedList* list, const char* name)
{  
  if(list == NULL)
  {
    printf("Cannot add to a NULL list\n");
    return -1;
  }

  if(list->num_nodes == 0)
  {
    printf("malloc\n");
    list->node = (Person*) malloc(sizeof(Person));

    printf("copy\n");
    strcpy(list->node->name, name);
    list->node->idx = list->num_nodes;
    list->node->next_person = NULL;

    printf("increment\n");
    ++list->num_nodes;
    return list->num_nodes;
  }
  
  // Carve out space on the heap for the new person's node
  Person* new_person = (Person*) malloc(sizeof(Person));
  Person* last_person = traverse_till_null(list);

  strcpy(new_person->name, name);
  
  // Update index of the new person
  new_person->idx = last_person->idx + 1;
  
  new_person->next_person = NULL;

  // Point the previous list node to the new node
  last_person->next_person = new_person;

  ++list->num_nodes;
  return list->num_nodes;
}


/*
Add a new node to a particular index.
*/
unsigned int add_person_index(LinkedList* list, const char* name, const int index)
{
  if(list == NULL)
  {
    printf("Cannot add to a NULL list\n");
    return -1;
  }

  // Handle corner case
  if(list->num_nodes == 0 && index != 0)
  {
    printf("Index does not line up with number of elements. Returning\n");
    return -1;
  }
  
  // Handle corner cases
  if(index < 0)
  {
    printf("Index needs to be >= 0. Returning\n");
    return -1;
  }
  else if(index > list->num_nodes)
  {
    printf("Cannot add past the end of the list.\n");
    return -1;
  }
  else if(index == 0)
  {
    return add_person_begin(list, name);
  }
  else if(index == list->num_nodes)
  {
    return add_person_end(list, name);
  }
  
  // Carve out space on the heap for the new person's node
  Person* new_person = (Person*) malloc(sizeof(Person));
  Person* last_person = traverse_till_index(list, index - 1);

  strcpy(new_person->name, name);
  
  // Update index of the new person
  new_person->idx = index;

  // rewire the pointers
  new_person->next_person = last_person->next_person;
  last_person->next_person = new_person;

  // Handle incrementing the elements after the one we inserted into
  Person* p = traverse_till_index(list, index);
  while(1)
  {
    if(p->next_person == NULL)
      break;

    p = p->next_person;
    ++p->idx;
  }

  ++list->num_nodes;
  return list->num_nodes;
}


/*
#######################################
##########                   ##########
########## REMOVAL FUNCTIONS ##########
##########                   ##########
#######################################
*/


/*
Remove the first element in the list.
*/
unsigned int remove_before(LinkedList* list)
{  
  if(list == NULL)
  {
    printf("Cannot remove from a NULL list.\n");
    return -1;
  }

  if(list->num_nodes == 0)
  {
    printf("Cannot remove from a empty list.\n");
    return -1;
  }
  
  printf("Removing Before.\n");
  Person* next = list->node->next_person;
  free(list->node);
  list->node = NULL;
  
  list->node = next;
  
  // Update the upstream index numbers
  if(NULL != next)
  {
    Person* p = list->node;
    --p->idx;
    while(1)
    {
      if(p->next_person == NULL)
        break;

      p = p->next_person;
      --p->idx;
    }
  }
  
  --list->num_nodes;
  return list->num_nodes;
}


/*
Remove the last element in the list.
*/
unsigned int remove_after(LinkedList* list)
{
  if(list == NULL)
  {
    printf("Cannot remove from a NULL list.\n");
    return -1;
  }

  if(list->num_nodes == 0)
  {
    printf("Cannot remove from a empty list.\n");
    return -1;
  }
  
  Person* ptr = list->node;
  
  while(1)
  {
    if(ptr == NULL || ptr->next_person == NULL)
    {
      printf("WARNING: Cannot locate the current pointer's neighbor. Returning.\n");
      return -1;
    }

    if(ptr->next_person->next_person == NULL)
      break;

    ptr = ptr->next_person;
  }
  
  printf("Removing After.\n");

  free(ptr->next_person);
  ptr->next_person = NULL;

  --list->num_nodes;
  return list->num_nodes;
}


/*
Remove a node at a particular index.
*/
unsigned int remove_person_index(LinkedList* list, const int index)
{
  if(list == NULL)
  {
    printf("Cannot remove from a NULL list.\n");
    return -1;
  }

  if(list->num_nodes == 0)
  {
    printf("Cannot remove from a empty list.\n");
    return -1;
  }

  // Handle corner case
  if(index != 0)
  {
    printf("Index does not line up with number of elements. Returning\n");
    return -1;
  }
  
  // Handle corner cases
  if(index < 0)
  {
    printf("Index needs to be >= 0. Returning\n");
    return -1;
  }
  else if(index > list->num_nodes)
  {
    printf("Cannot remove past the end of the list.\n");
    return -1;
  }
  else if(index == 0)
  {
    return remove_before(list);
  }
  else if(index == list->num_nodes)
  {
    return remove_after(list);
  }
  
  // Find the person before the person at the index we want to remove
  // Index should be  N-1 >= idx >= 1
  Person* last_person = traverse_till_index(list, index - 1);
  Person* current_person = last_person->next_person;

  // rewire the pointers
  last_person->next_person = current_person->next_person;

  free(current_person);
  current_person = NULL;

  // Handle decrementing the elements before the one we inserted into
  Person* p = traverse_till_index(list, index - 1);

  while(1)
  {
    if(p->next_person == NULL)
      break;

    p = p->next_person;
    --p->idx;
  }

  --list->num_nodes;
  return list->num_nodes;
}


/*
Clear out the list, and free the nodes.
Set the num_nodes to 0 and leave the list pointer
in a NULL state.
*/
int free_list(LinkedList** list)
{
  Person* n = (*list)->node;
  Person* nxt;
  
  if((*list) == NULL)
  {
    printf("List already empty(NULL).\n");
    return 1;
  }

  if((*list)->num_nodes == 0)
  {
    printf("List already empty. Setting to NULL.\n");
    (*list) = NULL;
    return 1;
  }
  
  while(1)
  {
    if (n == NULL)
      break;
      
    nxt = n->next_person;
    free(n);
    n = NULL;
    n = nxt;
  }
  
  (*list)->num_nodes = 0;
  free((*list));
  (*list) = NULL;
  printf("Emptied List.\n");
  return 0;
}
