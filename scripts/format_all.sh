#!/bin/bash

find -regextype posix-egrep -regex ".*\.(h|cpp|hpp)" \( -path "./include/*" -o -path "./src/*" \) -not -path "./include/external/*" -exec clang-format -i -style=file -fallback-style=none {} \;

