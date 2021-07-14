#include <stdio.h>
#include "ll.h"


/*
Entrypoint.
*/
int main()
{
  // The global holder/reference point for all list nodes
  Person* list = NULL;
  
  add_person_begin(&list, "Peter");
  add_person_end(&list, "Luke");

  remove_person_index(&list, 10);
  
  print_list(list);
  
  free_list(&list);
  
  return 0;
}
