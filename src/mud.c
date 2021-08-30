#include <stdio.h>
#include <stdlib.h>

#include "ll.h"


void print_options()
{
    puts("---------- OPTIONS ----------------");
    puts("1. Add Person Front");
    puts("2. Add Person End");
    puts("3. Add Person at Index");
    puts("4. Remove Person Front");
    puts("5. Remove Person End");
    puts("6. Remove Person at Index");
    puts("7. Print List");
    puts("8. Print Options");
    puts("9. Quit ");
    puts("-----------------------------------");
}


/*
Entrypoint.
*/
int main()
{
  // The global holder/reference point for all list nodes
  LinkedList* list = get_list();

  int done = 0;
  char option;

  print_options();

  while(!done)
  {
      puts("Enter your choice:");
      scanf(" %c", &option);
      switch(option)
      {
          case '1': // Add Person Front
          {
              char v[120];
              puts("Enter person name:");
              scanf("%s", v);
              add_person_begin(list, v);
              break;
          }
          case '2': // Add Person End
          {
              char v[120];
              puts("Enter person name:");
              scanf("%s", v);
              add_person_end(list, v);
              break;
          }
          case '3': // Add Person at Index
          {
              char v[120];
              int idx;
              puts("Enter person name:");
              scanf("%s", v);
              puts("Enter index:");
              scanf("%d", idx);
              add_person_index(list, v, idx);
              break;
          }
          case '4': // Remove Person Front
          {
              remove_before(list);
              break;
          }
          case '5': // Remove Person End
          {
              remove_after(list);
              break;
          }
          case '6': // Remove Person at Index
          {
              int idx;
              puts("Enter index:");
              scanf("%d", idx);
              remove_person_index(list, idx);
              break;
          }
          case '7': // Print List
          {
              print_list(list);
              break;
          }
          case '8': // Print Options
          {
              print_options();
              break;
          }
          case '9': // Quit
          {
              done = 1;
              break;
          }
          default:
          {
              printf("Cannot interpret command '%c' - quitting\n", option);
              done = 1;
          }
      }
  }
  free_list(&list);
  puts("Goodbye.");

  return 0;
}
