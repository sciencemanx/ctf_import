# ctf_import

> A small library that allows you to run basic functions cross platform from other binaries

## Usage

This library is designed for you to be able to quickly call functions from a stripped binary. All you need is the file name, the function offset, and the function signature. You can get these by reverse engineering the binary in IDA or Binary Ninja.

> void *import(char *file, size_t offset)

``` c
#include "ctf_import.h"

int main() {
    int (* fib)(int);
    
    // a.out is a binary with a fibonacci function at offset 0xf00
    fib = (int (*)(int)) import("a.out", 0xf00);
    
    printf("%d %d %d %d %d\n", fib(1), fib(2), fib(3), fib(4), fib(5));
}
```

To compile:

``` bash
$ gcc example.c ctf_import.c -o example
$ ./example
> 1 1 2 3 5
```

## Notes

Although the code will run "cross-OS", it will not run cross architecture. Additionally, this does not handle syscalls and anything that interacts with globals. 