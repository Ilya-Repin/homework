#ifndef ARRAY_H_
#define ARRAY_H_
#define ARRAY_TRAITS_IMPLEMENTED
#include <iostream>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t N>
class Array {
 public:
  T my_arr[N];

  T &operator[](size_t idx) {
    return my_arr[idx];
  }

  const T &operator[](size_t idx) const {
    return my_arr[idx];
  }

  T &At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }

    return my_arr[idx];
  }

  const T &At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }

    return my_arr[idx];
  }

  T &Front() {
    return my_arr[0];
  }

  const T &Front() const {
    return my_arr[0];
  }

  T &Back() {
    return my_arr[N - 1];
  }

  const T &Back() const {
    return my_arr[N - 1];
  }

  const T *Data() const {
    return my_arr;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return (N == 0);
  }

  void Fill(const T &value) {
    for (size_t i = 0; i < N; ++i) {
      my_arr[i] = value;
    }
  }

  void Swap(Array<T, N> &other) {
    for (size_t i = 0; i < N; ++i) {
      T tmp = std::move(my_arr[i]);
      my_arr[i] = std::move(other.my_arr[i]);
      other.my_arr[i] = std::move(tmp);
    }
  }
};

template <class T, size_t N>
size_t GetSize(T (&)[N]) {
  return N;
}

template <class T>
size_t GetSize(T) {
  return 0;
}

template <class T>
size_t GetRank(T) {
  return 0;
}

template <class T, size_t N>
size_t GetRank(T (&array)[N]) {
  return 1 + GetRank(array[0]);
}

template <class T>
size_t GetNumElements(T) {
  return 1;
}

template <class T, size_t N>
size_t GetNumElements(T (&array)[N]) {
  return GetSize(array) * GetNumElements(array[0]);
}
#endif  // ARRAY_H_
