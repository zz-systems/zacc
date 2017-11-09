//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------------


#pragma once

/**
 * @file memory.h
 * @brief utils for aligned memory
 */
#include <memory>



namespace zacc {

    /// @brief aligned allocator for std containers
    /// @see http://jmabille.github.io/blog/2014/12/06/aligned-memory-allocator/
    template<class T, int N>
    class aligned_allocator {

    public:

        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        template<class U>
        struct rebind {
            typedef aligned_allocator<U, N> other;
        };

        inline aligned_allocator() throw() { }

        inline aligned_allocator(const aligned_allocator &) throw() { }

        template<class U>
        inline aligned_allocator(const aligned_allocator<U, N> &) throw() { }

        inline ~aligned_allocator() throw() { }

        inline pointer address(reference r) { return &r; }

        inline const_pointer address(const_reference r) const { return &r; }

        pointer allocate(size_type n, typename std::allocator<void>::const_pointer hint = 0);

        inline void deallocate(pointer p, size_type);

        inline void construct(pointer p, const_reference value) { new(p) value_type(value); }

        inline void destroy(pointer p) { p->~value_type(); }

        inline size_type max_size() const throw() { return size_type(-1) / sizeof(T); }

        inline bool operator==(const aligned_allocator &) { return true; }

        inline bool operator!=(const aligned_allocator &rhs) { return !operator==(rhs); }
    };

    // TODO
    //template<class T>
    //aligned_allocator<T, std::enable_if<

    namespace detail
    {
        inline void* _aligned_malloc(size_t size, size_t alignment)
        {
            void* res = 0;
            void* ptr = malloc(size+alignment);
            if(ptr != 0)
            {
                res = reinterpret_cast<void*>((reinterpret_cast<size_t>(ptr) & ~(size_t(alignment-1))) + alignment);
                *(reinterpret_cast<void**>(res) - 1) = ptr;
            }
            return res;
        }
    }

    inline void* aligned_malloc(size_t size, size_t alignment)
    {
#if MALLOC_ALREADY_ALIGNED
        return malloc(size);
#elif HAS_MM_MALLOC
        return _mm_malloc(size,alignment);
#elif HAS_POSIX_MEMALIGN
        void* res;
        const int failed = posix_memalign(&res,size,alignment);
        if(failed) res = 0;
        return res;
#elif (defined _MSC_VER)
        return _aligned_malloc(size, alignment);
#else
        return detail::_aligned_malloc(size,alignment);
#endif
    }

    namespace detail
    {
        inline void _aligned_free(void* ptr)
        {
            if(ptr != 0)
                free(*(reinterpret_cast<void**>(ptr)-1));
        }
    }

    inline void aligned_free(void* ptr)
    {
#if MALLOC_ALREADY_ALIGNED
        free(ptr);
#elif HAS_MM_MALLOC
        _mm_free(ptr);
#elif HAS_POSIX_MEMALIGN
        free(ptr);
#elif defined(_MSC_VER)
        _aligned_free(ptr);
#else
        detail::_aligned_free(ptr);
#endif
    }

    template <class T, int N>
    typename aligned_allocator<T,N>::pointer
    aligned_allocator<T,N>::allocate(size_type n, typename std::allocator<void>::const_pointer)
    {
        pointer res = reinterpret_cast<pointer>(aligned_malloc(sizeof(T)*n,N));
        if(res == 0)
            throw std::bad_alloc();
        return res;
    }

    template <class T, int N>
    void
    aligned_allocator<T,N>::deallocate(pointer p, size_type)
    {
        aligned_free(p);
    }
    template<typename T, std::size_t align = std::alignment_of<T>::value, typename... Args>
    std::shared_ptr<T> make_shared(Args &&... args) {

        const std::size_t default_alignment = 16;

        if (align > default_alignment) {
            typedef aligned_allocator<T, align> alloc_type;
            return std::allocate_shared<T, alloc_type>(alloc_type(), std::forward<Args>(args)...);
        }
        else {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
    }
}