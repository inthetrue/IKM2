#include "compressor.h"

#include "exceptions.h"

const int kMaxIterations = 1000;

bool is_latin_letter_for_compression(char symbol) {
  return (symbol >= 'a' && symbol <= 'z') ||
         (symbol >= 'A' && symbol <= 'Z');
}

CompressionResult::CompressionResult() : original_(""), final_string_("") {}

const std::string& CompressionResult::original() const {
  return original_;
}

const std::string& CompressionResult::final_string() const {
  return final_string_;
}

bool CompressionResult::empty() const {
  return original_.empty() && final_string_.empty();
}

void CompressionResult::set_original(const std::string& original) {
  original_ = original;
}

void CompressionResult::set_final_string(const std::string& final_string) {
  final_string_ = final_string;
}

void CompressionResult::clear() {
  original_.clear();
  final_string_.clear();
}

CompressionResult StringCompressor::compress_until_stable(
    const std::string& text) const {
  if (text.empty()) {
    throw ValidationException("Строка не должна быть пустой");
  }

  CompressionResult result;
  result.set_original(text);

  std::string current = text;
  std::string next = compress_once(current);
  int repeat_count = 0;

  // цикл оставлен по условию, но цифры считаются частью количества
  while (next != current) {
    current = next;
    next = compress_once(current);
    ++repeat_count;

    // защита нужна, чтобы программа не зависла при ошибке в логике
    if (repeat_count > kMaxIterations) {
      throw ProjectException("Сжатие не стабилизировалось");
    }
  }

  result.set_final_string(current);
  return result;
}

std::string StringCompressor::compress_once(const std::string& text) const {
  if (text.empty()) {
    throw ValidationException("Строка не должна быть пустой");
  }

  // список нужен, чтобы не использовать готовые контейнеры для групп символов
  RunList runs = build_runs(text);
  return runs.to_compressed_string();
}

RunList StringCompressor::build_runs(const std::string& text) const {
  RunList runs;
  char current_symbol = text[0];
  int current_count = 1;

  // группа заканчивается, когда встречается другой символ
  for (int i = 1; i < static_cast<int>(text.length()); ++i) {
    if (text[i] == current_symbol) {
      ++current_count;
    } else {
      // флаг показывает, можно ли сжимать эту группу
      runs.push_back(current_symbol, current_count,
                     is_latin_letter_for_compression(current_symbol));
      current_symbol = text[i];
      current_count = 1;
    }
  }

  // последняя группа не попадет в список внутри цикла, поэтому добавляем ее тут
  runs.push_back(current_symbol, current_count,
                 is_latin_letter_for_compression(current_symbol));
  return runs;
}
