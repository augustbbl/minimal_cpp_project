/*******************************************************************************
** @file unique_ptr.hpp
** @author August Lounibos
** @date 6.4.18
** @brief unique_ptr interface file 
*******************************************************************************/

#pragma once

namespace diy {

/*******************************************************************************
** @brief unique_ptr 'smart pointer' object. automatically deletees managed ptr
** @tparam T managed poiner type
*******************************************************************************/
template <typename T>
class unique_ptr {
public:
    // ctors
    explicit unique_ptr(T * ptr = nullptr)                       noexcept;
    ~unique_ptr();
    unique_ptr(unique_ptr<T> && other)                           noexcept;
    unique_ptr<T> & operator =(unique_ptr<T> && other)           noexcept;
    unique_ptr(const unique_ptr<T> & other)                      = delete;
    unique_ptr<T> & operator =(const unique_ptr<T> & other)      = delete;

    // accessors
    T * get()                                              const noexcept;
    T & operator *()                                       const         ;
    T * operator ->()                                      const noexcept;
    explicit operator bool()                               const noexcept;

    // mutators 
    template <typename U>
    friend void swap(unique_ptr<U> & a, unique_ptr<U> & b)       noexcept;
    T * release()                                                noexcept;
    void reset(T * ptr = nullptr)                                noexcept;

private:
    T * data;
};

} // diy

#include "unique_ptr.tcc"
