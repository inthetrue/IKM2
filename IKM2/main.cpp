#include <exception>
#include <iostream>

#include "menu.h"

int main() {
  try {
    Menu menu;
    menu.run();
  } catch (const std::exception& exception) {
    std::cout << "Критическая ошибка: " << exception.what() << "\n";
    return 1;
  }

  return 0;
}
