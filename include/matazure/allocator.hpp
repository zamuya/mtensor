#pragma once

#include <malloc.h>
#include <matazure/config.hpp>

namespace matazure {

template <typename _Type, int_t _Alignment>
class aligned_allocator : public std::allocator<_Type> {
   public:
    MATAZURE_GENERAL aligned_allocator() {}
    MATAZURE_GENERAL aligned_allocator(const aligned_allocator& rhs) {}
    MATAZURE_GENERAL aligned_allocator& operator=(const aligned_allocator& rhs) {}

    _Type* allocate(size_t size) {
#ifdef __GNUC__
        _Type* data = reinterpret_cast<_Type*>(memalign(_Alignment, size * sizeof(_Type)));
#else
        _Type* data = reinterpret_cast<_Type*>(_aligned_malloc(size * sizeof(_Type), _Alignment));
#endif
        return data;
    }

    void deallocate(_Type* p, size_t size) {
#ifdef __GNUC__
        free(p);
#else
        _aligned_free(p);
#endif
    }

    MATAZURE_GENERAL ~aligned_allocator(){};
};

}  // namespace matazure