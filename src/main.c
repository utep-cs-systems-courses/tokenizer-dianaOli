#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define MAX 100

//a function called str_len that takes a string and returns a number
short str_len(char *str);

//a function called history_ui that needs a history list
void history_ui(List *history);

//function to compare two strings. It tells us if the two strings are the same or not
int custom_strcmp(char *str1, char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }

  /// If it finds a place where the two strings are different, it tells us that the strings are not the same
  return *(unsigned char*)str1 - *(unsigned char*)str2;
}


// function is used to find the position of a particular character in a string
int custom_strcspn(char *str, char *reject) {
  int len = 0;
  while (*str) {
    if (*str == *reject)
      break;
    str++;
    len++;
  }
  return len;
}



int main()
{
  List *history = init_history(); //creating an empty history list
  while(1){
    printf("Enter a string to tokenize\n");
    printf("Or Enter 'h' to see history 'q' to quit\n");
    printf("Input: ");
    
    char buf[MAX];
    if(fgets(buf, MAX, stdin) == NULL) {
      printf("Error reading input\n");
      continue;
    }

    buf[custom_strcspn(buf, "\n")] = 0;
    if(custom_strcmp(buf, "q") == 0) {
      free_history(history);
      break;
    }

    else if(custom_strcmp(buf, "") == 0){
      printf("No input given! Please try again.\n\n");
      continue;
    }

    else if(custom_strcmp(buf, "h") == 0)
      history_ui(history);
    else{
      char *s = copy_str(buf, str_len(buf));
      add_history(history, s);
      char **t = tokenize(buf);
      print_tokens(t);
      printf("\n");
      free_tokens(t);
      printf("Tokenized!\n");
    }

  }
  printf("Bye :)\n");
  return 0;

}

//function gives us the length of a string, or the number of characters in it
short str_len(char *str)
{
  char *p = str;
  while(*p != '\0'){
    p++;
  }
  return (p-str);
}

void history_ui(List *history)
{
  print_history(history);
  printf("Enter number to tokenize?\n>");
  char response[MAX];
  if(fgets(response, MAX, stdin) == NULL) {
    printf("Error reading input\n");
    return;
 }

  
  response[custom_strcspn(response, "\n")] = 0;
  int id = atoi(response);
  if(id != 0){
    char *str = get_history(history, id);
    if(str){
      char **t = tokenize(str);
      print_tokens(t);
      printf("\n");
      free_tokens(t);
      return;
    }
    else{
      printf("\nInvalid id");
    }
  }
  else{
    printf("\nInvalid input");
    return;
  }
}
