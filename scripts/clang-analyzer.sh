#!/bin/bash
# Requires llvm-3.8-runtime package for scan-view-3.8

folder=build_scan
analyzer=scan-build-3.8

if [[ ! $(type -p $analyzer) ]] ; then
  echo "Clang static analyzer (-3.8) not in path: " "$analyzer"
  exit 1
fi

if [[ -d $folder ]] ; then
  echo "Folder already exists: " "$folder"  
  if [[ $1 == "clean" ]] ; then
    echo "Removing.."
    rm -I -r "$folder"
  else
    echo "Did not pass option 'clean': Aborting."
    exit 1
  fi
fi

mkdir "$folder"
cd "$folder"

$analyzer cmake -DBINARY_OUTPUT_DIRECTORY="$folder" ..
$analyzer -v -V -stats \
          -o html_report \
          -enable-checker alpha \
          -enable-checker core \
          -enable-checker optin \
          -enable-checker optin.performance.Padding \
          -enable-checker llvm \
          -enable-checker security \
          make -j4

