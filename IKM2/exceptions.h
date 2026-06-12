#ifndef IKM_STRING_COMPRESSION_EXCEPTIONS_H_
#define IKM_STRING_COMPRESSION_EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class ProjectException : public std::runtime_error {
 public:
  explicit ProjectException(const std::string& message);
};

class ValidationException : public ProjectException {
 public:
  explicit ValidationException(const std::string& message);
};

class FileException : public ProjectException {
 public:
  explicit FileException(const std::string& message);
};

class EmptyDataException : public ProjectException {
 public:
  explicit EmptyDataException(const std::string& message);
};

#endif
