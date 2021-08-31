#include <stdio.h>
#include <stdlib.h>

#include "ll.h"


/*
Entrypoint.
*/
int main()
{
  LinkedList* list = get_list();
  
  printf("add begin\n");
  add_person_begin(list, "Peter");
  printf("add end\n");
  add_person_end(list, "Luke");
  
  print_list(list);

  printf("Size: %d\n", get_size(list));

  remove_person_index(list, 0);
  
  free_list(&list);

  printf("Size: %d\n", get_size(list));

  return 0;
}
