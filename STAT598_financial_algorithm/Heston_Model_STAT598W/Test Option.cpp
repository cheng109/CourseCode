#include <iostream>
#include "Option.h"
#include <queue>
using namespace std;

int main(){
    Option O(1.0,0.09,0.03,2,0.1,0.2,0.5,2.0);
    cout << O.getPrice() << endl;

    EuropeanCall E(100.0,0.09,0.03,0.01,0.1,0.01,0.5,2.0,100.0);
    cout << "Price: " << E.getPrice() << endl;
    
    //upOutPut E(1.0,0.08,0.03,2,0.1,0.2,0.5,2.0,1.0, 1.00);
    //cout << E.getPrice() << endl;
     return 0;
}