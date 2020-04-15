#pragma once

#include "cb_details.h"

#include <limits>
#include <algorithm>
#include <stdexcept>


#define MAX_ALLOC     std::allocator_traits<Alloc>::max_size(_alloc)
#define MAX_DIFF_TYPE std::numeric_limits<difference_type>::max()
#define MAX_SIZE      (std::min<size_type>)(MAX_ALLOC, (MAX_DIFF_TYPE))


template<class T, class Alloc = std::allocator<T>>
class circular_buffer
{
public:
/// Basic types

    using value_type      = typename std::allocator_traits<Alloc>::value_type;
    using pointer         = typename std::allocator_traits<Alloc>::pointer;
    using const_pointer   = typename std::allocator_traits<Alloc>::const_pointer;
    using reference       = typename std::allocator_traits<Alloc>::value_type&;
    using const_reference = const typename std::allocator_traits<Alloc>::value_type&;
    using difference_type = typename std::allocator_traits<Alloc>::difference_type;
    using size_type       = typename std::allocator_traits<Alloc>::size_type;
    using allocator_type  = Alloc;

    using capacity_type   = size_type;

    using const_iterator         = cb_details::iterator< circular_buffer<T, Alloc>,
            cb_details::const_traits<std::allocator_traits<Alloc>> >;
    using iterator               = cb_details::iterator< circular_buffer<T, Alloc>,
            cb_details::nonconst_traits<std::allocator_traits<Alloc>> >;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator       = std::reverse_iterator<iterator>;

    using param_value_type = const value_type&;
    using rvalue_type      = value_type&&;

private:
/// Member variables

    pointer        _buff;
    pointer        _end;
    pointer        _first;
    pointer        _last;
    size_type      _size;
    allocator_type _alloc;

/// Friends
    template<class Buff, class Traits> friend struct cb_details::iterator;

public:
/// Allocator

    [[nodiscard]] allocator_type get_allocator() const noexcept { return _alloc; }
    allocator_type& get_allocator() noexcept { return _alloc; }

/// Element access

    iterator begin() noexcept { return iterator(this, UNLIKELY(size() == 0) ? nullptr : _first); }
    iterator end() noexcept { return iterator(this, nullptr); }

    [[nodiscard]] const_iterator begin() const noexcept
    {
        return const_iterator(this, UNLIKELY(size() == 0) ? nullptr : _first);
    }
    [[nodiscard]] const_iterator end() const noexcept { return const_iterator(this, nullptr); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    [[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    [[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    reference operator [](size_type index)
    {
        assert( index < size() );
        return *add(_first, index);
    }
    const_reference operator [](size_type index) const
    {
        assert( index < size() );
        return *add(_first, index);
    }

/// Size and capacity

    [[nodiscard]] size_type size() const noexcept { return _size; }
    [[nodiscard]] capacity_type capacity() const noexcept { return _end - _buff; }

    void set_capacity(capacity_type new_capacity)
    {
        if ( UNLIKELY(new_capacity == capacity()) )
            return;
        pointer buff = allocate(new_capacity);
        iterator b = begin();
        try
        {
            reset(buff,
                  cb_details::copy(b, b + (std::min)(new_capacity, size()), buff, _alloc),
                  new_capacity);
        }
        catch(...)
        {
            deallocate(buff, new_capacity);
            throw;
        }
    }

/// Construction/Destruction

    explicit circular_buffer( const allocator_type& alloc = allocator_type() ) noexcept
            : _buff(0), _end(0), _first(0), _last(0), _size(0), _alloc(alloc) {}

    explicit circular_buffer( capacity_type buffer_capacity,
                              const allocator_type& alloc = allocator_type() )
            : _size(0), _alloc(alloc)
    {
        initialize_buffer(buffer_capacity);
        _first = _last = _buff;
    }

    circular_buffer( size_type n, param_value_type item, const allocator_type& alloc = allocator_type() )
            : _size(n), _alloc(alloc)
    {
        initialize_buffer(n, item);
        _first = _last = _buff;
    }

    circular_buffer( capacity_type buffer_capacity, size_type n, param_value_type item,
                     const allocator_type& alloc = allocator_type() )
            : _size(n), _alloc(alloc)
    {
        assert( buffer_capacity >= size() );
        initialize_buffer(buffer_capacity, item);
        _first = _buff;
        _last = LIKELY(buffer_capacity == n) ? _buff : _buff + n;
    }

    circular_buffer(const circular_buffer<T, Alloc>& cb)
            : _size( cb.size() ), _alloc( cb.get_allocator() )
    {
        initialize_buffer( cb.capacity() );
        _first = _buff;
        try
        {
            _last = cb_details::copy(cb.begin(), cb.end(), _buff, _alloc);
        }
        catch(...)
        {
            deallocate( _buff, cb.capacity() );
            throw;
        }
        if ( UNLIKELY(_last == _end) )
            _last = _buff;
    }

    circular_buffer(circular_buffer<T, Alloc>&& cb) noexcept
            : _buff(0), _end(0), _first(0), _last(0), _size(0), _alloc( cb.get_allocator() )
    {
        cb.swap(*this);
    }

    ~circular_buffer()
    {
        destroy();
    }

public:
/// Assign methods
    circular_buffer<T, Alloc>& operator =(const circular_buffer<T, Alloc>& cb)
    {
        if ( UNLIKELY(this == &cb) )
            return *this;
        pointer buff = allocate( cb.capacity() );
        try
        {
            reset(buff,
                  cb_details::copy(cb.begin(), cb.end(), buff, _alloc),
                  cb.capacity() );
        }
        catch(...)
        {
            deallocate( buff, cb.capacity() );
            throw;
        }
        return *this;
    }

    circular_buffer<T, Alloc>& operator =(circular_buffer<T, Alloc>&& cb) noexcept
    {
        cb.swap(*this);
        circular_buffer<T, Alloc>( get_allocator() ).swap(cb);
        return *this;
    }

/// push and pop
private:
    template<class ValT>
    void push_back_impl(ValT item)
    {
        if ( LIKELY(capacity() == size() ))
        {
            if ( UNLIKELY(size() == 0) )
                return;
            replace( _last, static_cast<ValT>(item) );
            increment(_last);
            _first = _last;
        }
        else
        {
            std::allocator_traits<Alloc>::construct(_alloc,
                                                    std::addressof(*_last), static_cast<ValT>(item));
            increment(_last);
            ++_size;
        }
    }

    template<class ValT>
    void push_front_impl(ValT item)
    {
        try
        {
            if ( LIKELY(capacity() == size() ))
            {
                if ( UNLIKELY(size() == 0) )
                    return;
                decrement(_first);
                replace( _first, static_cast<ValT>(item) );
                _last = _first;
            }
            else
            {
                decrement(_first);
                std::allocator_traits<Alloc>::construct(_alloc,
                                                        std::addressof(*_first), static_cast<ValT>(item));
                ++_size;
            }
        }
        catch(...)
        {
            increment(_first);
            throw;
        }
    }

public:
    void push_back(param_value_type item)
    {
        push_back_impl<param_value_type>(item);
    }

    void push_back(rvalue_type item)
    {
        push_back_impl<rvalue_type>( std::move(item) );
    }

    void push_front(param_value_type item)
    {
        push_front_impl<param_value_type>(item);
    }

    void push_front(rvalue_type item)
    {
        push_front_impl<rvalue_type>( std::move(item) );
    }

    void pop_back()
    {
        assert(size() != 0);
        decrement(_last);
        std::allocator_traits<Alloc>::destroy( _alloc, std::addressof(*_last) );
        --_size;
    }

    void pop_front()
    {
        assert(size() != 0);
        increment(_first);
        --_size;
    }

private:
    template<class ValT>
    iterator insert_impl(iterator pos, ValT item)
    {
        iterator b = begin();
        if ( UNLIKELY(capacity() == size() && pos == b) )
            return b;
        return insert_item<ValT>( pos, static_cast<ValT>(item) );
    }

public:
/// Insert

    iterator insert(iterator pos, param_value_type item)
    {
        return insert_impl<param_value_type>(pos, item);
    }

    iterator insert(iterator pos, rvalue_type item)
    {
        return insert_impl<rvalue_type>( pos, std::move(item) );
    }

/// Erase

    iterator erase(iterator pos)
    {
        assert(pos._it != nullptr);
        pointer next = pos._it;
        increment(next);
        for ( pointer p = pos._it; next != _last; p = next, increment(next) )
            replace( p, std::move_if_noexcept(*next) );
        decrement(_last);
        std::allocator_traits<Alloc>::destroy( _alloc, std::addressof(*_last) );
        --_size;
        return UNLIKELY(_last == pos._it) ? end() : pos;
    }

private:
/// Helper methods

    template<class Pointer>
    void increment(Pointer& p) const noexcept
    {
        if (++p == _end)
            p = _buff;
    }

    template<class Pointer>
    void decrement(Pointer& p) const noexcept
    {
        if (p == _buff)
            p = _end;
        --p;
    }

    template<class Pointer>
    Pointer add(Pointer p, difference_type n) const noexcept
    {
        return p + ( n < (_end - p) ? n : n - capacity() );
    }

    template<class Pointer>
    Pointer sub(Pointer p, difference_type n) const noexcept
    {
        return p - (n > (p - _buff) ? n - capacity() : n);
    }

    pointer allocate(size_type n)
    {
        if ( UNLIKELY(n > MAX_SIZE) )
            throw std::length_error("circular_buffer");
        return (n == 0) ? nullptr : _alloc.allocate(n);
    }

    void deallocate(pointer p, size_type n)
    {
        if (p != nullptr)
            _alloc.deallocate(p, n);
    }

    void replace(pointer pos, param_value_type item) noexcept
    {
        *pos = item;
    }

    void replace(pointer pos, rvalue_type item) noexcept
    {
        *pos = std::move(item);
    }

    void construct_or_replace(bool construct, pointer pos, param_value_type item) noexcept
    {
        construct ?
        std::allocator_traits<Alloc>::construct(_alloc, std::addressof(*pos), item)
                  : replace(pos, item);
    }

    void construct_or_replace(bool construct, pointer pos, rvalue_type item)  noexcept
    {
        construct ?
        std::allocator_traits<Alloc>::construct( _alloc, std::addressof(*pos), std::move(item) )
                  : replace( pos, std::move(item) );
    }

    void destroy()
    {
        for ( size_type i = 0; i < size(); ++i, increment(_first) )
            std::allocator_traits<Alloc>::destroy( _alloc, std::addressof(*_first) );
        deallocate( _buff, capacity() );
    }

    void initialize_buffer(capacity_type buffer_capacity)
    {
        _buff = allocate(buffer_capacity);
        _end = _buff + buffer_capacity;
    }

    void initialize_buffer(capacity_type buffer_capacity, param_value_type item)
    {
        initialize_buffer(buffer_capacity);
        try
        {
            auto next = _buff;
            try
            {
                for (; size() > 0; ++_buff, --size())
                    std::allocator_traits<Alloc>::construct(_alloc, std::addressof(*_buff), item);
            }
            catch (...)
            {
                for (; next != _buff; ++next)
                    std::allocator_traits<Alloc>::destroy(_alloc, std::addressof(*next));
                throw;
            }
        } catch(...) {
            deallocate(_buff, size());
            throw;
        }
    }

    void reset(pointer buff, pointer last, capacity_type new_capacity)
    {
        destroy();
        _size = last - buff;
        _first = _buff = buff;
        _end = _buff + new_capacity;
        _last = last == _end ? _buff : last;
    }

    template<class ValT>
    iterator insert_item(const iterator& pos, ValT item)
    {
        pointer p = pos._it;
        if ( UNLIKELY(p == nullptr) )
        {
            construct_or_replace(capacity() != size(), _last, static_cast<ValT>(item));
            p = _last;
        }
        else
        {
            pointer src = _last;
            pointer dest = _last;
            bool construct = capacity() != size();
            try
            {
                while (src != p)
                {
                    decrement(src);
                    construct_or_replace(construct, dest, std::move_if_noexcept(*src));
                    decrement(dest);
                    construct = false;
                }
                replace(p, static_cast<ValT>(item));
            }
            catch(...)
            {
                if (!construct && capacity() != size())
                {
                    increment(_last);
                    ++_size;
                }
                throw;
            }
        }
        increment(_last);
        if ( LIKELY(capacity() == size()) )
            _first = _last;
        else
            ++_size;
        return iterator(this, p);
    }

    void swap(circular_buffer<T, Alloc>& cb) noexcept
    {
        std::swap(_buff,  cb._buff);
        std::swap(_end,   cb._end);
        std::swap(_first, cb._first);
        std::swap(_last,  cb._last);
        std::swap(_size,  cb._size);
    }

};  // !class circular_buffer