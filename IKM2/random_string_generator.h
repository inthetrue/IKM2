#ifndef IKM_STRING_COMPRESSION_RANDOM_STRING_GENERATOR_H_
#define IKM_STRING_COMPRESSION_RANDOM_STRING_GENERATOR_H_

#include <string>

class RandomStringGenerator {
 public:
  std::string generate(int length, int alphabet_size) const;
};

#endif
