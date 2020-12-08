#include "list.h"

#include<stdexcept>

task::list::list()
    : head(nullptr), tail(nullptr), length(0) {}

task::list::list(size_t count, const int& value)
    : head(nullptr), tail(nullptr), length(0) {
  for (; count > 0; --count) {
    push_back(value);
  }
}

// copy ctor
task::list::list(const task::list& other)
    : head(nullptr), tail(nullptr), length(0) {
  auto cur_other = other.head;

  while (cur_other != nullptr) {
    push_back(cur_other->value);
    cur_other = cur_other->next;
  }
}

task::list::~list() {
  clear();
}

task::list& task::list::operator=(const task::list& other) {
  if (this == &other) {
    return *this;
  }

  // in case other.empty() use clear() because it is faster then resize()
  if (other.empty()) {
    clear();
    return *this;
  }

  // cut extra nodes to reduce size() to other.size()
  if (length > other.size()) {
    resize(other.size());
  }

  size_t iter = 0;
  auto cur_this = head;
  auto cur_other = other.head;

  // copy values of nodes from head to tail
  for (; iter < length; ++iter) {
    cur_this->value = cur_other->value;
    cur_this = cur_this->next;
    cur_other = cur_other->next;
  }

  // copy values of nodes from tail to other.tail (if other.size() > size())
  for (; iter < other.length; ++iter) {
    push_back(cur_other->value);
    cur_other = cur_other->next;
  }

  return *this;
}

int& task::list::front() {
  if (empty()) {
    throw std::runtime_error("list::front(): list is empty");
  }
  return head->value;
}

const int& task::list::front() const {
  if (empty()) {
    throw std::runtime_error("list::front(): list is empty");
  }
  return head->value;
}

int& task::list::back() {
  if (empty()) {
    throw std::runtime_error("list::back(): list is empty");
  }
  return tail->value;
}

const int& task::list::back() const {
  if (empty()) {
    throw std::runtime_error("list::back(): list is empty");
  }
  return tail->value;
}

bool task::list::empty() const {
  return length == 0;
}

size_t task::list::size() const {
  return length;
}

void task::list::clear() {
  if (empty()) {
    return;
  }

  for (auto cur = head; cur != nullptr;) {
    auto cur_next = cur->next;
    delete cur;
    cur = cur_next;
  }

  head = nullptr;
  tail = nullptr;
  length = 0;
}

void task::list::push_back(const int& value) {
  if (empty()) {
    tail = new task::Int_node{value, nullptr, nullptr};
    head = tail;
    length = 1;

  } else { // (length > 1)
    tail->next = new task::Int_node{value, tail, nullptr};
    tail = tail->next;
    ++length;
  }
}

void task::list::pop_back() {
  if (empty()) {
    throw std::runtime_error("list::pop_back(): list is empty");
  }

  if (length == 1) {
    delete tail;
    tail = nullptr;
    head = nullptr;

  } else { // (length > 1)
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
  }

  --length;
}

void task::list::push_front(const int& value) {
  if (empty()) {
    head = new task::Int_node{value, nullptr, nullptr};
    tail = head;
    length = 1;

  } else { // (length > 1)
    head->prev = new task::Int_node{value, nullptr, head};
    head = head->prev;
    ++length;
  }
}

void task::list::pop_front() {
  if (empty()) {
    throw std::runtime_error("list::pop_front(): list is empty");
  }

  if (length == 1) {
    delete head;
    tail = nullptr;
    head = nullptr;

  } else { // (length > 1)
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
  }

  --length;
}

void task::list::resize(size_t count) {
  if (count == 0) {
    clear();
    return;
  }

  while (length > count) {
    pop_back();
  }
  while (length < count) {
    push_back(int());
  }
}

void task::list::swap(task::list& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(length, other.length);
}

void task::list::unsafe_delete_node(Int_node* node) {
  // Unsafe because we need to know for sure that this node is from this list.

  if (node == head) {
    pop_front();

  } else if (node == tail) {
    pop_back();

  } else { // Node somewhere in the middle (length >= 3)
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --length;
  }
}

void task::list::remove(const int& value) {
  // If the value for delete was set using node from this list,
  // then if we delete this node we will no longer heve access
  // to this value anymore. So I just copy this value in case
  // this problem occurs.
  int value_copy = value;

  auto cur = head;

  while (cur != nullptr) {
    auto next_node = cur->next;
    if (cur->value == value_copy) {
      unsafe_delete_node(cur);
    }
    cur = next_node;
  }
}

void task::list::unique() {
  if (empty())
    return;

  auto cur = head->next;

  while (cur != nullptr) {
    if (cur->value == cur->prev->value) {
      unsafe_delete_node(cur->prev);
    }
    cur = cur->next;
  }
}

void task::list::sort() {
  if (length < 2) {
    return;
  }

  auto cur = head;

  for (size_t i = 0; i < length; ++i) {
    // Find node with max value after cur (include cur)

    auto max_node = cur;

    for (auto cur_tmp = cur; cur_tmp != nullptr; cur_tmp = cur_tmp->next) {
      if (max_node->value < cur_tmp->value) {
        max_node = cur_tmp;
      }
    }

    // Move max node to the front

    // if (max node == cur) move cur to the next node
    if (max_node == cur) {
      cur = cur->next;
    }

    // no need to move head node
    if (max_node == head) {
      continue;
    }

    // cut
    max_node->prev->next = max_node->next;
    if (max_node == tail) {
      tail = max_node->prev;
    } else {
      max_node->next->prev = max_node->prev;
    }

    // push front
    max_node->prev = nullptr;
    max_node->next = head;
    head->prev = max_node;
    head = max_node;
  }
}