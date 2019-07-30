// RUN: find-type -config=%S/conf.json %s -- | FileCheck %s

typedef double scalar;

scalar a = 10.0, b = 10.5, c = 11.0, d = 11.0;
int ai = 0.0, bi = 0.0, ci = 0.0, di = 0.0;

void container(){
    // CHECK: [[@LINE+1]]:5: [IfElseAssign]
    if(a == 0.){
        a = b;
    }
    else{
        a = c;
    }
}
