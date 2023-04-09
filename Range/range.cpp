#include "range.h"

ItObject::ItObject(int end) : begin_(0), end_(end), step_(1) {
  if (end_ < 0) {
    begin_ = 0;
    end_ = 0;
  }
}

ItObject::ItObject(int begin, int end, int step) : begin_(begin), end_(end), step_(step) {
  if (((step_ > 0) && (end_ - begin_ < 0)) || ((step_ < 0) && (end_ - begin_ > 0)) || (step_ == 0)) {
    begin_ = 0;
    end_ = 0;
  }
}

ItObject::Iterator::Iterator(int curr, int step) : curr_(curr), step_(step) {
}

int& ItObject::Iterator::operator*() {
  return curr_;
}

ItObject::Iterator ItObject::Iterator::operator++() {
  curr_ += step_;
  return *this;
}

bool ItObject::Iterator::operator!=(const Iterator& other) const {
  return curr_ != other.curr_;
}

bool ItObject::Iterator::operator==(const Iterator& other) const {
  return curr_ == other.curr_;
}

ItObject::ReverseIterator::ReverseIterator(int curr, int step) : curr_(curr), step_(step) {
}

int& ItObject::ReverseIterator::operator*() {
  return curr_;
}

ItObject::ReverseIterator ItObject::ReverseIterator::operator++() {
  curr_ -= step_;
  return *this;
}

bool ItObject::ReverseIterator::operator!=(const ReverseIterator& other) const {
  return curr_ != other.curr_;
}

bool ItObject::ReverseIterator::operator==(const ReverseIterator& other) const {
  return curr_ == other.curr_;
}

const ItObject::Iterator ItObject::begin() const {  // NOLINT
  return ItObject::Iterator(begin_, step_);
}

const ItObject::Iterator ItObject::end() const {  // NOLINT
  if (step_ == 0) {
    return ItObject::Iterator(0, 0);
  }

  int amount = std::abs(end_ - begin_) % std::abs(step_) == 0 ? (std::abs(end_ - begin_) / std::abs(step_))
                                                              : ((std::abs(end_ - begin_) / std::abs(step_)) + 1);

  return ItObject::Iterator(begin_ + step_ * amount, step_);
}

const ItObject::ReverseIterator ItObject::rbegin() const {  // NOLINT
  if (step_ == 0) {
    return ItObject::ReverseIterator(0, 0);
  }

  int amount = std::abs(end_ - begin_) % std::abs(step_) == 0 ? (std::abs(end_ - begin_) / std::abs(step_))
                                                              : ((std::abs(end_ - begin_) / std::abs(step_)) + 1);

  return ItObject::ReverseIterator(begin_ + step_ * (amount - 1), step_);
}

const ItObject::ReverseIterator ItObject::rend() const {  // NOLINT
  return ItObject::ReverseIterator(begin_ - step_, step_);
}

ItObject Range(int end) {
  return ItObject(end);
}

ItObject Range(int begin, int end, int step) {
  return ItObject(begin, end, step);
}