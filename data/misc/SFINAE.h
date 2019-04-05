//
// Created by Caleb Choi on 04/04/2019.
//

#ifndef CLION_SFINAE_H
#define CLION_SFINAE_H

#include <type_traits>

/*
 * Iteration 1
 */
//template<typename T>
//T& print(const T&,
//         typename std::enable_if<std::is_integral<T>::value, int>::type = nullptr);

/*
 * Iteration 2
 * Using std::enable_if_t alias (C++14 feature)
 */
//template<typename T>
//T& print(const T&,
//         std::enable_if_t<std::is_integral<T>::value, std::nullptr_t> = nullptr);

/*
 * Iteration 3
 * Using default template parameters (C++11 feature)
 */
//template<typename T, typename std::enable_if_t<std::is_integral<T>::value, std::nullptr_t> = nullptr>
//T& print(const T&);

/*
 * Iteration 4
 * Removed std::nullptr_t template parameter, using void as default enable_if_t parameter (C++11 feature)
 */
//template<typename T, typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
//T& print(const T&);

/*
 * Iteration 5
 * Letting std::enable_if_t void default be the template default (C++11 feature)
 */
//template<typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
//T& print(const T&);

/*
 * Iteration 6
 * Separation of conditional
 */
template<typename T>
using enable_if_integral = std::enable_if_t<std::is_integral<T>::value>;

template<typename T, typename = enable_if_integral<T>>
T& print(const T&);

#include "SFINAE.tpp"

#endif //CLION_SFINAE_H