#include <iostream>

class Set {
  private:
    int* data;
    std::size_t size;

  public:
    /*Специальный конструктор, начало*/
    Set(std::size_t size = 0):
      data(nullptr),
      size(size)
    {
      if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
          data[i] = 0;
        }
      }
    }
    /*Специальный конструктор, конец*/

    /*Деструктор, начало*/
    ~Set() {
      if (data) {
        // std::cout << "destruction began" << std::endl;
        delete[] data;
        // std::cout << "destructed" << std::endl;
      }
    }
    /*Деструктор, конец*/

    /*Методы для чтения и записи, начало*/
    int operator[](std::size_t index) const { return data[index]; } // reading element data[index]
    int& operator[](std::size_t index) { return data[index]; } // writing element data[index]
    std::size_t Size() const { return size; } // reading
    std::size_t& Size() { return size; } // writing
    /*Методы для чтения и записи, конец*/ 

    /*Конструктор копирования, начало*/
    Set(Set const& copy):
      size(copy.Size()),
      data(nullptr) 
    {
      if (size > 0) {
        data = new int[size];
      }

      for (int i = 0; i < size; i++) {
        data[i] = copy[i];
      }
    }
    /*Конструктор копирования, конец*/
    
    /*Вывод, начало*/
    friend std::ostream& operator<<(std::ostream& out, const Set& set) {
      for (int i = 0; i < set.Size(); i++) {
        out << set[i] << " ";
      }
      return out;
    }
    /*Вывод, конец*/

    /*Ввод, начало*/
    friend std::istream& operator>>(std::istream& in, Set& set) {
      int* tmp = new int[set.size + 1];

      for (int i = 0; i < set.size; i++) {
        tmp[i] = set.data[i];
      }

      in >> tmp[set.size];
      
      set.size++;
      
      if (set.data)
        delete[] set.data;
      
      set.data = new int[set.size];
      
      for (int i = 0; i < set.size; i++) {
        set.data[i] = tmp[i];
      }
      
      delete[] tmp;
      
      return in;
    }
    /*Ввод, конец*/

    /*Ввод 2, начало*/
    void PushBack(const int& value) {
      int* tmp = new int[size+1];
      for (int i = 0; i < size; i++) {
        tmp[i] = data[i];
      }
      tmp[size] = value;
      size++;
      if (data)
        delete[] data;
      data = new int[size];
      for (int i = 0; i < size; i++) {
        data[i] = tmp[i];
      }
      delete[] tmp;
      // data[size-1] = value; // data's size is not increased, so it throws error
    }
    /*Ввод 2, конец*/

    /*Метод определения принадлежности элемента множеству, начало*/
    bool IsSetMember(const int& value) const {
        for (int i = 0; i < size; i++) {
          if (data[i] == value)
            return true;
        }
        return false;
    }
    /*Метод определения принадлежности элемента множеству, конец*/

    /*Удаление элементов с заданным значением, начало*/
    void Erase(const int& value) {
      Set tmp;
      int nsize = 0;
      for (int i = 0; i < size; i++) {
        if (data[i] != value) {
          tmp.PushBack(data[i]);
          nsize++;
        }
      }
      size = nsize;
      if (data)
        delete[] data;
      data = new int[nsize];
      for (int i = 0; i < nsize; i++) {
        data[i] = tmp[i];
      }
    }
    /*Удаление элементов с заданным значением, конец*/

    /*Удаление повторов элемента с заданным значением, начало*/
    void MakeUnique(const int& value) {
      Set tmp;
      int nsize = 0;
      int flag = 1;
      for (int i = 0; i < size; i++) {
        if (data[i] != value) {
          tmp.PushBack(data[i]);
          nsize++;
        } else if (flag == 1) {
          tmp.PushBack(data[i]);
          nsize++;
          flag = 0;
        }
      }
      size = nsize;
      if (data)
        delete[] data;
      data = new int[nsize];
      for (int i = 0; i < nsize; i++) {
        data[i] = tmp[i];
      }
    }
    /*Удаление повторов элемента с заданным значением, конец*/

    /*Удаление повторений, начало*/
    void ClearReps() {
      int RepsCount = 0;
      for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
          if (data[j] == data[i]) {
            MakeUnique(data[i]);
            break;
          }
        }
      }
    }
    /*Удаление повторений, конец*/



    /*Сравнение множеств, начало ________________________*/
    /*Сравнение <=, начало*/
    bool operator<=(const Set& other) const {
      int i, j, flag;
      for (i = 0; i < size; i++) {
        flag = 0; 
        for (j = 0; j < other.Size(); j++) {
            if (data[i] == other[j]) {
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
    /*Сравнение множеств, конец ________________________*/



    /*Операции над множествами, начало ________________________*/
    /*Копирующее присваивание =, начало*/
    /*  
    Операция для копирования объекта из другого объекта того же типа принимает
    константную ссылку на объект того же типа и возвращает обычную ссылку на сам
    объект (для того, чтобы можно было написать A = B = C).
    */
    Set& operator=(const Set& other) {
      if (data)
        delete[] data;

      data = nullptr;
      size = other.Size();

      if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
          data[i] = other[i];
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
      Set NewSet;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < other.Size(); j++) {
          if ((data[i] == other[j]) && !(NewSet.IsSetMember(data[i])) ) {
            NewSet.PushBack(other[j]);
            break;
          }
        }
      }
      return NewSet;
    }
    /*Пересечение множеств без присваивания, конец*/

    /*Пересечение множеств с присваиванием, начало*/
    Set& operator&=(const Set& other) {
      *this = *this & other;
      return *this;
    }
    /*Пересечение множеств с присваиванием, конец*/

    /*Разность множеств без присваивания, начало*/
    Set operator-(const Set& other) const {
      Set NewSet;
      Set InterSet = *this & other;
      int i, j, flag;
      for (i = 0; i < size; i++) {
        flag = 0;
        for (j = 0; j < InterSet.Size(); j++) {
          if (data[i] == InterSet[j]) {
            flag = 1;
            break;
          }
        }
        if (flag != 1)
          NewSet.PushBack(data[i]);
      }
      return NewSet;
    }
    /*Разность множеств без присваивания, конец*/

    /*Разность множеств с присваиванием, начало*/
    Set& operator-=(const Set& other) {
      *this = *this - other;
      return *this;
    }
    /*Разность множеств с присваиванием, конец*/

    /*Симметрическая разность множеств без присваивания, начало*/
    Set operator^(const Set& other) const {
      Set UnionSet = *this | other;
      Set InterSet = *this & other;
      return UnionSet - InterSet;
    }
    /*Симметрическая разность множеств без присваивания, конец*/

    /*Симметрическая разность множеств с присваиванием, начало*/
    Set operator^=(const Set& other) {
      *this = *this ^ other;
      return *this;
    }
    /*Симметрическая разность множеств с присваиванием, конец*/
    /*Операции над множествами, конец ________________________*/
};

int main() {
  Set A(5);

  std::cout << A << std::endl;
  std::cin >> A;
  std::cout << A << std::endl;

  {
    Set copy(A); // ~ Set copy = A. При объявлении можно и равенством
    std::cout << A << "; " << copy << std::endl;
  }    // (1)
  A[0] = 99;    // (2)

  std::cout << "99 is A's member? " << A.IsSetMember(99) << std::endl;
  std::cout << "1755 is A's member? " << A.IsSetMember(1755) << std::endl;

  std::cout << std::endl;

  Set B;
  int k = 5;
  while (k > 0) {
    std::cin >> B;
    k--;
  }

  Set C(B);
  std::cin >> C;
  std::cout << "inputed B set: " << B << std::endl;
  std::cout << "C set: " << C << std::endl;

  if (B <= C)
    std::cout << "(B <= C) ~ true" << std::endl;
  if (!(C <= B))
    std::cout << "(C <= B) ~ false" << std::endl;

  if (C >= B)
    std::cout << "(C >= B) ~ true" << std::endl;
  if (!(B >= C))
    std::cout << "(B >= C) ~ false" << std::endl;

  if (C == B)
    std::cout << "(C == B) ~ true" << std::endl;
  if (!(B == C))
    std::cout << "(B == C) ~ false" << std::endl;

  if (C != B)
    std::cout << "(C != B) ~ true" << std::endl;
  if (!(B != C))
    std::cout << "(B != C) ~ false" << std::endl;

  if (C > B)
    std::cout << "(C > B) ~ true" << std::endl;
  if (!(B > C))
    std::cout << "(B > C) ~ false" << std::endl;

  if (C < B)
    std::cout << "(C < B) ~ true" << std::endl;
  if (!(B < C))
    std::cout << "(B < C) ~ false" << std::endl;

  std::cout << std::endl;

  A.ClearReps();
  B.ClearReps();
  C.ClearReps();

  std::cout << "A set cleared: " << A << std::endl;
  std::cout << "B set cleared: " << B << std::endl;
  std::cout << "C set cleared: " << C << std::endl;

  std::cout << std::endl;

  Set D;
  D = C;
  std::cout << "D = C result: " << D << std::endl;

  Set AunionB;
  AunionB = A|B;
  std::cout << "A union B: " << AunionB << std::endl;
  A|=B;
  std::cout << "A union B #2: " << A << std::endl;

  Set AintersectD;
  AintersectD = A&D;
  std::cout << "A intersect D: " << AintersectD << std::endl;
  A&=D;
  std::cout << "A intersect D #2: " << A << std::endl;

  Set CdifferenceB;
  CdifferenceB = C-B;
  std::cout << "C difference B: " << CdifferenceB << std::endl;
  C-=B;
  std::cout << "C difference B #2: " << C << std::endl;

  Set Dsym_differenceB;
  Dsym_differenceB = D^B;
  std::cout << "D sym difference B: " << Dsym_differenceB << std::endl;
  D^=B;
  std::cout << "D sym difference B #2: " << D << std::endl;

  return 0;
}