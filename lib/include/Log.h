#ifndef LOG_H_RWLBPF7A
#define LOG_H_RWLBPF7A
#include <iostream>

#define WRAP_EVAL(...)                      \
do {                                        \
    std::cout << ">>> " << #__VA_ARGS__ << std::endl; \
    __VA_ARGS__;                                      \
    std::cout << "<<< " << #__VA_ARGS__ << std::endl; \
} while(0)

#define LOG_EVAL(...) std::cout << "Eval Of ^" << #__VA_ARGS__ << "$ Is: [" << __VA_ARGS__ << "]" << std::endl

/* LOG_PAIR - one "literal string = [value]" chunk, can be used inside a stream
 * LOG_VARS - print up to 10 expressions, each as a literal string / value pair
 *
 * Usage:
 *  int a = 1; std::string b = "abc";
 *  LOG_VARS(a);               // a = [1]
 *  LOG_VARS(a, b);            // a = [1], b = [abc]
 *  LOG_VARS(a + 1, b.size()); // a + 1 = [2], b.size() = [3]
 */
#define LOG_PAIR(var) #var " = [" << (var) << "]"

#define LOG_CONCAT_IMPL(x, y) x##y
#define LOG_CONCAT(x, y) LOG_CONCAT_IMPL(x, y)

/* LOG_NARGS(a, b, c) -> 3, holds for 1 to 10 arguments */
#define LOG_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define LOG_NARGS(...) LOG_NARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define LOG_VARS_1(a1) LOG_PAIR(a1)
#define LOG_VARS_2(a1, a2) LOG_VARS_1(a1) << ", " << LOG_PAIR(a2)
#define LOG_VARS_3(a1, a2, a3) LOG_VARS_2(a1, a2) << ", " << LOG_PAIR(a3)
#define LOG_VARS_4(a1, a2, a3, a4) LOG_VARS_3(a1, a2, a3) << ", " << LOG_PAIR(a4)
#define LOG_VARS_5(a1, a2, a3, a4, a5) LOG_VARS_4(a1, a2, a3, a4) << ", " << LOG_PAIR(a5)
#define LOG_VARS_6(a1, a2, a3, a4, a5, a6) LOG_VARS_5(a1, a2, a3, a4, a5) << ", " << LOG_PAIR(a6)
#define LOG_VARS_7(a1, a2, a3, a4, a5, a6, a7) LOG_VARS_6(a1, a2, a3, a4, a5, a6) << ", " << LOG_PAIR(a7)
#define LOG_VARS_8(a1, a2, a3, a4, a5, a6, a7, a8) LOG_VARS_7(a1, a2, a3, a4, a5, a6, a7) << ", " << LOG_PAIR(a8)
#define LOG_VARS_9(a1, a2, a3, a4, a5, a6, a7, a8, a9) LOG_VARS_8(a1, a2, a3, a4, a5, a6, a7, a8) << ", " << LOG_PAIR(a9)
#define LOG_VARS_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) LOG_VARS_9(a1, a2, a3, a4, a5, a6, a7, a8, a9) << ", " << LOG_PAIR(a10)

/* more than 10 arguments picks an undefined LOG_VARS_<n> and fails to compile */
#define LOG_VARS(...) std::cout << LOG_CONCAT(LOG_VARS_, LOG_NARGS(__VA_ARGS__))(__VA_ARGS__) << std::endl

#endif /* end of include guard: LOG_H_RWLBPF7A */
