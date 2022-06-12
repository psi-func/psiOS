#ifndef SIMPLE_MATH
#define SIMPLE_MATH

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