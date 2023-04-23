#include "range.h"

IteratorObject::IteratorObject(int end) : begin_(0), end_(end), step_(1) {
  if (end_ < 0) {
    begin_ = 0;
    end_ = 0;
  }
}

IteratorObject::IteratorObject(int begin, int end, int step) : begin_(begin), end_(end), step_(step) {
  if ((step_ > 0 && end_ < begin_) || (step_ < 0 && end_ > begin_) || (step_ == 0)) {
    begin_ = 0;
    end_ = 0;
  }
}

IteratorObject::Iterator::Iterator(int curr, int step) : curr_(curr), step_(step) {
}

int& IteratorObject::Iterator::operator*() {
  return curr_;
}

IteratorObject::Iterator IteratorObject::Iterator::operator++() {
  curr_ += step_;
  return *this;
}

bool IteratorObject::Iterator::operator!=(const Iterator& other) const {
  return curr_ != other.curr_;
}

bool IteratorObject::Iterator::operator==(const Iterator& other) const {
  return curr_ == other.curr_;
}

IteratorObject::ReverseIterator::ReverseIterator(int curr, int step) : curr_(curr), step_(step) {
}

int& IteratorObject::ReverseIterator::operator*() {
  return curr_;
}

IteratorObject::ReverseIterator IteratorObject::ReverseIterator::operator++() {
  curr_ -= step_;
  return *this;
}

bool IteratorObject::ReverseIterator::operator!=(const ReverseIterator& other) const {
  return curr_ != other.curr_;
}

bool IteratorObject::ReverseIterator::operator==(const ReverseIterator& other) const {
  return curr_ == other.curr_;
}

const IteratorObject::Iterator IteratorObject::begin() const {  // NOLINT
  return IteratorObject::Iterator(begin_, step_);
}

const IteratorObject::Iterator IteratorObject::end() const {  // NOLINT
  if (step_ == 0) {
    return IteratorObject::Iterator(0, 0);
  }

  int amount;

  if (std::abs(end_ - begin_) % std::abs(step_) == 0) {
    amount = (std::abs(end_ - begin_) / std::abs(step_));
  } else {
    amount = ((std::abs(end_ - begin_) / std::abs(step_)) + 1);
  }

  return IteratorObject::Iterator(begin_ + step_ * amount, step_);
}

const IteratorObject::ReverseIterator IteratorObject::rbegin() const {  // NOLINT
  if (step_ == 0) {
    return IteratorObject::ReverseIterator(0, 0);
  }

  int amount;

  if (std::abs(end_ - begin_) % std::abs(step_) == 0) {
    amount = (std::abs(end_ - begin_) / std::abs(step_));
  } else {
    amount = ((std::abs(end_ - begin_) / std::abs(step_)) + 1);
  }

  return IteratorObject::ReverseIterator(begin_ + step_ * (amount - 1), step_);
}

const IteratorObject::ReverseIterator IteratorObject::rend() const {  // NOLINT
  return IteratorObject::ReverseIterator(begin_ - step_, step_);
}

IteratorObject Range(int end) {
  return IteratorObject(end);
}

IteratorObject Range(int begin, int end, int step) {
  return IteratorObject(begin, end, step);
}