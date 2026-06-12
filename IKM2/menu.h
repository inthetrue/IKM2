#ifndef IKM_STRING_COMPRESSION_MENU_H_
#define IKM_STRING_COMPRESSION_MENU_H_

#include "compressor.h"
#include "random_string_generator.h"

class Menu {
 public:
  Menu();
  void run();

 private:
  StringCompressor compressor_;
  RandomStringGenerator generator_;
  CompressionResult last_result_;
  bool has_result_;

  void show_menu() const;
  void compress_from_keyboard();
  void compress_from_file();
  void compress_random_string();
  void show_last_result() const;
  void save_last_result() const;
  void compress_and_show(const std::string& text);
  void print_result_line() const;
};

#endif
