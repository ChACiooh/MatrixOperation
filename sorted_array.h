#ifndef SORTED_ARRAY_H_INCLUDED
#define SORTED_ARRAY_H_INCLUDED

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
class SortedArray {
 public:
  SortedArray();
  SortedArray(const SortedArray& a);
  SortedArray(size_t size);
  ~SortedArray();
  SortedArray& operator=(const SortedArray& a);

  size_t size() const { return size_; }
  const T& operator()(int idx) const;

  void Reserve(int size);  // 주어진 크기만큼 미리 메모리 할당.
  void Add(const T& value);

  int Find(const T& value);  // 주어진 값의 위치, 없으면 -1을 리턴.

private:
  T* values_;
  int size_, alloc_;
  // operator 함수들을 friend 로 선언하지 말고 public 함수를 이용.
};

template <typename T>
SortedArray<T>::SortedArray():values_(NULL), size_(0), alloc_(0) {}
template <typename T>
SortedArray<T>::SortedArray(const SortedArray& a)
{
    size_ = a.size_;
    alloc_ = a.alloc_;
    values_ = new T[alloc_];
    for(int i=0;i<size_;i++)
        values_[i] = a.values_[i];
}
template <typename T>
SortedArray<T>::SortedArray(size_t size):values_(new T[size]), size_(size), alloc_(size) {}
template <typename T>
SortedArray<T>::~SortedArray() { delete[] values_; }
template <typename T>
SortedArray<T>& SortedArray<T>::operator=(const SortedArray<T>& a)
{
    delete[] values_;
    size_ = a.size_;
    alloc_ = a.alloc_;
    values_ = new T[alloc_];
    for(int i=0;i<size_;i++)
        values_[i] = a.values_[i];
    return *this;
}
template <typename T>
const T& SortedArray<T>::operator()(int idx) const
{
    //Suggest that there's no exception.
    return *(values_+idx);
}

template <typename T>
void SortedArray<T>::Reserve(int size)
{
    // This function works role of resize too.
    if(size<=alloc_)    return;
    T* temp = new T[alloc_ = size];
    for(int i=0;i<size_;i++)
        temp[i] = values_[i];
    delete[] values_;
    values_ = temp;
}
template <typename T>
void SortedArray<T>::Add(const T& value)
{
    if(size_ == alloc_)
    {
        T* new_vals = new T[size_+1];
        for(int i=0;i<size_;i++)
            new_vals[i] = values_[i];
        delete[] values_;
        new_vals[size_] = value;
        values_ = new_vals;
        size_++;    alloc_++;
    }
    else    values_[size_++] = value;
    sort(values_, values_+size_);
}
template <typename T>
int SortedArray<T>::Find(const T& value)
{
    int start = -1, end = size_;
    int mid = (start+end)/2;
    while(mid != start && mid != end)
    {
        if(values_[mid] > value)    end = mid;
        else if(values_[mid] < value)   start = mid;
        else    return mid;
        mid = (start+end)/2;
    }
    return -1;
}


template <typename T>
istream& operator>>(istream& is, SortedArray<T>& a)
{
    int num;
    is >> num;
    a.Reserve(num);
    for(int i=0;i<num;i++)
    {
        T data;
        is >> data;
        a.Add(data);
    }
    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const SortedArray<T>& a)
{
    for(size_t i=0;i<a.size();i++) os << a(i) << " ";
    return os;
}


#endif // SORTED_ARRAY_H_INCLUDED
