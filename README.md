[![Build Status](https://travis-ci.org/ahueck/opovlint.svg?branch=master)](https://travis-ci.org/ahueck/opovlint)

# OO-Lint (opovlint)

This is a project for linting operator overloads in C++. It is implemented as 
a Clang tool.


## Disclaimer

The status of this software is alpha level.


## License

Distributed under the MIT License. For details refer to the [LICENSE](LICENSE).


## Motivation

Operator overloading allows for the semantic augmentation of existing codes. 
The basic arithmetic type in a code is replaced by a user-defined type (e.g., **adouble**).

*Type change* (in theory these just works): 
- typedef **double** scalar; -> typedef **adouble** scalar;
- using scalar = **double**; -> using scalar = **adouble**;

However, several coding patterns are not compatible with user-defined classes 
and result in compile time errors.
- Implicit Conversions
    - “At most one user-defined conversion [...] is implicitly 
         applied to a single value.” –  [§12.3-4, C++03 Standard]
    - Subset: 
        - Boolean Conversions, i.e., conditional statements
- Unions
    - Incompatible with complex data classes [§9.5-1, C++03 Standard]
- Explicit Conversions
    - Cast operation from a user-defined type to a built-in is often not possible
- Friend functions and the Scope Resolution Operator (**::**)
    - A combination of these two C++ features can cause problems in certain circumstances


## Goal

Provide developers of (numerical) codes with static code analysis 
to avoid problematic coding patterns.

For legacy numerical codes:
- Flag potential problematic code locations
- Ideally auto-correct them


## Installation 

The tool is developed and tested on Linux. 
For Ubuntu/Debian, refer to the [Travis CI file](.travis.yml) for guidance.

### Prerequisites

1.  C++ Compiler with C++11 support. Tested compilers: GCC-(4.8 4.9 5.0) and Clang-(3.6 3.7 3.8)
2.  cmake (version >=3.0)
3.  Clang/LLVM-3.6 with development packages. For a Debian-based distro the following packages may work:
    - clang-3.6
    - llvm-3.6
    - libclang-3.6-dev
    - llvm-3.6-dev

    Other versions might not work due to the changing API.
    The build system relies on the presence of the *llvm-config*(-3.6 -3.7 -3.8) binary.
    If it can not be found, set the cmake variable ${**LLVM_ROOT_DIR**} to point to the 
    respective *bin* folder where *llvm-config* is located.

### Build the OO-Lint tool

In the root folder of the project:

    mkdir build && cd build/
    cmake -DCMAKE_BUILD_TYPE=Release -DMAKE_TEST=FALSE ..
    cmake --build .

The binary  should be created in the project folder *bin*. 
