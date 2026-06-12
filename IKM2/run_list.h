#ifndef IKM_STRING_COMPRESSION_RUN_LIST_H_
#define IKM_STRING_COMPRESSION_RUN_LIST_H_

#include <string>

class RunNode {
 public:
  RunNode(char symbol, int count, bool need_compression);

  char symbol() const;
  int count() const;
  bool need_compression() const;
  RunNode* next() const;
  void set_next(RunNode* next);

 private:
  char symbol_;
  int count_;
  bool need_compression_;
  RunNode* next_;
};

class RunList {
 public:
  RunList();
  RunList(const RunList& other);
  RunList& operator=(const RunList& other);
  ~RunList();

  void push_back(char symbol, int count, bool need_compression);
  std::string to_compressed_string() const;
  void clear();
  bool empty() const;

 private:
  RunNode* head_;
  RunNode* tail_;

  void copy_from(const RunList& other);
};

#endif
