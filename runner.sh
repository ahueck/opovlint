#!/bin/bash

debug=0

function verify() {
    if [ $debug -eq 1 ] ; then
        local suffix="Debug";
    fi
    echo -e "Test '$1' \c"
    ./bin/test_$1$suffix > /dev/shm/out_opov.log
    grep -q 'All tests passed' /dev/shm/out_opov.log && echo "succeeded." || echo "failed!"
}

verify system
verify union_matcher
verify implicitconversion
verify implicitcond_matcher
#verify implicitcond
verify explicitcast
verify conditionalassgn
verify explicitconstructor
verify allimplicitconversion
