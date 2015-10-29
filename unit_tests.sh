#!/bin/bash

failed=0

function verify() {
  # returns ret indicating whether the test succeeded or failed
  ret=0
  local name=${1#.*_}
  echo -e "Test '${name%Debug}' \c"
  "$1" > /dev/shm/out_opov.log
  grep -q 'All tests passed' /dev/shm/out_opov.log && echo "succeeded."
  if [ ! $? -eq 0 ] ; then
    echo "failed!"
    ret=1    
  fi
}

for test in ./bin/test_* ; do
  verify $test
  if [ $ret -eq 1 ] ; then
    ((failed++))
  fi
done

if [ $failed -eq 1 ] ; then
  echo "# of failed tests:" $failed && exit 1
fi
