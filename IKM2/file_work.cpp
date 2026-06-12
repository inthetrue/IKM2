#include "file_work.h"

#include <filesystem>
#include <fstream>

#include "exceptions.h"
#include "input_validator.h"

std::string FileWork::read_latin_string_from_file(
    const std::string& filename) {
  std::ifstream input(filename);
  if (!input.is_open()) {
    throw FileException("Не удалось открыть файл для чтения");
  }

  std::string text;
  if (!std::getline(input, text)) {
    throw FileException("Не удалось прочитать строку из файла");
  }

  InputValidator::validate_latin_string(text);
  return text;
}

void FileWork::save_result_to_file(const std::string& filename,
                                   const CompressionResult& result) {
  if (result.empty()) {
    throw EmptyDataException("Нет результата для сохранения");
  }

  std::filesystem::path file_path(filename);

  if (file_path.has_parent_path() &&
      !std::filesystem::exists(file_path.parent_path())) {
    throw FileException("Папка для сохранения не существует");
  }

  if (std::filesystem::is_directory(file_path)) {
    throw FileException("Нельзя сохранить результат в папку");
  }

  std::ofstream output(filename);
  if (!output.is_open()) {
    throw FileException("Не удалось открыть файл для записи");
  }

  output << result.original() << " -> ";
  output << result.final_string();
  output << " -> (остается без изменений)\n";
}
