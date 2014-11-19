#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Matrix {
 public:
  Matrix();
  Matrix(const Matrix& m);
  Matrix(int rows, int cols);

  int rows() const { return rows_; }
  int cols() const { return cols_; }
  void Resize(int rows, int cols);

  T& operator()(int r, int c);
  const T& operator()(int r, int c) const;

  Matrix<T> operator+() const;
  Matrix<T> operator-() const;
  Matrix<T> Transpose() const;

 private:
  // 행과 열을 받아 해당 원소의 배열 내의 위치를 계산하는 함수.
  int Sub2Ind(int r, int c) const { return r + c * rows_; }

  vector<T> values_;  // rows_ * cols_ 만큼의 정수를 가진 배열.
  int rows_, cols_;   // 행과 열의 개수.

  // operator 함수들을 friend 로 선언하지 말고 public 함수를 이용.
};

template <typename T>
inline Matrix<T>::Matrix():values_(), rows_(0), cols_(0) {}
template <typename T>
inline Matrix<T>::Matrix(const Matrix& m):values_(m.values_), rows_(m.rows_), cols_(m.cols_) {}
template <typename T>
inline Matrix<T>::Matrix(int rows, int cols) { values_.resize((rows_ = rows)*(cols_ = cols)); }
template <typename T>
inline void Matrix<T>::Resize(int rows, int cols)
{
    vector<T> tmp = values_;
    values_.resize(rows*cols);
    /*for(int i=0;i<rows && i<rows_;i++)
        for(int j=0;j<cols && j<cols_;j++)
            values_[i*cols+j] = tmp[i*cols_+j];
    rows_ = rows;
    cols_ = cols;*/
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(i<rows && i<rows_ && j<cols && j<cols_)
                values_[i*cols+j] = tmp[i*cols_+j];
            else    values_[i*cols +j ] = 0;
        }
    }
    rows_ = rows;
    cols_ = cols;
}
template <typename T>
inline T& Matrix<T>::operator()(int r, int c) { return values_[r*cols_+c]; }
template <typename T>
inline const T& Matrix<T>::operator()(int r, int c) const { return values_[r*cols_+c]; }
template <typename T>
inline Matrix<T> Matrix<T>::operator+() const { return *this; }
template <typename T>
inline Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> res(rows_, cols_);
    for(size_t i=0; i<values_.size(); i++)
        res.values_[i] = -values_[i];
    return res;
}
template <typename T>
inline Matrix<T> Matrix<T>::Transpose() const
{
    Matrix<T> res(cols_, rows_);
    for(int i=0;i<cols_;i++)
        for(int j=0;j<rows_;j++)
            res(i, j) = operator()(j, i);
    return res;
}

template <typename T>
istream& operator>>(istream& is, Matrix<T>& m)
{
    int row, col;
    is >> row >> col;
    m.Resize(row, col);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            int num;
            is >> num;
            m(i, j) = num;
            //cout << i << ", " << j << ":" << m(i,j) << endl;
        }
    }
    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const Matrix<T>& m)
{
    for(int i=0;i<m.rows();i++)
    {
        for(int j=0;j<m.cols();j++) os << m(i,j) << " ";
        os << endl;
    }
    return os;
}

template <typename T, typename S>
Matrix<T> operator+(const Matrix<T>& lm, const Matrix<S>& rm)
{
    //Suggest the number of cols and rows of lm and rm is same each
    Matrix<T> res(lm.rows(), lm.cols());
    for(int i=0;i<res.rows();i++)
    {
        for(int j=0;j<res.cols();j++)
            res(i,j) = lm(i,j) + rm(i,j);
    }
    return res;
}

template <typename T, typename S>
Matrix<T> operator-(const Matrix<T>& lm, const Matrix<S>& rm)
{
   //Suggest the number of cols and rows of lm and rm is same each
    Matrix<T> res(lm.rows(), lm.cols());
    for(int i=0;i<res.rows();i++)
    {
        for(int j=0;j<res.cols();j++)
            res(i,j) = lm(i,j) - rm(i,j);
    }
    return res;
}

template <typename T, typename S>
Matrix<T> operator*(const Matrix<T>& lm, const Matrix<S>& rm)
{
    Matrix<T> res(lm.rows(), rm.cols());
    for(int i=0;i<lm.rows();i++)
    {
        for(int j=0;j<rm.cols();j++)
        {
            res(i,j) = 0;
            for(int k=0;k<rm.rows();k++)
                res(i,j) += lm(i,k) * rm(k, j);
        }
    }
    return res;
}

template <typename T, typename S>
Matrix<T> operator+(const S& a, const Matrix<T>& rm)
{
    Matrix<T> res(rm);
    for(int i=0;i<res.rows();i++)
        for(int j=0;j<res.cols();j++)
            res(i,j) += a;
    return res;
}

template <typename T, typename S>
Matrix<T> operator-(const S& a, const Matrix<T>& rm)
{
    Matrix<T> res(rm);
    for(int i=0;i<res.rows();i++)
        for(int j=0;j<res.cols();j++)
            res(i,j) -= a;
    return res;
}

template <typename T, typename S>
Matrix<T> operator*(const S& a, const Matrix<T>& rm)
{
    Matrix<T> res(rm);
    for(int i=0;i<res.rows();i++)
        for(int j=0;j<res.cols();j++)
            res(i,j) *= a;
    return res;
}

template <typename T, typename S>
Matrix<T> operator+(const Matrix<T>& lm, const S& a)
{
    Matrix<T> res(lm);
    for(int i=0;i<res.rows();i++)
        for(int j=0;j<res.cols();j++)
            res(i,j) += a;
    return res;
}

template <typename T, typename S>
Matrix<T> operator-(const Matrix<T>& lm, const S& a)
{
    Matrix<T> res(lm);
    for(int i=0;i<res.rows();i++)
        for(int j=0;j<res.cols();j++)
            res(i,j) -= a;
    return res;
}

template <typename T, typename S>
Matrix<T> operator*(const Matrix<T>& lm, const S& a)
{
    Matrix<T> res(lm);
    for(int i=0;i<res.rows();i++)
        for(int j=0;j<res.cols();j++)
            res(i,j) *= a;
    return res;
}

#endif // MATRIX_H_INCLUDED
