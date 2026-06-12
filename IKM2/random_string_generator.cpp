#include "random_string_generator.h"

#include <random>

#include "exceptions.h"

std::string RandomStringGenerator::generate(int length,
                                            int alphabet_size) const {
  if (length <= 0) {
    throw ValidationException("Длина строки должна быть больше нуля");
  }
  if (alphabet_size <= 0 || alphabet_size > 26) {
    throw ValidationException("Количество букв должно быть от 1 до 26");
  }

  const std::string letters = "abcdefghijklmnopqrstuvwxyz";
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> index_dist(0, alphabet_size - 1);

  std::string result;
  for (int i = 0; i < length; ++i) {
    // чем меньше alphabet_size, тем чаще будут повторы и заметнее сжатие
    result += letters[index_dist(gen)];
  }

  return result;
}
