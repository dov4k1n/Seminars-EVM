/**
 * @file methods/main.cpp
 * @author Mikhail Lozhnikov, Ayzat Rizatdinov (dov4k1n)
 *
 * Файл с функией main() для серверной части программы.
 */

#include <httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "methods.hpp"

using graph::TopologicalSortMethod;

int main(int argc, char* argv[]) {
  // Порт по-умолчанию.
  int port = 8080;

  if (argc >= 2) {
    // Меняем порт по умолчанию, если предоставлен соответствующий
    // аргумент командной строки.
    if (std::sscanf(argv[1], "%d", &port) != 1) {
      return -1;
    }
  }

  std::cerr << "Listening on port " << port << "..." << std::endl;

  httplib::Server svr;

  // Обработчик для GET запроса по адресу /stop. Этот обработчик
  // останавливает сервер.
  svr.Get("/stop", [&](const httplib::Request& /*unused*/,
    httplib::Response& /*unused*/) {
      svr.stop();
  });

  /* Сюда нужно вставить обработчик post запроса для алгоритма. */

  /* /TopologicalSort это адрес для запросов на топологическую сортировку
  на сервере. */
  svr.Post(
    "/TopologicalSort",
    [&](
      const httplib::Request& request,
      httplib::Response& response
    ) {
      /*
      Поле body структуры httplib::Request содержит текст запроса.
      Функция nlohmann::json::parse() используется для того,
      чтобы преобразовать текст в объект типа nlohmann::json.
      */
      const nlohmann::json input = nlohmann::json::parse(request.body);
      nlohmann::json output;

      /* Если метод завершился с ошибкой, то выставляем статус 400. */
      if (TopologicalSortMethod(input, &output) < 0)
        response.status = 400;

      /*
      Метод nlohmann::json::dump() используется для сериализации
      объекта типа nlohmann::json в строку. Метод set_content()
      позволяет задать содержимое ответа на запрос. Если передаются
      JSON данные, то MIME тип следует выставить application/json.
      */
      response.set_content(output.dump(), "application/json");
    }
  );

  /* Конец вставки. */

  // Эта функция запускает сервер на указанном порту. Программа не завершится
  // до тех пор, пока сервер не будет остановлен.
  svr.listen("0.0.0.0", port);

  return 0;
}
