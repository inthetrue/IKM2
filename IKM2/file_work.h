#ifndef IKM_STRING_COMPRESSION_FILE_WORK_H_
#define IKM_STRING_COMPRESSION_FILE_WORK_H_

#include <string>

#include "compressor.h"

class FileWork {
 public:
  static std::string read_latin_string_from_file(
      const std::string& filename);
  static void save_result_to_file(const std::string& filename,
                                  const CompressionResult& result);
};

#endif
