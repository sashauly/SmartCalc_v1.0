# SmartCalc v1.0

### Implementation of SmartCalc v1.0, an extended version of the usual calculator, which can be found in the standard applications of each operating system in the C programming language using structured programming. 
In addition to basic arithmetic operations such as add/subtract and multiply/divide, calculator are able to calculate arithmetic expressions by following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.). Besides calculating expressions, it also support the use of the _x_ variable and the graphing of the corresponding function.

In this project i tried to learn more about `reverse Polish notation` and `Dijkstra's algorithm`.

This is an educational project, so it's no longer supported!
> 11.01.2023

## Important notes

- The program developed in `C` language of C11 standard using gcc compiler with Qt framework and additional Qt libraries and modules for GUI part(this is my first experience with `C++`).
- The program code located in the src folder
- The program built with Makefile which contains standard set of targets for GNU-programs: `all`, `install`, `uninstall`, `clean`, `dvi`, `dist`, `tests`, `gcov_report`.
- Written code follows the Google style. Legacy and outdated functions are not used according to POSIX.1-2017 standard(see `clang` goal in Makefile).
- Integration tests covered all of the library's functions by unit-tests using the `check.h` library(see `test` goal in Makefile).
- Unit tests coverage checked using gcov. It provides a gcov report in the form of an html page(see `gcov_report` goal in Makefile).
- The programs developed according to the principles of structured programming, duplication in the code is avoided
- Both integers and real numbers with a dot can be input into the program. You can optionally provide the input of numbers in exponential notation
- The calculation is done after you complete entering the calculating expression and press the `=` symbol.
- Calculating arbitrary bracketed arithmetic expressions in infix notation
- Calculate arbitrary bracketed arithmetic expressions in infix notation with substitution of the value of the variable _x_ as a number
- Plotting a graph of a function given by an expression in infix notation with the variable _x_ (with coordinate axes, mark of the used scale and an adaptive grid)
- Domain and codomain of a function are limited to at least numbers from -1000000 to 1000000
- Verifiable accuracy of the fractional part is at least to 7 decimal places
- Users are able to enter up to 255 characters

## Supported operations and functions

  - **Arithmetic operators**:

    | Operator name | Infix notation <br /> (Classic) | Prefix notation <br /> (Polish notation) |  Postfix notation <br /> (Reverse Polish notation) |
    | --------- | ------ | ------ | ------ |
    | Brackets | (a + b) | (+ a b) | a b + |
    | Addition | a + b | + a b | a b + |
    | Subtraction | a - b | - a b | a b - |
    | Multiplication | a * b | * a b | a b * |
    | Division | a / b | / a b | a b \ |
    | Power | a ^ b | ^ a b | a b ^ |
    | Modulus | a mod b | mod a b | a b mod |
    | Unary plus | +a | +a | a+ |
    | Unary minus | -a | -a | a- |

  - **Functions**:

    | Function description | Function |
    | ------ | ------ |
    | Computes cosine | cos(x) |
    | Computes sine | sin(x) |
    | Computes tangent | tan(x) |
    | Computes arc cosine | acos(x) |
    | Computes arc sine | asin(x) |
    | Computes arc tangent | atan(x) |
    | Computes square root | sqrt(x) |
    | Computes natural logarithm | ln(x) |
    | Computes common logarithm | log(x) |