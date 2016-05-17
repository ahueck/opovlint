#!/bin/bash

format=clang-format

# clang-format-3.6 does not support all file entries 
# TODO check compatibility with clang-format-3.7 
for v in 3.8 3.7 ; do
  if [[ $(type -p clang-format-"$v") ]] ; then  
    format=clang-format-"$v"
    break
  fi
done

find -regextype posix-egrep -regex ".*\.(h|cpp|hpp)" \
         \( -path "./include/*" -o -path "./src/*" \) -not -path "./include/external/*" \
         -exec "$format" -i -style=file -fallback-style=none {} \;

