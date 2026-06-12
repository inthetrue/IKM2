#include "input_validator.h"

#include <iostream>
#include <sstream>

#include "exceptions.h"

int InputValidator::read_menu_choice(int min_value, int max_value) {
  return read_int_in_range("Введите пункт меню: ", min_value, max_value);
}

int InputValidator::read_int_in_range(const std::string& prompt,
                                      int min_value, int max_value) {
  while (true) {
    int value = read_int(prompt);
    if (value >= min_value && value <= max_value) {
      return value;
    }

    std::cout << "Введите число от " << min_value << " до "
              << max_value << "\n";
  }
}

std::string InputValidator::read_latin_string() {
  while (true) {
    std::string text = read_non_empty_line("Введите строку: ");
    try {
      validate_latin_string(text);
      return text;
    } catch (const ValidationException& exception) {
      std::cout << "Ошибка: " << exception.what() << "\n";
    }
  }
}

std::string InputValidator::read_non_empty_line(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string line;

    if (!std::getline(std::cin, line)) {
      std::cin.clear();
      std::cout << "Ошибка чтения строки\n";
      continue;
    }

    if (!line.empty()) {
      return line;
    }

    std::cout << "Строка не должна быть пустой\n";
  }
}

void InputValidator::validate_latin_string(const std::string& text) {
  if (text.empty()) {
    throw ValidationException("Строка не должна быть пустой");
  }

  for (int i = 0; i < static_cast<int>(text.length()); ++i) {
    if (!is_latin_letter(text[i])) {
      throw ValidationException(
          "Разрешены только буквы латинского алфавита");
    }
  }
}

int InputValidator::read_int(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string line;

    if (!std::getline(std::cin, line)) {
      std::cin.clear();
      std::cout << "Ошибка чтения числа\n";
      continue;
    }

    std::stringstream stream(line);
    int value = 0;
    char extra = '\0';

    // extra нужен, чтобы строка вида 12abc не считалась корректным вводом
    if ((stream >> value) && !(stream >> extra)) {
      return value;
    }

    std::cout << "Введите целое число\n";
  }
}

bool InputValidator::is_latin_letter(char symbol) {
  return (symbol >= 'a' && symbol <= 'z') ||
         (symbol >= 'A' && symbol <= 'Z');
}
