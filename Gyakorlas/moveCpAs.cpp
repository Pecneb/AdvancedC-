// VizsgaPlayground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

class IntNode {
  int value;
  IntNode* next;
public:
  IntNode(int v) : value(v), next(nullptr) {}
  int getValue() { return value; }
  IntNode* getNext() { return next; }
  void setNext(IntNode* n) { next = n; }
};

class IntLinkedList {
  IntNode* head;
public:
  IntLinkedList() : head(nullptr) {}
  ~IntLinkedList();
  IntLinkedList(const IntLinkedList& other);
  IntLinkedList& operator=(const IntLinkedList& other);
  IntLinkedList(IntLinkedList&& other);
  IntLinkedList& operator=(IntLinkedList&& other);
  IntLinkedList& addNode(int value);
  void clear();
  void print();
};

IntLinkedList::~IntLinkedList() {
  IntNode* cur = head;
  IntNode* next = nullptr;
  while (true) {
    if (cur) {
      next = cur->getNext();
      delete cur;
      cur = next;
    }
    else {
      break;
    }
  }
}

void IntLinkedList::clear() {
  IntNode* cur = head;
  IntNode* next = nullptr;
  while(cur) {
    next = cur->getNext();
    delete cur;
    cur = next;
  }
}

IntLinkedList::IntLinkedList(const IntLinkedList& other) : head(nullptr) {
  std::cout << "\tcopy constructor called" << std::endl;
  IntNode* curInOther = other.head;
  IntNode* preInThis = nullptr;
  while (true) {
    if (curInOther && !head) {
      head = new IntNode(curInOther->getValue());
      preInThis = head;
    }
    else if (curInOther) {
      preInThis->setNext(new IntNode(curInOther->getValue()));
      preInThis = preInThis->getNext();
    }
    else {
      break;
    }
    curInOther = curInOther->getNext();
  }
}

IntLinkedList& IntLinkedList::operator=(const IntLinkedList& other) {
  std::cout << "\tcopy consturtor called" << std::endl;
  // copy and swap
  IntLinkedList tmp(other);
  IntNode* tmpHead = tmp.head;
  tmp.head = this->head;
  this->head = tmpHead;
  return *this;
}

IntLinkedList::IntLinkedList(IntLinkedList&& other) : head(other.head) {
  std::cout << "\tmove constructor called" << std::endl;
  other.head = nullptr;
}

IntLinkedList& IntLinkedList::operator=(IntLinkedList&& other) {
  std::cout << "\tmove assingment called" << std::endl;
  head = other.head;
  other.head = nullptr;
  return *this;
}

IntLinkedList& IntLinkedList::addNode(int value) {
  if (!head) {
    head = new IntNode(value);
  }
  else {
    IntNode* pre = head;
    IntNode* cur = head->getNext();
    while (true) {
      if (!cur) {
        cur = new IntNode(value);
        if (pre) pre->setNext(cur);
        break;
      }
      pre = cur;
      cur = cur->getNext();
    }
  }
  return *this;
}

void IntLinkedList::print() {
  IntNode* cur = head;
  while (true) {
    if (cur) {
      std::cout << cur->getValue();
    }
    else {
      std::cout << std::endl;
      break;
    }
    cur = cur->getNext();
    if (cur) { std::cout << ", "; }
  }
}



int main()
{
  IntLinkedList ll1;
  ll1.addNode(5).addNode(6).addNode(7);
  ll1.print();

  IntLinkedList ll2(ll1);
  ll2.addNode(77);

  ll1.print();
  ll2.print();

  IntLinkedList ll3 = ll1;

  ll3.print();

  ll2 = ll1;

  ll2.print();
}

