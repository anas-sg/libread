# libread
A custom C library for the handling of textual input such as reading a word, a line or multiple lines.

## Usage
For the compilation of multiple translation units, each source file that requires the functions from libread must include the header file: 
```C
#include "read.h"
```
The units would then have to be compiled together with `read.c`, for example:
```
gcc -o main main.c unit1.c unit2.c read.c
```
