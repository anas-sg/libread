# libread
A custom C library for the reading of textual input such as a word, a line, multiple lines or CSV.

## Usage
Each source file that requires the functions from libread must include the header file: 
```C
#include "read.h"
```
The files would then have to be compiled together with `read.c`, for example:
```
gcc read.c main.c test1.c test2.c  -o main 
```