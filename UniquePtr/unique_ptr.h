#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

#include <iostream>

template <class T>
class UniquePtr {
 public:
  UniquePtr() : ptr_(nullptr) {
  }

  explicit UniquePtr(T *other) : ptr_(other) {
  }

  UniquePtr(UniquePtr &&other) noexcept : ptr_(other.ptr_) {
      other.ptr_ = nullptr;
  }

  UniquePtr(const UniquePtr<T> &other) = delete;

  UniquePtr &operator=(const UniquePtr<T> &other) = delete;

  UniquePtr &operator=(UniquePtr &&other) noexcept {
    Reset(other.ptr_);
    other.ptr_ = nullptr;
    return *this;
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return (ptr_ != nullptr);
  }

  T *Release() {
    T *copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }

  void Reset(T *ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  void Swap(UniquePtr<T> &other) {
    std::swap(ptr_, other.ptr_);
  }

  T *Get() const {
    return ptr_;
  }

  ~UniquePtr() {
    delete ptr_;
  }

 private:
  T *ptr_;
};

#endif  // UNIQUEPTR_H_
