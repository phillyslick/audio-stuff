#include <stdio.h>

int main (int argc, char const *argv[])
{
  int int_tester;
  char char_tester;
  short short_tester;
  long long_tester;
  float float_tester;
  double double_tester;
  int the_answer;
  
  the_answer = sizeof(int_tester);  
  printf("The size of an int in bytes is: %d\n", the_answer);
  the_answer = sizeof(char_tester);  
  printf("The size of a char in bytes is: %d\n", the_answer);
  the_answer = sizeof(short_tester);  
  printf("The size of a short in bytes is: %d\n", the_answer);
  the_answer = sizeof(short_tester);  
  printf("The size of a long in bytes is: %d\n", the_answer);
  the_answer = sizeof(long_tester);  
  printf("The size of a float in bytes is: %d\n", the_answer);
  the_answer = sizeof(float_tester);  
  printf("The size of a double in bytes is: %d\n", the_answer);
       
  return 0;
}