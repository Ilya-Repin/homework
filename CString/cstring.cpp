#include "cstring.h"

size_t Strlen(const char *str) {
  size_t i = 0;

  while (str[i] != '\0') {
    ++i;
  }

  return i;
}

int Strcmp(const char *first, const char *second) {
  size_t a = 0;
  size_t b = 0;

  while (first[a] && second[b]) {
    if (first[a] < second[b]) {
      return -1;
    }

    if (first[a] > second[b]) {
      return 1;
    }

    ++a;
    ++b;
  }

  int lf = Strlen(first);
  int ls = Strlen(second);

  return ((lf == ls) ? 0 : (lf < ls) ? -1 : 1);
}

int Strncmp(const char *first, const char *second, size_t count) {
  size_t a = 0;
  size_t b = 0;

  while (a < count && b < count && first[a] && second[b]) {
    if (first[a] < second[b]) {
      return -1;
    }

    if (first[a] > second[b]) {
      return 1;
    }

    ++a;
    ++b;
  }

  return ((a == b) ? 0 : (a < b) ? -1 : 1);
}

char *Strcpy(char *dest, const char *src) {
  size_t i = 0;

  while (src[i] != '\0') {
    dest[i] = src[i];
    ++i;
  }

  dest[i] = src[i];
  return dest;
}

char *Strncpy(char *dest, const char *src, size_t count) {
  size_t i = 0;

  while (count && src[i] != '\0') {
    dest[i] = src[i];
    ++i;
    --count;
  }

  if (count) {
    while (--count) {
      dest[i++] = '\0';
    }

    dest[i] = '\0';
  }

  return dest;
}

char *Strcat(char *dest, const char *src) {
  size_t len = Strlen(dest);
  size_t i = 0;

  while (src[i] != '\0') {
    dest[len++] = src[i++];
  }

  dest[len] = '\0';
  return dest;
}

char *Strncat(char *dest, const char *src, size_t count) {
  size_t len = Strlen(dest);
  size_t i = 0;

  while (i < count && src[i] != '\0') {
    dest[len++] = src[i++];
  }

  dest[len] = '\0';
  return dest;
}

const char *Strchr(const char *str, char symbol) {
  if (symbol == '\0') {
    return str + Strlen(str);
  }

  size_t i = 0;

  while (str[i] != '\0') {
    if (str[i] == symbol) {
      return (str + i);
    }

    ++i;
  }

  return nullptr;
}

const char *Strrchr(const char *str, char symbol) {
  if (symbol == '\0') {
    return str + Strlen(str);
  }

  size_t i = 0;
  size_t pos = 0;
  bool flag = false;

  while (str[i] != '\0') {
    if (str[i] == symbol) {
      pos = i;
      flag = true;
    }

    ++i;
  }

  return flag ? (str + pos) : nullptr;
}

size_t Strspn(const char *dest, const char *src) {
  size_t i = 0;

  while (dest[i] != '\0') {
    size_t j = 0;
    bool flag = false;

    while (src[j] != '\0') {
      if (dest[i] == src[j]) {
        flag = true;
        break;
      }

      ++j;
    }

    if (!flag) {
      return i;
    }

    ++i;
  }

  return i;
}

size_t Strcspn(const char *dest, const char *src) {
  size_t i = 0;

  while (dest[i] != '\0') {
    size_t j = 0;
    bool flag = false;

    while (src[j] != '\0') {
      if (dest[i] == src[j]) {
        flag = true;
        break;
      }

      ++j;
    }

    if (flag) {
      return i;
    }

    ++i;
  }

  return i;
}

const char *Strpbrk(const char *dest, const char *breakset) {
  size_t i = 0;

  while (dest[i] != '\0') {
    size_t j = 0;

    while (breakset[j] != '\0') {
      if (dest[i] == breakset[j]) {
        return (dest + i);
      }

      ++j;
    }

    ++i;
  }

  return nullptr;
}

const char *Strstr(const char *str, const char *pattern) {
  if (pattern[0] == '\0') {
    return str;
  }

  size_t i = 0;

  while (str[i] != '\0') {
    if (str[i] == pattern[0]) {
      size_t j = 0;

      while (pattern[j] != '\0') {
        if (str[i + j] != pattern[j]) {
          break;
        }

        ++j;
      }

      if (j == Strlen(pattern)) {
        return (str + i);
      }
    }

    ++i;
  }

  return nullptr;
}