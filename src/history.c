#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"



//This method initializes the linked list for history
List *init_history()
{
  //allocate memory for new_list(pointer to the newly allocted memory)
  List *new_list = malloc(sizeof(List));
  if (new_list == NULL) return NULL;  // check if malloc succeeded
  new_list->root = NULL;
  return new_list;
}




//This method adds a new item to the linked list
void add_history(List *list, char *str)
{
  if (list == NULL || str == NULL) return;  // check if list and string are valid
  Item *new_item = malloc(sizeof(Item));
  if (new_item == NULL) return;  // check if malloc succeeded
  
  short len = str_len(str);
  new_item->str = copy_str(str, len);
  //next pointer of new_item set  to point to null
  new_item->next = NULL;

  if (list->root == NULL) {
    new_item->id = 1;
    list->root = new_item;
  }
  else {
    Item *curr_item = list->root;
    while(curr_item->next) {
      curr_item = curr_item->next;
    }
    new_item->id = curr_item->id + 1;
    curr_item->next = new_item;  // adds new node to end of linked list
  }
}

//this method returns the string at requested node
char *get_history(List *list, int id)
{
  if(list == NULL) return NULL;  // check if list is valid
  Item *curr_item = list->root;
  while(curr_item && (curr_item->id != id)){
    curr_item = curr_item->next;
  }
  return (curr_item && (curr_item->id == id)) ? curr_item->str : NULL;
}

//This method prints out the ids and strings of all elements in the linked list
void print_history(List *list)
{
  if(list == NULL) return;  // check if list is valid
  Item *curr_item = list->root;
  while(curr_item){
    printf("%d. %s\n", curr_item->id, curr_item->str);
    curr_item = curr_item->next;
  }
}



//This method frees the nodes and list from memory
void free_history(List *list)
{

  if(list == NULL) return;  // check if list is valid
  Item *current_item = list->root;
  while(current_item){
    Item *next_item = current_item->next;
    free(current_item->str);  // free the string
    free(current_item);  // free the item
    current_item = next_item;
  }
  free(list);
}
