#ifndef SOME_METAPROGRAMMING_PRIMITIVES
#define SOME_METAPROGRAMMING_PRIMITIVES

/**
 * @brief integral constant primitive for easy living :)
 * 
 * @tparam T type to be in value field of metafunction
 * @tparam B value to be in value field
 */
template <typename T, T v>
struct integral_constant {
    static constexpr T value = v;
};

/**
 * @brief template branch enabler
 * 
 * @tparam B boolean constexpr condition
 * @tparam T returnable type if true, if not - substitusion fail (SFINAE)
 */
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
    using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

/**
 * @brief remove constant and volatile from type
 * 
 * @tparam T input type
 */
template <typename T>
struct remove_cv {
    using type = T;
};

template <typename T>
struct remove_cv<const T> {
    using type = T;
};

template <typename T>
struct remove_cv<volatile T> {
    using type = T;
};

template <typename T>
struct remove_cv<const volatile T> {
    using type = T;
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

/**
 * @brief remove const from type
 * 
 * @tparam T input type
 */
template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

/**
 * @brief remove volatile from type
 * 
 * @tparam T input type
 */
template <typename T>
struct remove_volatile {
    using type = T;
};
template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

#endif