//
// Created by Konstantin Okriashvili on 19.05.2025.
//

#ifndef ARRAY_H
#define ARRAY_H
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
public:
  ArrayOutOfRange() : std::out_of_range("Вышлт за предел"){}
};

template <typename T, size_t N>
class Array {
public:
  T arr[N];
  T& operator[](size_t i) {
    return arr[i];
  }
  const T& operator[](size_t i) const {
    return arr[i];
  }
  T& At(size_t idx) {
    if (idx < N) {
      return arr[idx];
    }
    throw ArrayOutOfRange{};
  }
  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return arr[idx];
  }

  T& Front() {
    return arr[0];
  }

  T& Back() {
    return arr[N - 1];
  }

  const T& Front() const {
    return arr[0];
  }

  const T& Back() const {
    return arr[N - 1];
  }

  size_t Size() const {
    size_t i = 0;
    while (i != N) {
      i++;
    }
    return i;
  }

  bool Empty() const {
    return N == 0;
  }
  T* Data() {
    return arr;
  }
  const T* Data() const {
    return arr;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; i++) {
      arr[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; i++) {
      T tmp = arr[i];
      arr[i] = other[i];
      other[i] = tmp;
    }
  }

};

//Доп часть позже


#endif //ARRAY_H
