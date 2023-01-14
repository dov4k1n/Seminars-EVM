#include <iostream>
#include <vector>

class Set {
  private:
    std::vector<int> set;
    std::size_t size;

  public:
    /*Специальный конструктор, начало*/
    Set(std::vector<int> set) :
      set(set),
      size(set.size())
    { }
    /*Специальный конструктор, конец*/

    /*Конструктор копирования, начало*/
    Set(const Set& other) {
      set = other.set;
      size = other.size;
    }
    /*Конструктор копирования, конец*/



/*
class Set {
  private:
    int* set;
    std::size_t size;

  public:
    /*Специальный конструктор, начало*/
    /*Set(int* set = nullptr, std::size_t size = 0) :
      set = new int[size], // при использовании класса, нужно передавать как аргумент int* set_A = new int[size]
      size(size)
    { }*/
    Set(int* set = nullptr, int choice = 0) :
      
      if (choice) {
        set = new int[count];
        size = count;
        std::cout << "builded1" << std::endl;
      }
     { }

     /*Метод для добавления элемента в конец массива, начало*/
    void PushBack(const int& input) {
      size++;
      set[size] = input;
    }
    /*Метод для добавления элемента в конец массива, конец*/

    /*Деструктор, начало*/
    ~Set() {
      if (set) {
        std::cout << "destructed" << std::endl;
        delete[] set;
      }
    }
    /*Деструктор, конец*/
};*/

int main() {
  // при использовании класса, нужно передавать как аргумент int* set_A = new int[size]
  Set a(1);

  /*
  int* b = new int[3];
  for (int i = 0; i < 3; i++) {
    b[i] = i;
  }
  Set a = b;
  std::cout << a;
  delete[] b;
  */

  return 0;
}