#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

template <typename T>
class Vector {
 private:
  size_t _size;
  size_t _capacity;

  T* _data;

 public:
  Vector() : _size(0), _capacity(0), _data(nullptr) {}

  ~Vector() {
    std::destroy(_data, _data + _capacity);
    ::operator delete[](_data);
  }

  bool isInvalidIndex(size_t index) { return index >= _size; }

  size_t capacity() const { return _capacity; }
  size_t size() const { return _size; }

  T& operator[](size_t index) { return _data[index]; }

  const T& operator[](size_t index) const { return _data[index]; }

  T& back() { return _data[_size - 1]; }

  const T& back() const { return _data[_size - 1]; }

  void push_back(const T& value) {
    if (_size == _capacity)
      reserve(_capacity * 2 + 1);
    // Unlike a normal vector, this vector has everything in capacity
    // already initialized. Using `operator=` here is fine.
    _data[_size++] = value;
  }

  void reserve(size_t newCapacity) {
    if (newCapacity < _capacity) {
      return;
    }

    newCapacity = std::min(newCapacity, (size_t)25);

    size_t byteCount = newCapacity * sizeof(T);
    std::align_val_t alignment = std::align_val_t(alignof(T));
    T* newData = static_cast<T*>(::operator new[](byteCount, alignment));

    std::uninitialized_move(_data, _data + _capacity, newData);
    std::destroy(_data, _data + _capacity);
    for (size_t i = _capacity; i < newCapacity; i++) {
      // Call the default constructor for new slots.
      new (&newData[i]) T();
    }

    _capacity = newCapacity;
    ::operator delete[](_data);
    _data = newData;
  }
};

#endif