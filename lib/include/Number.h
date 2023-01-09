#ifndef NUMBER_H_UGZH6JQI
#define NUMBER_H_UGZH6JQI

namespace Number {
template <typename T>
T Add(T x, T y) { return x + y; }

template <typename T>
T Sub(T x, T y) { return x - y; }

template <typename T>
T Multiply(T x, T y) { return x * y; }

template <typename T>
T Divide(T x, T y) { return x / y; }

int Add(int, int);
} /* Number  */ 
#endif /* end of include guard: NUMBER_H_UGZH6JQI */
