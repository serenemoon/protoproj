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

#endif /* end of include guard: LOG_H_RWLBPF7A */
