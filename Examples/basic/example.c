#include <stdio.h>

#include "ctf_import.h"


int main() {
    int (* fib)(int);
    
    // a.out is a binary with a fibonacci function at offset 0xf00
    fib = (int (*)(int)) import("a.out", 0xf00);
    
    printf("%d %d %d %d %d\n", fib(1), fib(2), fib(3), fib(4), fib(5));
}