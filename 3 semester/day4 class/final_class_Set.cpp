#include <iostream>

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
    Set(std::size_t count, int manual) {
      if (count) {
        set = new int[count];
        size = count;
      } else {
        set = nullptr;
        size = 0;
      }
    }
    /*Специальный конструктор, конец*/

    /*Конструктор копирования, начало*/
    Set(const Set& other) :
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

    /*Метод для добавления элемента в конец массива, начало*/
    void PushBack(const int& input) {
      size++;
      set[size] = input;
    }
    /*Метод для добавления элемента в конец массива, конец*/

    /*Методы для чтения и записи, начало*/
    int operator[](std::size_t index) const { return set[index]; } // reading element set[index]
    int& operator[](std::size_t index) { return set[index]; } // writing element set[index]
    std::size_t Size() const { return size; } // reading Set_size
    std::size_t& Size() { return size; } // writing Set_size
    /*Методы для чтения и записи, конец*/

    /*Метод определения принадлежности элемента множеству, начало*/
    bool IsSetMember(const int& value) const {
        for (int i = 0; i < size; i++) {
          if (set[i] == value)
            return true;
        }
        return false;
    }
    /*Метод определения принадлежности элемента множеству, конец*/

    /*Сравнение множеств, начало*/
    /*Сравнение <=, начало*/
    bool operator<=(const Set& other) const {
      int i, j, flag;
      for (i = 0; i < size; i++) {
        flag = 0; 
        for (j = 0; j < other.size; j++) {
            if (set[i] == other[j]) {
              flag = 1;
              break;
            }
        }
        if (flag == 0)
          return false;
      }
      return true;
    }
    /*Сравнение <=, конец*/

    /*Сравнение >=, начало*/
    bool operator>=(const Set& other) const {
      if (other <= *this)
        return true;
      return false;
    }
    /*Сравнение >=, конец*/

    /*Сравнение ==, начало*/
    bool operator==(const Set& other) const {
      if (*this <= other && other <= *this)
        return true;
      return false;
    }
    /*Сравнение ==, конец*/
    
    /*Сравнение !=, начало*/
    bool operator!=(const Set& other) const {
      if (*this == other)
        return false;
      return true;
    }
    /*Сравнение !=, конец*/

    /*Сравнение <, начало*/
    bool operator<(const Set& other) const {
      if (*this <= other && *this != other)
        return true;
      return false;
    }
    /*Сравнение <, конец*/

    /*Сравнение >, начало*/
    bool operator>(const Set& other) const {
      if (other <= *this && other != *this)
        return true;
      return false;
    }
    /*Сравнение >, конец*/
    /*Перегрузка операторов, конец*/

    /*Операции над множествами, начало*/
    /*Копирующее присваивание =, начало*/
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
      }
      return *this;
    }
    /*Копирующее присваивание =, конец*/

    /*Объединение множеств без присваивания, начало*/
    Set operator|(const Set& other) const {
      Set NewSet = *this;
      for (int i = 0; i < other.Size(); i++) {
        NewSet.PushBack(other[i]);
      }
      return NewSet;
    }
    /*Объединение множеств без присваивания, конец*/

    /*Объединение множеств с присваиванием, начало*/
    Set& operator|=(const Set& other) {
      for (int i = 0; i < other.Size(); i++) {
        PushBack(other[i]);
      }
      return *this;
    }
    /*Объединение множеств с присваиванием, конец*/

    /*Пересечение множеств без присваивания, начало*/
    Set operator&(const Set& other) const { 
      Set NewSet = *this;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < other.Size(); j++) {
          if (set[i] == other[j]) {
            NewSet.PushBack(other[j]);
            break;
          }
        }
      }
      return NewSet;
    }
    /*Пересечение множеств без присваивания, конец*/

    /*Пересечение множеств с присваиванием, начало*/
    Set& operator&(const Set& other) {
      *this = *this & other;
      return *this;
    }
    /*Пересечение множеств с присваиванием, конец*/

    /*Разность множеств без присваивания, начало*/
    Set operator/(const Set& other) const {
      Set NewSet;
      Set InterSet = *this & other;
      int i, j, flag;
      for (i = 0; i < size; i++) {
        flag = 0;
        for (j = 0; j < InterSet.Size(); j++) {
          if (set[i] == InterSet[j]) {
            flag = 1;
            break;
          }
        }
        if (flag != 1)
          NewSet.PushBack(set[i]);
      }
      return NewSet;
    }
    /*Разность множеств без присваивания, конец*/

    /*Разность множеств с присваиванием, начало*/
    Set& operator/=(const Set& other) {
      *this = *this / other;
      return *this;
    }
    /*Разность множеств с присваиванием, конец*/

    /*Симметрическая разность множеств без присваивания, начало*/
    Set operator^(const Set& other) const {
      Set UnionSet = *this | other;
      Set InterSet = *this & other;
      return UnionSet / InterSet;
    }
    /*Симметрическая разность множеств без присваивания, конец*/

    /*Симметрическая разность множеств с присваиванием, начало*/
    Set operator^=(const Set& other) {
      *this = *this ^ other;
      return *this;
    }
    /*Симметрическая разность множеств с присваиванием, конец*/
    /*Операции над множествами, конец*/

    /*Деструктор, начало*/
    ~Set() {
      if (set)
        delete[] set;
    }
    /*Деструктор, конец*/
};

/*Вывод, начало*/
std::ostream& operator<<(std::ostream& out, const Set& set) {
  for (int i = 0; i < set.Size(); i++) {
    out << " " << set[i];
  }
  return out;
}
/*Вывод, конец*/

/*Ввод, начало*/
std::istream& operator>>(std::istream& in, Set& set) {
  set.Size()++;
  in >> set[set.Size()] ; // ~ pushback
  return in;
}
/*Ввод, конец*/

double my_fun() {
  return 0;
}

int main() {
  // при использовании класса, нужно передавать как аргумент int* set_A = new int[size]
  int* b = new int[3];
  for (int i = 0; i < 3; i++) {
    b[i] = i;
  }
  Set a = b;
  std::cout << a;
  delete[] b;
  return 0;
}