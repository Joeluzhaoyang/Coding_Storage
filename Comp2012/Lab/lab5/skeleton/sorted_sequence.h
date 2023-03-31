#ifndef __SORTED_SEQUENCE__
#define __SORTED_SEQUENCE__

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class SortedSequence{
  public:
    SortedSequence() : capacity_(0), size_(0), data_(nullptr) {}
    ~SortedSequence() { delete[] data_; }

    void add(const T &a) {  // Task 2 - To Do
      if(this->data_ == nullptr)
      {
        T* data = new T[1];
        data_ = data;
        data[0] = a;
        capacity_ = 1;
        size_ = 1;
      }
      else
      {
        if(size_ == capacity_)
        {
          capacity_ *= 2;
        }
          T* data1 = new T[capacity_];
          for(int i = 0; i < size_;i++)//copy the old array
          {
            data1[i] = data_[i];
          }
          delete[] data_;

          int index = 0;
          for(; index < size_; index++)//find the location to insert
          {
            if( a<data1[index])
              break;
          }

          if(index == size_)
          {
            data1[size_] = a;
          }
          else
          {
            for(int i = size_-1; i != index-1;i--)
            {
              data1[i+1] = data1[i];
            }
            data1[index] = a;
          }

          data_ = data1;
          size_++;
      }
    }

    std::string toString() const {
      std::stringstream ss;
      ss << "capacity: " << capacity_ << ", size: " << size_
        << ", data: " << std::endl;
      if (data_ == nullptr) {
        ss << "None";
      } else {
        for (int i = 0; i < size_; i++) {
          ss << data_[i] << " ";
        }
      }
      return ss.str();
    }

  private:
    int capacity_;
    int size_;
    T *data_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const SortedSequence<T>& t) {
  os << t.toString();
  return os;
}

#endif 