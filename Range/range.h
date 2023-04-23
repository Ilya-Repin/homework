#ifndef RANGE_H_
#define RANGE_H_
#define REVERSE_RANGE_IMPLEMENTED
#include <iostream>

class IteratorObject {
 public:
  explicit IteratorObject(int end);
  IteratorObject(int begin, int end, int step = 1);

  class Iterator {
   public:
    Iterator(int curr, int step);

    int& operator*();
    Iterator operator++();

    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;

   private:
    int curr_;
    int step_;
  };

  class ReverseIterator {
   public:
    ReverseIterator(int curr, int step);

    int& operator*();
    ReverseIterator operator++();

    bool operator!=(const ReverseIterator& other) const;
    bool operator==(const ReverseIterator& other) const;

   private:
    int curr_;
    int step_;
  };

  const Iterator begin() const;          // NOLINT
  const Iterator end() const;            // NOLINT
  const ReverseIterator rbegin() const;  // NOLINT
  const ReverseIterator rend() const;    // NOLINT

 private:
  int begin_;
  int end_;
  int step_;
};

IteratorObject Range(int end);
IteratorObject Range(int begin, int end, int step = 1);

#endif  // RANGE_H_
