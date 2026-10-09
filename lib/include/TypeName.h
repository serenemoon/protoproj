#ifndef TYPENAME_H_RBTSWW7B
#define TYPENAME_H_RBTSWW7B
#include "Log.h"
#include <string_view>

// clang-format off
/*
 *
 *
 *
__PRETTY_FUNCTION__:
__PRETTY_FUNCTION__ = [constexpr std::string_view SubtractTypeName() [with T = std::vector<int>; std::string_view = std::basic_string_view<char>]]
__PRETTY_FUNCTION__ = [constexpr std::string_view SubtractTypeName() [with T = std::__cxx11::list<int>; std::string_view = std::basic_string_view<char>]]
__PRETTY_FUNCTION__ = [constexpr std::string_view SubtractTypeName() [with T = int (&)[3]; std::string_view = std::basic_string_view<char>]]
__PRETTY_FUNCTION__ = [constexpr std::string_view SubtractTypeName() [with T = int [3]; std::string_view = std::basic_string_view<char>]]
__PRETTY_FUNCTION__ = [constexpr std::string_view SubtractTypeName() [with T = std::__cxx11::list<int>; std::string_view = std::basic_string_view<char>]]
__PRETTY_FUNCTION__ = [constexpr std::string_view SubtractTypeName() [with T = std::__cxx11::basic_string<char>; std::string_view = std::basic_string_view<char>]]


__FUNCSIG__:
 __FSTREXP __FUNCSIG__   = [class std::basic_string_view<char,struct std::char_traits<char> > __cdecl SubtractTypeName<class std::vector<int,class std::allocator<int> >>(void)]
 __FSTREXP __FUNCSIG__   = [class std::basic_string_view<char,struct std::char_traits<char> > __cdecl SubtractTypeName<class std::list<int,class std::allocator<int> >>(void)]
 __FSTREXP __FUNCSIG__   = [class std::basic_string_view<char,struct std::char_traits<char> > __cdecl SubtractTypeName<int(&)[3]>(void)]
 __FSTREXP __FUNCSIG__   = [class std::basic_string_view<char,struct std::char_traits<char> > __cdecl SubtractTypeName<int[3]>(void)]
 __FSTREXP __FUNCSIG__   = [class std::basic_string_view<char,struct std::char_traits<char> > __cdecl SubtractTypeName<class std::list<int,class std::allocator<int> >>(void)]
 __FSTREXP __FUNCSIG__   = [class std::basic_string_view<char,struct std::char_traits<char> > __cdecl SubtractTypeName<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >>(void)]
 *
 */

/* Cross-platform extraction of the deduced type name.
 *
 * Every supported compiler exposes the full signature of the enclosing
 * function in a slightly different way:
 *
 *   GCC    : __PRETTY_FUNCTION__ -> "... [with T = int; std::string_view = ...]"
 *   Clang  : __PRETTY_FUNCTION__ -> "... [T = int]"
 *   MSVC   : __FUNCSIG__ -> "... __cdecl SubtractTypeName<int>(void)"
 *
 * They all contain the deduced type name in full, so extracting it only needs
 * to know which marker precedes the type and which one terminates it. That
 * logic is compiler independent (TypeNameDetail::Strip) so it can be exercised
 * with synthetic signatures from any backend.
 */
// clang-format on
namespace TypeNameDetail {

enum class Style { Msvc, Gcc, Clang };

constexpr bool IsSpace(char c) { return c == ' ' || c == '\t'; }

constexpr std::string_view Trim(std::string_view s) {
  while (!s.empty() && IsSpace(s.front())) {
    s.remove_prefix(1);
  }
  while (!s.empty() && IsSpace(s.back())) {
    s.remove_suffix(1);
  }
  return s;
}

template <Style S>
constexpr std::string_view Strip(std::string_view signature) {
  std::string_view prefix;
  if constexpr (S == Style::Msvc) {
    prefix = "SubtractTypeName<";
  } else if constexpr (S == Style::Gcc) {
    prefix = "with T = ";
  } else {
    prefix = "T = ";
  }

  const auto marker = signature.find(prefix);
  if (marker == std::string_view::npos) {
    return {};
  }
  const auto start = marker + prefix.size();

  std::string_view name;
  if constexpr (S == Style::Msvc) {
    /* __FUNCSIG__ always ends with ">(void)", so the deduced type runs up to
     * the final '>'. Nested templates are rendered as "> >", leaving a space
     * that Trim() removes afterwards. */
    const auto end = signature.rfind('>');
    if (end == std::string_view::npos || end < start) {
      return {};
    }
    name = signature.substr(start, end - start);

    /* MSVC decorates class-type arguments ("class Foo", "struct Bar"). Drop a
     * single leading keyword so the result matches the GCC/Clang spelling. */
    if (name.size() > 6 && name.compare(0, 6, "class ") == 0) {
      name.remove_prefix(6);
    } else if (name.size() > 7 && name.compare(0, 7, "struct ") == 0) {
      name.remove_prefix(7);
    } else if (name.size() > 6 && name.compare(0, 6, "union ") == 0) {
      name.remove_prefix(6);
    }
  } else {
    /* GCC appends "; alias = ..." notes right after the type; Clang closes the
     * bracket instead. When neither is present fall back to the final ']'. */
    const auto semi = signature.find(';', start);
    const auto end =
        (semi != std::string_view::npos) ? semi : signature.rfind(']');
    if (end == std::string_view::npos || end < start) {
      return {};
    }
    name = signature.substr(start, end - start);
  }

  return Trim(name);
}

} /* namespace TypeNameDetail */

template <typename T> constexpr std::string_view SubtractTypeName() {
#if defined(__clang__) /* also clang-cl, which defines _MSC_VER as well */
  LOG_VARS(__PRETTY_FUNCTION__);
  return TypeNameDetail::Strip<TypeNameDetail::Style::Clang>(
      __PRETTY_FUNCTION__);
#elif defined(_MSC_VER)
  LOG_VARS(__FUNCSIG__);
  return TypeNameDetail::Strip<TypeNameDetail::Style::Msvc>(__FUNCSIG__);
#elif defined(__GNUC__)
  LOG_VARS(__PRETTY_FUNCTION__);
  return TypeNameDetail::Strip<TypeNameDetail::Style::Gcc>(__PRETTY_FUNCTION__);
#else
#error "TypeName.h: unsupported compiler"
#endif
}

template <typename T> constexpr auto PrintT() { return SubtractTypeName<T>(); }

template <typename T> constexpr auto PrintV(T &&val) {
  (void)val;
  return SubtractTypeName<T>();
}

#define print_t(type)                                                          \
  {                                                                            \
    auto val = PrintT<type>();                                                 \
    LOG_VARS("PrintT<type>:", val);                                            \
  }
#define print_v(val)                                                           \
  {                                                                            \
    auto nval = PrintV(val);                                                   \
    LOG_VARS("PrintV(val):", nval);                                            \
  }

#endif /* end of include guard: TYPENAME_H_RBTSWW7B */
