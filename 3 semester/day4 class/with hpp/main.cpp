#include <iostream>
#include "class_Set.hpp"

int main() {
  
  /*Здесь вызывается специальный конструктор*/
  Set A;

  /*Применение конструктора копирования*/
  Set CopyA(A);

  return 0;
}