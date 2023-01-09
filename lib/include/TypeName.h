#ifndef TYPENAME_H_RBTSWW7B
#define TYPENAME_H_RBTSWW7B
#include <string_view>
#include <utility>
#include <cstring>
#include "Log.h"

class ClassAnchor{};
template <typename T>
constexpr std::string_view SubtractTypeName()
{
    if constexpr (std::is_same_v<std::remove_cv_t<T>, ClassAnchor>) {
        return __PRETTY_FUNCTION__;
    }
    auto anchor = SubtractTypeName<ClassAnchor>();
    auto prefixlen = anchor.find("ClassAnchor");
    auto suffixlen = anchor.length() - prefixlen - strlen("ClassAnchor");
    auto tname = std::string_view(__PRETTY_FUNCTION__);
    tname.remove_prefix(prefixlen);
    tname.remove_suffix(suffixlen);
    return tname;
}

template <typename T>
constexpr auto PrintT() { return SubtractTypeName<T>(); }

template <typename T>
constexpr auto PrintV(T&& val) { return SubtractTypeName<T>(); }

#define print_t(type) LOG_EVAL(PrintT<type>())
#define print_v(val)  LOG_EVAL(PrintV(val))

#endif /* end of include guard: TYPENAME_H_RBTSWW7B */
