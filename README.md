## OO-Lint (opovlint)

This is a project for linting operator overloads in C++. It is implemented as 
a Clang tool.

## Disclaimer

The status of this software is alpha level and not ready for public usage.

## License

Distributed under the MIT License. For details refer to file "LICENSE"


## Motivation

Operator Overloading allows for the semantic augmentation of existing codes. The basic arithmetic type in a code is replaced by a user-defined type.

Type change (in theory this just works): 
    typedef scalar double -> typedef scalar userdef_double

However, several coding patterns are not compatible with user-defined classes 
and result in compile time errors
- Implicit Conversions
    - “At most one user-defined conversion [...] is implicitly 
         applied to a single value.” –  [§12.3-4, C++03 Standard]
    - Subset: 
        - Boolean Conversions: i.e., conditional statements
- Unions
    - Incompatible with complex data classes [§9.5-1, C++03 Standard]
- Explicit Conversions
    - Cast operation from a user-defined type to a built-in often not possible
- etc.


## Goal

Provide developers of (numerical) codes with static code analysis 
to avoid problematic coding patterns

For legacy numerical codes:
    - Flag potential problematic code locations
    - Ideally autocorrect them


## Installation 

TBD
