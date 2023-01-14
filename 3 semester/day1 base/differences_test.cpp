 #include <iostream>

class Vector2d {
  private:
    double x;
    double y;
  public:
    /*Функция для чтения*/
    double X() const { return x; }
    /* Фукция для записи. Возвращает ссылку и не является константной.*/
    double& X() { return x; }
    double Y() const { return y; }
    double& Y() { return y; }
};

int main() {
  Vector2d vec;
  /* Полю x объекта vec присваиваем значение 5. */
  vec.X() = 5;
  /* Можно сохранить ссылку на поле y объекта vec. */
  double& yRef = vec.Y();
  /* Полю y объекта vec при помощи ссылки yRef присваиваем значение 10. */
  yRef = 10;
  /* Выводим поля x и y объекта vec. */
  std::cout << vec.X() << " " << vec.Y() << std::endl;
  return 0;
}