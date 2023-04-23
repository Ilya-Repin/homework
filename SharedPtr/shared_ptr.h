#ifndef SHAREDPTR_H_
#define SHAREDPTR_H_
#include <iostream>

template <class T>
class SharedPtr {
 public:
  SharedPtr() = default;

  explicit SharedPtr(T *other) : ptr_(other) {
    if (other != nullptr) {
      ref_count_ = new size_t(1);
    } else {
      ref_count_ = nullptr;
    }
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    if (ref_count_ != nullptr) {
      ++*ref_count_;
    }
  }

  SharedPtr(SharedPtr<T> &&other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this == &other) {
      return *this;
    }

    Reset();
    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;

    if (ref_count_ != nullptr) {
      ++*ref_count_;
    }

    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    Reset();
    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;

    return *this;
  }

  void Reset(T *other = nullptr) {
    if (ref_count_ != nullptr) {
      --*ref_count_;

      if (*ref_count_ == 0) {
        delete ptr_;
        delete ref_count_;
      }
    }

    ptr_ = other;

    if (ptr_ != nullptr) {
      ref_count_ = new size_t(1);
    } else {
      ref_count_ = nullptr;
    }
  }

  void Swap(SharedPtr<T> &other) {
    std::swap(ptr_, other.ptr_);
    std::swap(ref_count_, other.ref_count_);
  }

  T *Get() const {
    return ptr_;
  }

  size_t UseCount() const {
    if (ref_count_ == nullptr) {
      return 0;
    }

    return *ref_count_;
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
    if (ref_count_ == nullptr) {
      return;
    }

    --*ref_count_;

    if (*ref_count_ == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

 private:
  T *ptr_ = nullptr;
  size_t *ref_count_ = nullptr;
};

#endif  // SHAREDPTR_H_
