#ifndef IKM_STRING_COMPRESSION_STRING_LIST_H_
#define IKM_STRING_COMPRESSION_STRING_LIST_H_

#include <iosfwd>
#include <string>

class StringNode {
 public:
  explicit StringNode(const std::string& value);

  const std::string& value() const;
  StringNode* next() const;
  void set_next(StringNode* next);

 private:
  std::string value_;
  StringNode* next_;
};

class StringList {
 public:
  StringList();
  StringList(const StringList& other);
  StringList& operator=(const StringList& other);
  ~StringList();

  void push_back(const std::string& value);
  void print(std::ostream* out) const;
  void clear();
  bool empty() const;
  int size() const;
  std::string last() const;

 private:
  StringNode* head_;
  StringNode* tail_;
  int size_;

  void copy_from(const StringList& other);
};

#endif
