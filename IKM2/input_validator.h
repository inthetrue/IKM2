#ifndef IKM_STRING_COMPRESSION_INPUT_VALIDATOR_H_
#define IKM_STRING_COMPRESSION_INPUT_VALIDATOR_H_

#include <string>

class InputValidator {
 public:
  static int read_menu_choice(int min_value, int max_value);
  static int read_int_in_range(const std::string& prompt, int min_value,
                               int max_value);
  static std::string read_latin_string();
  static std::string read_non_empty_line(const std::string& prompt);
  static void validate_latin_string(const std::string& text);

 private:
  static int read_int(const std::string& prompt);
  static bool is_latin_letter(char symbol);
};

#endif
