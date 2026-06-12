#include "menu.h"

#include <iostream>

#include "exceptions.h"
#include "file_work.h"
#include "input_validator.h"
#include "test_runner.h"

Menu::Menu() : has_result_(false) {}

void Menu::run() {
  while (true) {
    show_menu();
    int choice = InputValidator::read_menu_choice(0, 6);

    try {
      if (choice == 0) {
        std::cout << "Работа завершена\n";
        return;
      }
      if (choice == 1) {
        compress_from_keyboard();
      } else if (choice == 2) {
        compress_from_file();
      } else if (choice == 3) {
        compress_random_string();
      } else if (choice == 4) {
        show_last_result();
      } else if (choice == 5) {
        save_last_result();
      } else {
        TestRunner::run_all();
      }
    } catch (const ProjectException& exception) {
      // после ошибки программа не завершается, а возвращает пользователя в меню
      std::cout << "Ошибка: " << exception.what() << "\n";
    }
  }
}

void Menu::show_menu() const {
  std::cout << "\nСжатие строки\n";
  std::cout << "1. Сжать строку с клавиатуры\n";
  std::cout << "2. Сжать строку из файла\n";
  std::cout << "3. Сжать случайную строку\n";
  std::cout << "4. Показать последний результат\n";
  std::cout << "5. Сохранить последний результат в файл\n";
  std::cout << "6. Запустить тесты\n";
  std::cout << "0. Выход\n";
}

void Menu::compress_from_keyboard() {
  std::string text = InputValidator::read_latin_string();
  compress_and_show(text);
}

void Menu::compress_from_file() {
  std::string filename =
      InputValidator::read_non_empty_line("Введите имя файла: ");
  std::string text = FileWork::read_latin_string_from_file(filename);
  compress_and_show(text);
}

void Menu::compress_random_string() {
  int length = InputValidator::read_int_in_range(
      "Введите длину случайной строки: ", 1, 1000);
  int alphabet_size = InputValidator::read_int_in_range(
      "Введите количество букв из алфавита: ", 1, 26);
  std::string text = generator_.generate(length, alphabet_size);

  std::cout << "Случайная строка: " << text << "\n";
  compress_and_show(text);
}

void Menu::show_last_result() const {
  if (!has_result_) {
    throw EmptyDataException("Сначала выполните сжатие");
  }

  std::cout << "\n";
  print_result_line();
}

void Menu::save_last_result() const {
  if (!has_result_) {
    throw EmptyDataException("Сначала выполните сжатие");
  }

  std::string filename =
      InputValidator::read_non_empty_line("Введите имя файла: ");
  FileWork::save_result_to_file(filename, last_result_);
  std::cout << "Результат сохранен\n";
}

void Menu::compress_and_show(const std::string& text) {
  last_result_ = compressor_.compress_until_stable(text);
  has_result_ = true;
  show_last_result();
}

void Menu::print_result_line() const {
  std::cout << last_result_.original() << " -> ";
  std::cout << last_result_.final_string();
  std::cout << " -> (остается без изменений)\n";
}
