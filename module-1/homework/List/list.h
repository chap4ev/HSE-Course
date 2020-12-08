#pragma once
#include <cstddef>


namespace task {

class Int_node {
 public:
  int value;

  Int_node* prev;
  Int_node* next;
};


class list {

 public:

  list();
  list(size_t count, const int& value = int());

  list(const list& other);

  ~list();

  list& operator=(const list& other);


  int& front();
  const int& front() const;

  int& back();
  const int& back() const;


  bool empty() const;
  size_t size() const;
  void clear();


  void push_back(const int& value);
  void pop_back();

  void push_front(const int& value);
  void pop_front();


  void resize(size_t count);

  void swap(list& other);

  void remove(const int& value);

  void unique();

  void sort();

 private:

  Int_node* head;
  Int_node* tail;
  
  size_t length;

  void unsafe_delete_node(Int_node* node);

}; // class list

}  // namespace task
