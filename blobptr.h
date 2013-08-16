#ifndef BLOBPTR_H
#define BLOBPTR_H

#include <iterator>
#include "blob.h"

template <typename T>
bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T>
class BlobPtr : public std::iterator<std::bidirectional_iterator_tag, T>
{
    friend bool operator==<T>(const BlobPtr<T>&, const BlobPtr<T>&);
public:
    BlobPtr() : curr(0) {}
    BlobPtr( Blob<T> &a, size_t sz=0 )
        : wptr(a.data), curr(sz){}

    T& operator[] (std::size_t i)
    {
        auto p = check(i, "subscript out of range");
        return (*p)[i];
    }

    const T& operator[] (std::size_t i) const
    {
        auto p = check(i, "subscript out of range");
        return (*p)[i];
    }

    T& operator* () const
    {
        auto p=check(curr, "dereference past end");
        return (*p)[curr];
    }

    T* operator-> () const
    {
      return & this->operator *();
    }

    // increment and decrement
    BlobPtr& operator ++();    //prefix operators
    BlobPtr& operator --();

    BlobPtr operator ++(int);  //postfix operators
    BlobPtr operator --(int);

private:
    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

template <typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return lhs.wptr.lock.get() == rhs.wptr.lock.get() &&
           lhs.curr == rhs.curr;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator ++()
{

}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator --()
{

}

#endif // BLOBPTR_H
