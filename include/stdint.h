#ifndef KERNEL_STD_INTEGER_TYPES
#define KERNEL_STD_INTEGER_TYPES

#include "mtp.hpp"

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

/**
 * @brief Check if integer type is unsigned or not
 * 
 * @tparam I integral type template arg
 */
template <typename I>
struct is_unsigned : integral_constant<bool, I(0) < I(-1) > {};

template <typename I>
inline constexpr bool is_unsigned_v = is_unsigned<I>::value;

namespace detail {
    template <typename T>
    struct is_integral : integral_constant<bool, false> { };
    
    template <>
    struct is_integral<i8> : integral_constant<bool, true> { };
    template <>
    struct is_integral<u8> : integral_constant<bool, true> { };
    
    template <>
    struct is_integral<i16> : integral_constant<bool, true> { };
    template <>
    struct is_integral<u16> : integral_constant<bool, true> { };
    
    template <>
    struct is_integral<i32> : integral_constant<bool, true> { };
    template <>
    struct is_integral<u32> : integral_constant<bool, true> { };
    
    template <>
    struct is_integral<i64> : integral_constant<bool, true> { };
    template <>
    struct is_integral<u64> : integral_constant<bool, true> { };

}

template <typename T>
struct is_integral : detail::is_integral<remove_cv_t<T>> { };

template <typename T>
inline constexpr bool is_integral_v = is_integral<T>::value;

namespace detail {

    template <typename T>
    struct is_floating_point : integral_constant<bool, false> {};
    
    template <>
    struct is_floating_point<float> : integral_constant<bool, true> { };
    template <>
    struct is_floating_point<double> : integral_constant<bool, true> { };
    template <>
    struct is_floating_point<long double> : integral_constant<bool, true> { };

}

template <typename T>
struct is_floating_point : detail::is_floating_point<remove_cv_t<T>> { };

template <typename T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;


#endif