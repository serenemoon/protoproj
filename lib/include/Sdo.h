#ifndef SDO_H_YGFWFMZC
#define SDO_H_YGFWFMZC

namespace Sdo {
/* DataList - template parameter should be like x0, x1, x2, x3...
 *  compare v against each x, to check if list contains or not contains v
 * 
 * Usage:
 *  using DL = DataList<3, 6, 8, 19>;
 *  auto contains = DL::Contains(3); // contains == true
 *  auto contains = DL::Contains(4); // contains == false
 */
template <auto... vs>
struct DataList {
    template <typename T>
    static bool Contains(T val) { return ((vs == val) || ...); }
    template <typename T>
    static bool NotContains(T val) { return !Contains(val); }
};

/* DataPairs - template parameter should be like x0, y0, x1, y1, x2, y2, ..., z
 *  if v matches one of x, return corresponding y, else return z as default
 *
 * Usage:
 *  using DP = DataPairs<1, 10, 2, 20, 0>;
 *  auto v = DP::ValueOfKey(1); // v == 10
 *  auto w = DP::ValueOfKey(3); // w == 0
 */
template <auto x, auto y, auto z, auto... vs>
struct DataPairs {
    static_assert(sizeof...(vs) % 2 == 0, "DataPairs Must be odd, and > 3");

    template <typename T>
    static auto ValueOfKey(T val)
    {
        if constexpr (sizeof...(vs) == 0) {
            return val == x ? y : z;
        } else {
            return val == x ? y : DataPairs<z, vs...>::ValueOfKey(val);
        }
    }
};
} /* Sdo */ 

#endif /* end of include guard: SDO_H_YGFWFMZC */
