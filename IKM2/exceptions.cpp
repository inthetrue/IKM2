#include "exceptions.h"

ProjectException::ProjectException(const std::string& message)
    : std::runtime_error(message) {}

ValidationException::ValidationException(const std::string& message)
    : ProjectException(message) {}

FileException::FileException(const std::string& message)
    : ProjectException(message) {}

EmptyDataException::EmptyDataException(const std::string& message)
    : ProjectException(message) {}
