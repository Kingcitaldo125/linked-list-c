#include <stdio.h>
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
  Person* list = NULL;
  int done = 0;
  int pass = 0;
  int option;

  print_options();

  while(!done)
  {
      puts("Enter your choice:");
      scanf("%d", &option);
      switch(option)
      {
          case 1: // Add Person Front
          {
              char v[120];
              puts("Enter person name:");
              scanf("%s", v);
              add_person_begin(&list, v);
              pass = 0;
              break;
          }
          case 2: // Add Person End
          {
              char v[120];
              puts("Enter person name:");
              scanf("%s", v);
              add_person_end(&list, v);
              pass = 0;
              break;
          }
          case 3: // Add Person at Index
          {
              char v[120];
              int idx;
              puts("Enter person name:");
              scanf("%s", v);
              puts("Enter index:");
              scanf("%d", &idx);
              add_person_index(&list, v, idx);
              pass = 0;
              break;
          }
          case 4: // Remove Person Front
          {
              remove_before(&list);
              pass = 0;
              break;
          }
          case 5: // Remove Person End
          {
              remove_after(&list);
              pass = 0;
              break;
          }
          case 6: // Remove Person at Index
          {
              int idx;
              puts("Enter index:");
              scanf("%d", &idx);
              remove_person_index(&list, idx);
              pass = 0;
              break;
          }
          case 7: // Print List
          {
              print_list(list);
              pass = 0;
              break;
          }
          case 8: // Print Options
          {
              print_options();
              pass = 0;
              break;
          }
          case 9: // Quit
          {
              done = 1;
              pass = 0;
              break;
          }
          default:
          {
              printf("Cannot interpret command '%d' - quitting\n", option);
              done = 1;
          }
      }
      ++pass;
      if(pass > 2)
        done = 1;
  }
  free_list(&list);
  puts("Goodbye.");

  return 0;
}
