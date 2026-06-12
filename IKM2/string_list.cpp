#include "string_list.h"

#include <iostream>

#include "exceptions.h"

StringNode::StringNode(const std::string& value)
    : value_(value), next_(nullptr) {}

const std::string& StringNode::value() const {
  return value_;
}

StringNode* StringNode::next() const {
  return next_;
}

void StringNode::set_next(StringNode* next) {
  next_ = next;
}

StringList::StringList() : head_(nullptr), tail_(nullptr), size_(0) {}

StringList::StringList(const StringList& other)
    : head_(nullptr), tail_(nullptr), size_(0) {
  copy_from(other);
}

StringList& StringList::operator=(const StringList& other) {
  if (this != &other) {
    clear();
    copy_from(other);
  }
  return *this;
}

StringList::~StringList() {
  clear();
}

void StringList::push_back(const std::string& value) {
  StringNode* new_node = new StringNode(value);
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    ++size_;
    return;
  }

  tail_->set_next(new_node);
  tail_ = new_node;
  ++size_;
}

void StringList::print(std::ostream* out) const {
  StringNode* current = head_;
  int step_number = 0;

  while (current != nullptr) {
    *out << step_number << ". " << current->value() << "\n";
    current = current->next();
    ++step_number;
  }
}

void StringList::clear() {
  StringNode* current = head_;
  while (current != nullptr) {
    // узлы создавались через new, поэтому каждый нужно освободить через delete
    StringNode* next = current->next();
    delete current;
    current = next;
  }

  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

bool StringList::empty() const {
  return head_ == nullptr;
}

int StringList::size() const {
  return size_;
}

std::string StringList::last() const {
  if (tail_ == nullptr) {
    throw EmptyDataException("История сжатия пуста");
  }

  return tail_->value();
}

void StringList::copy_from(const StringList& other) {
  StringNode* current = other.head_;
  while (current != nullptr) {
    push_back(current->value());
    current = current->next();
  }
}
