[![Build Status](https://travis-ci.org/ahueck/opovlint.svg?branch=master)](https://travis-ci.org/ahueck/opovlint)

OO-Lint (opovlint)
===========

This is a project for linting operator overloads in C++. It is implemented as 
a Clang tool.


Disclaimer
------------

The status of this software is alpha level.


License
------------

Distributed under the MIT License. For details refer to the [LICENSE](LICENSE)


Motivation
------------

Operator overloading allows for the semantic augmentation of existing codes. 
The basic arithmetic type in a code is replaced by a user-defined type.

*Type change* (in theory this just works): 
- typedef **double** scalar; -> typedef **userdef_double** scalar;

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


Goal
------------

Provide developers of (numerical) codes with static code analysis 
to avoid problematic coding patterns.

For legacy numerical codes:
- Flag potential problematic code locations
- Ideally autocorrect them


Installation 
------------

The tool is developed and tested on Linux. 
For Ubuntu/Debian, refer to the [Travis CI file](.travis.yml) for guidance.

### Prerequisites

1.  C++ Compiler with C++11 support (GCC version >= 4.8)
2.  cmake (version >=2.8)
3.  Clang/LLVM in Version 3.5.0. Newer versions might not work due to the changing API.
    The build system relies on the presence of the **llvm-config**(-3.5 -3.6 -3.7) binary.
    If it can not be found, set the cmake variable ${LLVM_ROOT_DIR} to point to the 
    respective bin/ folder where llvm-config is located.

### Build the OO-Lint tool

In the root folder of the project:

    mkdir build && cd build/
    cmake -DCMAKE_BUILD_TYPE=Release -DMAKE_TEST=FALSE ..
    make

The binary should be created in the project folder *bin/*. 
