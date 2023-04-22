#ifndef STRING_VIEW_H_
#define STRING_VIEW_H_

#include <iostream>
#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  StringView();
  StringView(const char *ptr);  // NOLINT
  StringView(const char *ptr, size_t size);

  const char &operator[](size_t pos) const;
  const char &At(size_t pos) const;
  const char &Front() const;
  const char &Back() const;

  size_t Size() const;
  size_t Length() const;
  bool Empty() const;

  const char *Data() const;

  void Swap(StringView &sv);

  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);

  StringView Substr(size_t pos, size_t count = -1);

 private:
  const char *ptr_;
  size_t size_;
};
#endif  // STRING_VIEW_H_
