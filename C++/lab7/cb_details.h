#pragma once

#include <iterator>
#include <memory>
#include <cassert>


#if defined(__GNUC__)
#define LIKELY(x) __builtin_expect(x, 1)
#define UNLIKELY(x) __builtin_expect(x, 0)
#elif defined(__clang__) && !defined(__c2__) && defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define LIKELY(x) __builtin_expect(x, 1)
#define UNLIKELY(x) __builtin_expect(x, 0)
#endif
#endif

#ifndef LIKELY
#define LIKELY(expr) (expr)
#endif // !LIKELY

#ifndef UNLIKELY
#define UNLIKELY(expr) (expr)
#endif // !UNLIKELY


namespace cb_details
{

    template<class Traits>
    struct nonconst_traits
    {
        using value_type      = typename Traits::value_type;
        using pointer         = typename Traits::pointer;
        using reference       = typename Traits::value_type&;
        using size_type       = typename Traits::size_type;
        using difference_type = typename Traits::difference_type;

        using nonconst_self   = nonconst_traits<Traits>;
    };

    template<class Traits>
    struct const_traits
    {
        using value_type      = typename Traits::value_type;
        using pointer         = typename Traits::const_pointer;
        using reference       = const typename Traits::value_type&;
        using size_type       = typename Traits::size_type;
        using difference_type = typename Traits::difference_type;

        using nonconst_self   = nonconst_traits<Traits>;
    };

    template<class Buff, class Traits>
    struct iterator :
            public std::iterator<
                    std::random_access_iterator_tag,
                    typename Traits::value_type,
                    typename Traits::difference_type,
                    typename Traits::pointer,
                    typename Traits::reference>
    {
        using base_iterator = std::iterator<
                std::random_access_iterator_tag,
                typename Traits::value_type,
                typename Traits::difference_type,
                typename Traits::pointer,
                typename Traits::reference>;

        using nonconst_self = iterator<Buff, typename Traits::nonconst_self>;

        /// Basic types

        using value_type      = typename base_iterator::value_type;
        using pointer         = typename base_iterator::pointer;
        using reference       = typename base_iterator::reference;
        using size_type       = typename Traits::size_type;
        using difference_type = typename base_iterator::difference_type;

        /// Member variables

        const Buff* _buff;
        pointer     _it;

        /// Construction & assignment

        iterator() noexcept : _buff(0), _it(0) {}
        iterator(const nonconst_self& it) noexcept : _buff(it._buff), _it(it._it) {}
        iterator(const Buff* cb, const pointer p) noexcept : _buff(cb), _it(p) {}

        iterator& operator =(const iterator& it) noexcept
        {
            if ( UNLIKELY(this == &it) )
                return *this;
            _buff = it._buff;
            _it = it._it;
            return *this;
        }

        /// Random access iterator methods

        reference operator *() const
        {
            assert(_it != nullptr);
            return *_it;
        }

        pointer operator ->() const noexcept { return &( operator*() ); }

        iterator& operator ++()
        {
            assert(_it != nullptr);
            _buff->increment(_it);
            if ( UNLIKELY(_it == _buff->_last) )
                _it = nullptr;
            return *this;
        }

        iterator operator ++(int) noexcept
        {
            iterator<Buff, Traits> tmp = *this;
            ++*this;
            return tmp;
        }

        iterator& operator --()
        {
            assert(_it != _buff->_first);
            if ( UNLIKELY(_it == 0) )
                _it = _buff->_last;
            _buff->decrement(_it);
            return *this;
        }

        iterator operator --(int) noexcept
        {
            iterator<Buff, Traits> tmp = *this;
            --*this;
            return tmp;
        }

        iterator& operator +=(difference_type n) noexcept
        {
            if ( LIKELY(n > 0) )
            {
                _it = _buff->add(_it, n);
                if ( UNLIKELY(_it == _buff->_last) )
                    _it = nullptr;
            }
            else if (n < 0)
                *this -= -n;
            return *this;
        }

        iterator operator +(difference_type n) const noexcept { return iterator<Buff, Traits>(*this) += n; }

        iterator& operator -=(difference_type n) noexcept
        {
            if ( UNLIKELY(n > 0) )
                _it = _buff->sub(UNLIKELY(_it == nullptr) ? _buff->_last : _it, n);
            else if (n < 0)
                *this += -n;
            return *this;
        }

        iterator operator -(difference_type n) const noexcept { return iterator<Buff, Traits>(*this) -= n; }

        reference operator [](difference_type n) const noexcept { return *(*this + n); }

        /// Equality & comparison

        template<class Traits0>
        bool operator ==(const iterator<Buff, Traits0>& it) const noexcept { return _it == it._it; }

        template<class Traits0>
        bool operator !=(const iterator<Buff, Traits0>& it) const  noexcept{ return _it != it._it; }

        template<class Traits0>
        bool operator <(const iterator<Buff, Traits0>& it) const noexcept { return *this < it; }

        template<class Traits0>
        bool operator >(const iterator<Buff, Traits0>& it) const noexcept { return it < *this; }

        template<class Traits0>
        bool operator <=(const iterator<Buff, Traits0>& it) const noexcept { return !(it < *this); }

        template<class Traits0>
        bool operator >=(const iterator<Buff, Traits0>& it) const noexcept { return !(*this < it); }
    };

    /// Helper method

    template<class InputIterator, class ForwardIterator, class Alloc>
    ForwardIterator copy(InputIterator first,
                         InputIterator last,
                         ForwardIterator dest,
                         Alloc& a)
    {
        ForwardIterator next = dest;
        try
        {
            for (; first != last; ++first, ++dest)
                std::allocator_traits<Alloc>::construct(a, std::addressof(*dest), *first);
        }
        catch (...)
        {
            for (; next != dest; ++next)
                std::allocator_traits<Alloc>::destroy(a, std::addressof(*next));
            throw;
        }
        return dest;
    }

}  // !namespace cb_details