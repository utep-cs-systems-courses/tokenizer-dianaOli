#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"


//check for a space or tab space
int space_char(char c){
  return (c == ' ' || c == '\t');
}

//check that char is not a  space, tab, or null
int non_space_char(char c){
  return (c != ' ' && c != '\t' && c != '\0');
}


//find the start of the next word/"token"
char *token_start(char *str){
  while(space_char(*str) && *str != '\0')
    str++;
  return str;
}


//finds the end of the current word/"token"
char *token_terminator(char *token){
  while(non_space_char(*token) && *token != '\0')
    token++;
  return token;
}


//counts tokens in the given string 
int count_tokens(char *str){
  int count = 0;
  char *start = token_start(str);
  while(*start != '\0'){
    start = token_terminator(start);
    start = token_start(start);
    count++;
  }
  return count;
}


//inStr pointer to the starrt of substring
//len length of substring
char *copy_str(char *inStr, short len){

  //allocates memory  to create new str outStr that can hold a null terminator 
  char *outStr = malloc((len+1) * sizeof(char));
  //strcpy ensures no more then "len" chars are copied 
  strncpy(outStr, inStr, len);
  //teriminates new string w. null 
  outStr[len] = '\0';
  //reurn pointer to newly created str
  return outStr;
}


//function breaks down the string given by the user into tokens
//char** tokens: tokens is a pointer to the first element of an array of strings.
//tokens[i]: Each tokens[i] is a pointer to the i-th string in the array.
char **tokenize(char* str){
  //determine token count and store into token_count
  int token_count = count_tokens(str);
  //array of pointer ,allocate memory and store all tokens along with they "null" terminator 
  char **tokens = malloc((token_count + 1)* sizeof(char*));
  char *start = str;
  char *end;

  //iterating and identifying start and end of token
  for(int i = 0; i < token_count; i++){
    start = token_start(start);
    end = token_terminator(start);
    //copy  the new token exactly as given
    tokens[i] = copy_str(start, end - start);
    //u[pdate start to the end of the current token for next iteration 
    start = end;
    
  }
  //add a null pointer to the end of the token array
  tokens[token_count] = NULL;
  return tokens;
}

//prints the words/"tokens"
void print_tokens(char **tokens){
  for(int i = 0; tokens[i] != NULL; i++){
    printf("%s\n", tokens[i]);
  }
}


//frees the memory allocated to store the tokens 
void free_tokens(char **tokens){
  for(int i = 0; tokens[i] != NULL; i++){
    free(tokens[i]);
  }
  free(tokens);
}


			 
