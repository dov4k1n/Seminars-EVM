#include <iostream>

int main() {
  int a, b, c;

  a = 48;
  for (int b = 1; b < 7; b++) {
    c = 7-b;
    if (2*a*b + b*c + c == 273 && a*b + b*c - a*c - b == -70) {
      printf("(%d, %d, %d)", a, b, c);
      break;
    } 
  }

  a = 6;
  for (int b = 1; b < 49; b++) {
    c = 49-b;
    if (2*a*b + b*c + c == 273 && a*b + b*c - a*c - b == -70) {
      printf("(%d, %d, %d)\n", a, b, c);
      break;
    } 
  }

  return 0;
}