#include "test_runner.h"

#include <iostream>
#include <string>

#include "compressor.h"

class TestCase {
 public:
  TestCase(const char* name, const char* input, const char* expected)
      : name_(name), input_(input), expected_(expected) {}

  const char* name() const {
    return name_;
  }

  const char* input() const {
    return input_;
  }

  const char* expected() const {
    return expected_;
  }

 private:
  const char* name_;
  const char* input_;
  const char* expected_;
};

void TestRunner::run_all() {
  const TestCase tests[] = {
      TestCase("пример 1", "aaabbb", "a3b3"),
      TestCase("пример 2", "aaaabbaaacccaaa", "a4b2a3c3a3"),
      TestCase("без повторов", "abcXYZ", "abcXYZ"),
      TestCase("один символ", "a", "a"),
      TestCase("число повторений не сжимается", "aaaaaaaaaaa", "a11"),
      TestCase("разные регистры", "aaAAAbb", "a2A3b2")};

  const int test_count = static_cast<int>(sizeof(tests) / sizeof(tests[0]));
  int passed_count = 0;
  StringCompressor compressor;

  std::cout << "\nТестирование\n";
  for (int i = 0; i < test_count; ++i) {
    CompressionResult result =
        compressor.compress_until_stable(tests[i].input());

    bool passed = result.final_string() == tests[i].expected();
    if (passed) {
      ++passed_count;
    }

    std::cout << tests[i].name() << ": ";
    std::cout << tests[i].input() << " -> " << result.final_string();
    std::cout << " | ожидалось: " << tests[i].expected();
    std::cout << " | " << (passed ? "успешно" : "ошибка") << "\n";
  }

  std::cout << "Итог: " << passed_count << " из "
            << test_count << " тестов пройдено\n";
}
