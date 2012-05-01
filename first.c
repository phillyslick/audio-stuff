#include <stdio.h> /* header file */
int main (int argc, char const *argv[])
{
  int a,b,c;
  printf("\nPlease Enter A Number: ");
  scanf("%d", &a);
  printf(" Please Enter A Second Number: ");
  scanf("%d", &b);
  c=a+b;
  printf("%d + %d = %d \n", a,b,c);
  return 0; //function returns 0 (ok)
}