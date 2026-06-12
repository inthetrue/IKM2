#include "run_list.h"

#include <string>

RunNode::RunNode(char symbol, int count, bool need_compression)
    : symbol_(symbol),
      count_(count),
      need_compression_(need_compression),
      next_(nullptr) {}

char RunNode::symbol() const {
  return symbol_;
}

int RunNode::count() const {
  return count_;
}

bool RunNode::need_compression() const {
  return need_compression_;
}

RunNode* RunNode::next() const {
  return next_;
}

void RunNode::set_next(RunNode* next) {
  next_ = next;
}

RunList::RunList() : head_(nullptr), tail_(nullptr) {}

RunList::RunList(const RunList& other) : head_(nullptr), tail_(nullptr) {
  copy_from(other);
}

RunList& RunList::operator=(const RunList& other) {
  if (this != &other) {
    clear();
    copy_from(other);
  }
  return *this;
}

RunList::~RunList() {
  clear();
}

void RunList::push_back(char symbol, int count, bool need_compression) {
  RunNode* new_node = new RunNode(symbol, count, need_compression);
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    return;
  }

  tail_->set_next(new_node);
  tail_ = new_node;
}

std::string RunList::to_compressed_string() const {
  std::string result;
  RunNode* current = head_;

  while (current != nullptr) {
    if (current->need_compression()) {
      result += current->symbol();
      if (current->count() > 1) {
        result += std::to_string(current->count());
      }
    } else {
      // цифры уже являются количеством, поэтому не превращаем 11 в 12
      for (int i = 0; i < current->count(); ++i) {
        result += current->symbol();
      }
    }
    current = current->next();
  }

  return result;
}

void RunList::clear() {
  RunNode* current = head_;
  while (current != nullptr) {
    // next сохраняется до delete, иначе ссылка на следующий узел потеряется
    RunNode* next = current->next();
    delete current;
    current = next;
  }

  head_ = nullptr;
  tail_ = nullptr;
}

bool RunList::empty() const {
  return head_ == nullptr;
}

void RunList::copy_from(const RunList& other) {
  RunNode* current = other.head_;
  while (current != nullptr) {
    push_back(current->symbol(), current->count(),
              current->need_compression());
    current = current->next();
  }
}
