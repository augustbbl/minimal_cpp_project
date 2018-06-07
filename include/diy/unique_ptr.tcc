/*******************************************************************************
** @file unique_ptr.tcc
** @author August Lounibos
** @date 6.5.18
** @brief unique_ptr implementation file 
*******************************************************************************/

#pragma once

#include <utility>

namespace diy {

/*******************************************************************************
** @brief unique_ptr constructs unique_ptr that owns resource ptr
** @tparam T managed type
** @param ptr resource to be managed
*******************************************************************************/
template <typename T>
unique_ptr<T>::unique_ptr(T * ptr) noexcept : data(ptr) {}

/*******************************************************************************
** @brief unique_ptr constructs unique_ptr and transfers ownership of other.data
** @tparam T managed type
** @param other unique_ptr to be moved from
*******************************************************************************/
template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T> && other) noexcept : data(other.release()) {}

/*******************************************************************************
** @brief operator = deletes current data, transfers ownership of other.data
** @tparam T managed type
** @param other unique_ptr to be moved from
** @return unique_ptr<T> & self-reference
** @post previous resource deallocated
*******************************************************************************/
template <typename T>
unique_ptr<T> & unique_ptr<T>::operator =(unique_ptr<T> && other) noexcept {
    swap(*this, other);
    return *this;
}

/*******************************************************************************
** @brief ~unique_ptr deallocate managed resource
** @tparam T managed type
** @post resource deallocated
*******************************************************************************/
template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (data) {
        delete data;
    }
}

/*******************************************************************************
** @brief make_unique unique_ptr factory function
** @tparam T managed type
** @tparam Args variadic type list of arguments to T's constructor
** @param args variadic list of arguments to T's constructor
** @return unique_ptr<T> constructed unique_ptr
*******************************************************************************/
template <typename T, typename ... Args>
unique_ptr<T> make_unique(Args && ... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/*******************************************************************************
** @brief get return managed resource 
** @tparam T managed type
** @return T * managed resource
*******************************************************************************/
template <typename T>
T * unique_ptr<T>::get() const noexcept {
    return data;
}

/*******************************************************************************
** @brief operator * dereference managed resource
** @tparam T managed type
** @return T & managed resource (dereferenced)
*******************************************************************************/
template <typename T>
T & unique_ptr<T>::operator *() const {
    return *data;
}

/*******************************************************************************
** @brief operator -> managed resource member access
** @tparam T managed type
** @return T * managed resource
*******************************************************************************/
template <typename T>
T * unique_ptr<T>::operator ->() const noexcept {
    return data; 
}

/*******************************************************************************
** @brief operator bool return true if managed ptr is not null
** @tparam T managed type
** @return bool true if ptr is not null
*******************************************************************************/
template <typename T>
unique_ptr<T>::operator bool() const noexcept {
    return data != nullptr;
}

/*******************************************************************************
** @brief swap swap two diy::unique_ptr's
** @tparam T type managed by diy::unique_ptr's
** @param a object to be swapped
** @param b object to be swapped
** @post a and b's pointers are swapped
*******************************************************************************/
template <typename U>
void swap(unique_ptr<U> & a, unique_ptr<U> & b) noexcept {
    std::swap(a.data, b.data); 
}

/*******************************************************************************
** @brief reset delete current pointer, manage new one
** @tparam T managed type
** @param ptr new managed pointer (default: nullptr)
** @post old pointer deleted
*******************************************************************************/
template <typename T>
void unique_ptr<T>::reset(T * ptr) noexcept {
    if (data and data != ptr) {
        delete data;
    }
    data = ptr;
}

/*******************************************************************************
** @brief release relinquish ownership of managed pointer
** @tparam T managed type
** @return T * previously owned pointer
** @post ownership transfered to raw pointer
*******************************************************************************/
template <typename T>
T * unique_ptr<T>::release() noexcept {
    T * ret = nullptr;
    std::swap(data, ret);
    return ret;
}

} // diy
