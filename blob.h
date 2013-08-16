#ifndef BLOB_H
#define BLOB_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <initializer_list>
#include <stdexcept>

template <typename> class BlobPtr;
template <typename> class Blob; // needed for parameters in operator==
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob
{
    friend class BlobPtr<T>;
    friend bool operator==<T> (const Blob<T> &, const Blob<T> &);

public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    //ctor
    Blob(T *): data(std::make_shared<std::vector<T>>()) {}

    Blob(std::initializer_list<T> il) try :
        data(std::make_shared<std::vector<T>>(il)) {
    } catch(const std::bad_alloc &e) { /*handle_out_of_memory(e);*/ }

    template <typename It> Blob(It b, It e);
    Blob (T*, std::size_t);

    // return BlobPtr to the first and one past the last elements
    BlobPtr<T> begin() { return BlobPtr<T>(*this); }
    BlobPtr<T> end()
    {
        auto ret = BlobPtr<T>(*this, data->size());
        return ret;
    }

    // number of elements in the Blob
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();

    // element access
    T& front();
    T& back();
    T& at(size_type);
    const T& front() const;
    const T& back() const;
    const T& at(size_type) const;
    T& operator[] (size_type i);
    const T& operator [] (size_type i) const;

    void swap(Blob &b) { data.swap(b.data); }
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if(i>=data->size())
        throw std::out_of_range(msg);
}

template <typename T>
Blob<T>::Blob (T* p, std::size_t n) :
    data(std::make_shared<std::vector<T>>(p, p+n)) {}

template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e) :
    data(std::make_shared<std::vector<T>>(b,e)) {}

template <typename T>
T& Blob<T>::front()
{
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
const T& Blob<T>::front() const
{
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
const T& Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T& Blob<T>::at(size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
const T& Blob<T>::at(size_type i) const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
T& Blob<T>::operator[] (size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
const T& Blob<T>::operator[] (size_type i) const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

// operators
template <typename T>
bool operator ==(const Blob<T> &lhs, const Blob<T> &rhs)
{
    if (rhs.size() != lhs.size())
        return false;
    for (size_t i=0; i<lhs.size; ++i)
    {
        if(lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <typename T>
std::ostream& operator<< (std::ostream &os, const Blob<T> &a)
{
    os<<"< ";
    for(size_t i=0; i<a.size(); ++i)
        os<<a[i]<<" ";
    os<<" >";
    return os;
}

#endif // BLOB_H
