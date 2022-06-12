#ifndef KERNEL_STD_INTEGER_TYPES
#define KERNEL_STD_INTEGER_TYPES

// #include <cstdint>

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long;
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long;
// using i8 = int8_t;
// using i16 = int16_t;
// using i32 = int32_t;
// using i64 = int64_t;
// using u8 = uint8_t;
// using u16 = uint16_t;
// using u32 = uint32_t;
// using u64 = uint64_t;

template <typename T, bool B>
struct integral_constant;

template <>
struct integral_constant<bool, true> {
    static const bool value = true; 
};

template <>
struct integral_constant<bool, false> {
    static const bool value = false; 
};


/**
 * @brief Check if integer type is unsigned or not
 * 
 * @tparam I integral type template arg
 */
template <typename I>
struct is_unsigned : integral_constant<bool, I(0) < I(-1) > {};

template <typename I>
inline constexpr bool is_unsigned_v = is_unsigned<I>::value;


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


template <typename T>
T abs(T value) {
    if constexpr (is_unsigned<T>::value) {
        return value;
    }
    else {
        if (value < 0) return -value;
        return value;
    }
}

#endif