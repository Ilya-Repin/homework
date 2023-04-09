#ifndef SHAREDPTR_H_
#define SHAREDPTR_H_
#include <iostream>

template <class T>
class SharedPtr {
 public:
  SharedPtr() = default;

  explicit SharedPtr(T *other) : ptr_(other) {
    if (other != nullptr) {
      amount_ = new size_t(1);
    } else {
      amount_ = nullptr;
    }
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), amount_(other.amount_) {
    if (amount_ != nullptr) {
      ++*amount_;
    }
  }

  SharedPtr(SharedPtr<T> &&other) noexcept : ptr_(other.ptr_), amount_(other.amount_) {
    other.ptr_ = nullptr;
    other.amount_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this == &other) {
      return *this;
    }

    Reset();
    ptr_ = other.ptr_;
    amount_ = other.amount_;

    if (amount_ != nullptr) {
      ++*amount_;
    }

    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    Reset();
    ptr_ = other.ptr_;
    amount_ = other.amount_;
    other.ptr_ = nullptr;
    other.amount_ = nullptr;

    return *this;
  }

  void Reset(T *other = nullptr) {
    if (amount_ != nullptr) {
      --*amount_;

      if (*amount_ == 0) {
        delete ptr_;
        delete amount_;
      }
    }

    ptr_ = other;

    if (ptr_ != nullptr) {
      amount_ = new size_t(1);
    } else {
      amount_ = nullptr;
    }
  }

  void Swap(SharedPtr<T> &other) {
    std::swap(ptr_, other.ptr_);
    std::swap(amount_, other.amount_);
  }

  T *Get() const {
    return ptr_;
  }

  size_t UseCount() const {
    if (amount_ == nullptr) {
      return 0;
    }

    return *amount_;
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

  ~SharedPtr() {
    if (amount_ == nullptr) {
      return;
    }

    --*amount_;

    if (*amount_ == 0) {
      delete ptr_;
      delete amount_;
    }
  }

 private:
  T *ptr_ = nullptr;
  size_t *amount_ = nullptr;
};

#endif  // SHAREDPTR_H_
