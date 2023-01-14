#include <iostream>
#include "class_Set.hpp"

class Set {
  private:
    int* set;
    std::size_t size;

  public:
    /*Специальный конструктор, начало*/
    Set::Set() :
      set(nullptr),
      size(0)
    { }

    Set::Set(int* set, std::size_t size) :
      set(set), // при использовании класса, нужно передавать как аргумент int* set_A = new int[size]
      size(size)
    { }
    /*Специальный конструктор, конец*/

    /*Конструктор копирования, начало*/
    Set::Set(const Set& other) :
      set(nullptr),
      size(other.size)
    {
      if (size > 0) {
        set = new int[size];
      }

      for (int i = 0; i < size; i++) {
        set[i] = other.set[i];
      }
    }
    /*Конструктор копирования, конец*/

    /*Метод для добавления элементта в конец массива, начало*/
    void Set::PushBack(const int& input) {
      size++;
      set[size] = input;
    }
    /*Метод для добавления элементта в конец массива, конец*/

    /*Методы для чтения и записи, начало*/
    int* Set::GetSet() const { return set; } // reading Set
    std::size_t Set::Size() const { return size; } // reading Set_size
    std::size_t& Set::Size() { return size; } // writing Set_size
    /*Методы для чтения и записи, конец*/

    /*Перегрузка операторов, начало*/

    /*Печать, начало*/
    std::ostream& operator<<(std::ostream& ostr, const std::vector<int>& set) {
      for (auto &i : set) {
          ostr << " " << i;
      }
      return ostr;
    }
    /*Печать, конец*/

    /*Присваивание, начало*/

    /*  
    Операция для копирования объекта из другого объекта того же типа принимает
    константную ссылку на объект того же типа и возвращает обычную ссылку на сам
    объект (для того, чтобы можно было написать A = B = C).
    */

    Set& operator=(const Set& other) {
      if (set)
        delete[] set;

      set = nullptr;
      size = other.size;

      if (other.set) {
        set = new int[size];
        for (int i = 0; i < size; i++) {
          set[i] = other.set[i];
        }

      return *this;
    }

    
    /*Присваивание, конец*/

    /*Перегрузка операторов, конец*/

    /*Деструктор, начало*/
    ~Set() {
      if (set)
        delete[] set;
    }
    /*Деструктор, конец*/
};