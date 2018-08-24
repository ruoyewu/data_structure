//
// Created by 张群 on 2018/8/21.
//

#ifndef DATA_STRUCTURE_ARRAY_LIST_H
#define DATA_STRUCTURE_ARRAY_LIST_H

#include <memory>
#include <iostream>
#include <algorithm>

template <class T, class Alloc=std::allocator<T>>
class array_list {
public:
    typedef T value_type;
    typedef const value_type const_value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    std::allocator<value_type> _alloc;
    iterator _start;
    iterator _end;
    iterator _end_of_storage;

public:
    /**
     * 构造函数
     */
    array_list() :_start(0), _end(0), _end_of_storage(0){}
    array_list(size_type n, const_value_type value);
    explicit array_list(size_type n);
    array_list(iterator first, iterator last);
    array_list(const array_list& list);
    array_list& operator=(const array_list& list);
    ~array_list() {
        _destroy();
    }

    /**
     * 容器操作
     */
    iterator begin() { return _start; }
    iterator end() { return _end; }
    const_iterator c_begin() const {
        return _start;
    }
    const_iterator c_end() const {
        return _end;
    }

    size_type size() {
        return size_type(end() - begin());
    }
    size_type capacity() {
        return size_type(_end_of_storage - begin());
    }
    bool empty() {
        return begin() == end();
    }

    void swap(array_list& other);

    reference front() {
        return *_start;
    }
    reference back() {
        return *(end() - 1);
    }
    reference operator[](size_type n) {
        return *(begin() + n);
    }

    void insert(iterator position, const_reference x);
    void push(const_reference x);
    void pop();
    void insert(iterator position, size_type n, const_reference x);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void clear() {
        erase(begin(), end());
    }

private:
    void _destroy();
};

template <class T, class Alloc>
array_list<T, Alloc>::array_list(size_type n, const_value_type value) {
    _start = _alloc.allocate(n);
    std::uninitialized_fill(_start, _start+n, value);
    _end = _end_of_storage = _start+n;
}

template <class T, class Alloc>
array_list<T, Alloc>::array_list(size_type n) {
    _start = _alloc.allocate(n);
    std::uninitialized_fill(_start, _start+n, 0);
    _end = _end_of_storage = _start+n;
}

template <class T, class Alloc>
array_list<T, Alloc>::array_list(iterator first, iterator last) {
    _start = _alloc.allocate(last - first);
    _end = _end_of_storage = std::uninitialized_copy(first, last, _start);
}

template <class T, class Alloc>
array_list<T, Alloc>::array_list(const array_list &list) {
    size_type n = list.c_end() - list.c_begin();
    _start = _alloc.allocate(n);
    _end = _end_of_storage = std::uninitialized_copy(list.c_begin(), list.c_end(), _start);
}

template <class T, class Alloc>
void array_list<T, Alloc>::swap(array_list &other) {
    std::swap(_start, other._start);
    std::swap(_end, other._end);
    std::swap(_end_of_storage, other._end_of_storage);
}

template <class T, class Alloc>
array_list<T, Alloc> &array_list<T, Alloc>::operator=(const array_list& list) {
    if (this == &list) {
        return *this;
    }
    size_type n = list.c_end() - list.c_begin();
    _start = _alloc.allocate(n);
    _end = _end_of_storage = std::uninitialized_copy(list.begin(), list.end(), _start);
}

template <class T, class Alloc>
void array_list<T, Alloc>::insert(iterator position, size_type n, const_reference x) {
    if (n >= 0) {
        if (_end_of_storage - _end >= n) {
            value_type x_copy = x;
            // 插入点之后的元素个数
            const size_type elem_after = _end - position;
            iterator old_end = _end;
            if (elem_after > n) {
                std::uninitialized_copy(_end-n, _end, _end);
                _end += n;
                std::copy_backward(position, old_end-n, old_end);
                std::fill(position, position+n, x_copy);
            }else {
                std::uninitialized_fill_n(_end, n-elem_after, x_copy);
                _end += n - elem_after;
                std::uninitialized_copy(position, old_end, _end);
                _end += elem_after;
                std::fill(position, old_end, x_copy);
            }
        }else {
            const size_type old_size = size();
            const size_type len = old_size + std::max(n, old_size);
            iterator new_start = _alloc.allocate(len);
            iterator new_end = new_start;
            new_end = std::uninitialized_copy(_start, position, new_start);
            new_end = std::uninitialized_fill_n(new_end, n, x);
            new_end = std::uninitialized_copy(position, _end, new_end);
            _destroy();

            _start = new_start;
            _end = new_end;
            _end_of_storage = new_start + len;
        }
    }
}

template <class T, class Alloc>
void array_list<T, Alloc>::insert(iterator position, const_reference x) {
    if (_end != _end_of_storage) {
        std::uninitialized_copy(position, _end, position+1);
        _alloc.construct(position, x);
        _end += 1;
    }else {
        const size_type old_size = size();
        const size_type len = old_size ? 2 * old_size : 1;
        iterator new_start = _alloc.allocate(len);
        iterator new_end = std::uninitialized_copy(_start, position, new_start);
        _alloc.construct(new_end, x);
        ++new_end;
        new_end = std::uninitialized_copy(position, _end, new_end);

        _destroy();

        _start = new_start;
        _end = new_end;
        _end_of_storage = new_start + len;
    }
}

template <class T, class Alloc>
void array_list<T, Alloc>::push(const_reference x) {
    if (_end != _end_of_storage) {
        _alloc.construct(_end, x);
        _end++;
    }else {
        insert(end(), x);
    }
}

template <class T, class Alloc>
void array_list<T, Alloc>::pop() {
    --_end;
    _alloc.destroy(_end);
}

template <class T, class Alloc>
typename array_list<T, Alloc>::iterator array_list<T, Alloc>::erase(iterator position) {
    if (position+1 != end()) {
        std::copy(position+1, end(), position);
    }
    --_end;
    _alloc.destroy(_end);
    return position;
}

template <class T, class Alloc>
typename array_list<T, Alloc>::iterator array_list<T, Alloc>::erase(iterator first,
        iterator last) {
    difference_type left = _end - last;
    std::copy(last, _end, first);
    iterator it(first + left);
    while (_end != it) {
        _alloc.destroy(--_end);
    }
    return first;
}

template <class T, class Alloc>
void array_list<T, Alloc>::_destroy() {
    if (_start) {
        iterator it(_end);
        while (it != _start) {
            _alloc.destroy(--it);
        }
    }

    _alloc.deallocate(_start, _end_of_storage-_start);
    _start = _end_of_storage = _end = NULL;
}

#endif //DATA_STRUCTURE_ARRAY_LIST_H
