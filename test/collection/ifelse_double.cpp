// RUN: find-type -config=%S/conf_double.json %s -- | FileCheck %s -check-prefix=CHECK-DOUBLE

typedef double scalar;

double a = 10.0, b = 10.5, c = 11.0, d = 11.0;
int ai = 0.0, bi = 0.0, ci = 0.0, di = 0.0;

void container(){
    // CHECK-DOUBLE: [[@LINE+1]]:5: [IfElseAssign]
    if(a == 0.){
        a = b;
    }
    else{
        a = c;
    }
}
