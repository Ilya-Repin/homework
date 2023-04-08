#include "string_view.h"

StringView::StringView() : ptr_(nullptr), size_(0) {
}

StringView::StringView(const char *ptr) : ptr_(ptr) {
  size_t i = 0;

  while (ptr[i] != '\0') {
    ++i;
  }

  size_ = i;
}

StringView::StringView(const char *ptr, const size_t size) : ptr_(ptr), size_(size) {
}

const char &StringView::operator[](const size_t pos) const {
  return ptr_[pos];
}

const char &StringView::At(const size_t pos) const {
  if (pos >= size_) {
    throw StringViewOutOfRange{};
  }

  return ptr_[pos];
}

const char &StringView::Front() const {
  return ptr_[0];
}

const char &StringView::Back() const {
  return ptr_[size_ - 1];
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return (size_ == 0);
}

const char *StringView::Data() const {
  return ptr_;
}

void StringView::Swap(StringView &sv) {
  std::swap(ptr_, sv.ptr_);
  std::swap(size_, sv.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  ptr_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  if (pos >= size_) {
    throw StringViewOutOfRange{};
  }

  return StringView(ptr_ + pos, std::min(count, size_ - pos));
}
