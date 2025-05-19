//
// Created by Konstantin Okriashvili on 19.05.2025.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

class MatrixSchet : public std::logic_error {
 public:
  MatrixSchet() : std::logic_error("Размеры матриц некорректны") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("Вышли за пределы") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T matrix[N][M];
  size_t RowsNumber() const {
    return N;
  }
  size_t ColumnsNumber() const {
    return M;
  }
  T& operator()(size_t row, size_t column) {
    return matrix[row][column];
  }
  const T& operator()(size_t i, size_t j) const {
    return matrix[i][j];
  }

  T& At(size_t i, size_t j) {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange{};
    }
    return matrix[i][j];
  }

  const T& At(size_t i, size_t j) const {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange{};
    }

    return matrix[i][j];
  }

  Matrix<T, N, M>& operator+=(const Matrix& mtr2) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        (*this)(i, j) += mtr2(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator-=(const Matrix& mtr2) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        (*this)(i, j) -= mtr2(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator*=(const Matrix<T, M, M>& mtr2) {
    Matrix<T, N, M> prom;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        T sum{};
        for (size_t k = 0; k < M; k++) {
          sum += (*this)(i, k) * mtr2(k, j);
        }
        prom(i, j) = sum;
      }
    }
    *this = prom;
    return *this;
  }

  Matrix& operator*=(const T& znach) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        (*this)(i, j) *= znach;
      }
    }
    return *this;
  }

  Matrix& operator/=(const T& znach) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        (*this)(i, j) /= znach;
      }
    }
    return *this;
  }
};

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M> operator*(const S& znach, const Matrix<T, N, M>& mtr1) {
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      res(i, j) = static_cast<T>(znach) * mtr1(i, j);
    }
  }
  return res;
}

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M> operator*(const Matrix<T, N, M>& mtr1, const S& znach) {
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      res(i, j) = mtr1(i, j) * static_cast<T>(znach);
    }
  }

  return res;
}

template <class T, size_t N, size_t M, class S>
Matrix<T, N, M> operator/(const Matrix<T, N, M>& mtr1, const S& znach) {
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      res(i, j) = mtr1(i, j) / static_cast<T>(znach);
    }
  }
  return res;
}

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& mtr1) {
  Matrix<T, M, N> res;
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      res(i, j) = mtr1(j, i);
    }
  }
  return res;
}

template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& matr) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      if (j + 1 < M) {
        os << matr(i, j) << " ";
      }
      else {
        os << matr(i, j) << "\n";
      }
    }
  }
  return os;
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& is, Matrix<T, N, M>& mat) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      is >> mat(i, j);
    }
  }
  return is;
}

template <class T, size_t N, size_t M>
bool operator==(const Matrix<T, N, M>& mtr1, const Matrix<T, N, M>& mtr2) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      if (mtr1(i, j) != mtr2(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <class T, size_t N, size_t M>
bool operator!=(const Matrix<T, N, M>& mtr1, const Matrix<T, N, M>& mtr2) {
  return !(mtr1 == mtr2);
}

template <class T, size_t N, size_t M, size_t O, size_t P>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& mtr1, const Matrix<T, O, P>& mtr2) {
  if (N != O || M != P) {
    throw MatrixSchet{};
  }
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      res(i, j) = mtr1(i, j) + mtr2(i, j);
    }
  }
  return res;
}

template <class T, size_t N, size_t M, size_t O, size_t P>
Matrix<T, N, M> operator-(const Matrix<T, N, M>& mtr1, const Matrix<T, O, P>& mtr2) {
  if (N != O || M != P) {
    throw MatrixSchet{};
  }
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      res(i, j) = mtr1(i, j) - mtr2(i, j);
    }
  }
  return res;
}

template <class T, size_t N, size_t M, size_t O, size_t P>
Matrix<T, N, P> operator*(const Matrix<T, N, M>& mtr1, const Matrix<T, O, P>& mtr2) {
  if (M != O) {
    throw MatrixSchet{};
  }
  Matrix<T, N, P> res;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < P; j++) {
      T prom{};
      for (size_t k = 0; k < M; k++) {
        prom += mtr1(i, k) * mtr2(k, j);
      }
      res(i, j) = prom;
    }
  }
  return res;
}

// Доп часть будет;

#endif  // MATRIX_H