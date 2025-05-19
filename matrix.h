//
// Created by Konstantin Okriashvili on 18.05.2025.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <string>

class MatrixSchet : public std::logic_error {
 public:
  MatrixSchet() : std::logic_error("Размеры матриц некорректны") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  explicit MatrixOutOfRange(const std::string& what_arg) : std::out_of_range(what_arg) {
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
  const T& At(size_t i, size_t j) const {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange("Вышли за пределы");
    }

    return matrix[i][j];
  }

  T& At(size_t i, size_t j) {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange("Вышли за пределы");
    }

    return matrix[i][j];
  }

  template <size_t O, size_t C>
  Matrix<T, N, M> operator+(const Matrix<T, O, C>& other_matrix) const {
    if ((N != O || M != C)) {
      throw MatrixSchet();
    }
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        result.matrix[i][j] = matrix[i][j] + other_matrix.matrix[i][j];
      }
    }
    return result;
  }

  template <size_t O, size_t C>
  Matrix<T, N, M> operator-(const Matrix<T, O, C>& mtr2) const {
    if ((N != O || M != C)) {
      throw MatrixSchet();
    }
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        result.matrix[i][j] = matrix[i][j] - mtr2.matrix[i][j];
      }
    }
    return result;
  }

  template <size_t O, size_t C>
  Matrix<T, N, C> operator*(const Matrix<T, O, C>& mtr2) const {
    if ((M != O)) {
      throw MatrixSchet();
    }
    Matrix<T, N, C> result;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < C; j++) {
        T prom = T();
        for (size_t k = 0; k < M; k++) {
          prom += matrix[i][k] * mtr2.matrix[k][j];
        }
        result.matrix[i][j] = prom;
      }
    }
    return result;
  }

  template <size_t O, size_t C>
  Matrix<T, N, M> operator+=(const Matrix<T, O, C>& mtr2) {
    if ((N != O || M != C)) {
      throw MatrixSchet();
    }
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        matrix[i][j] += mtr2.matrix[i][j];
      }
    }
    return *this;
  }

  template <size_t O, size_t C>
  Matrix<T, N, M> operator-=(const Matrix<T, O, C>& mtr2) {
    if ((N != O || M != C)) {
      throw MatrixSchet();
    }
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        matrix[i][j] -= mtr2.matrix[i][j];
      }
    }
    return *this;
  }

  template <size_t O, size_t C>
  Matrix<T, N, C> operator*=(const Matrix<T, O, C>& other_matrix) {
    if ((M != O)) {
      throw MatrixSchet();
    }
    Matrix<T,N,C> prom;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < C; j++) {
        T sum = T();
        for (size_t k = 0; k < M; k++) {
          sum += matrix[i][k] * other_matrix.matrix[k][j];
        }
        prom.matrix[i][j] = sum;
      }
    }
    *this = prom;
    return *this;
  }

  friend Matrix<T, N, M> operator*(const T& chisl, const Matrix<T, N, M>& matr) {
    return matr * chisl;
  }

  Matrix<T, N, M> operator*(const T& chisl) const {
    Matrix mtr;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        mtr.matrix[i][j] = this->matrix[i][j] * chisl;
      }
    }
    return mtr;
  }

  Matrix<T, N, M>& operator*=(const T& chisl) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        this->matrix[i][j] *= chisl;
      }
    }
    return *this;
  }

  Matrix<T, N, M> operator/(const T& chisl) {
    Matrix mtr1;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        mtr1.matrix[i][j] = this->matrix[i][j] / chisl;
      }
    }
    return mtr1;
  }

  Matrix& operator/=(const T& scalar) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] /= scalar;
      }
    }
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& matr) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        if (j + 1 < M) {
          os << matr.matrix[i][j] << " ";
        }
      }
      os << "\n";
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Matrix& mat) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        is >> mat.matrix[i][j];
      }
    }
    return is;
  }

  template <size_t O, size_t C>
  bool operator==(const Matrix<T, O, C>& mtr1) const {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        if (this->matrix[i][j] != mtr1.matrix[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  template <size_t O, size_t C>
  bool operator!=(const Matrix<T, O, C>& mtr2) const {
    return !(*this == mtr2);
  }

  friend Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& mtr2) {
    Matrix<T, M, N> res;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        res.matrix[i][j] = mtr2.matrix[j][i];
      }
    }
    return res;
  }
};

#endif  // MATRIX_H
