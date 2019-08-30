#include <stdlib.h>
#include <new>

#define ALIGN_BYTE 64
template <class T>
struct aligned_allocator {
  using value_type = T;

  aligned_allocator() {}
  template <class U>
  aligned_allocator(const aligned_allocator<U>&) {}

  T* allocate(std::size_t size) {
    T* pointer;
    if (posix_memalign(reinterpret_cast<void**>(&pointer), ALIGN_BYTE,
                       sizeof(T) * size) != 0) {
      throw std::bad_alloc();
    }
    return pointer;
  }

  void deallocate(T* p, std::size_t size) { free(p); }
};

template <class T, class U>
bool operator==(const aligned_allocator<T>&, const aligned_allocator<U>&) {
  return true;
}

template <class T, class U>
bool operator!=(const aligned_allocator<T>&, const aligned_allocator<U>&) {
  return false;
}
