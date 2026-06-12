#ifndef IKM_STRING_COMPRESSION_COMPRESSOR_H_
#define IKM_STRING_COMPRESSION_COMPRESSOR_H_

#include <string>

#include "run_list.h"

class CompressionResult {
 public:
  CompressionResult();

  const std::string& original() const;
  const std::string& final_string() const;
  bool empty() const;

  void set_original(const std::string& original);
  void set_final_string(const std::string& final_string);
  void clear();

 private:
  std::string original_;
  std::string final_string_;
};

class StringCompressor {
 public:
  CompressionResult compress_until_stable(const std::string& text) const;
  std::string compress_once(const std::string& text) const;

 private:
  RunList build_runs(const std::string& text) const;
};

#endif
