/*
 * Branden Hitt
 * Luhn Algorithm
 */

/* 
 * File:   main.cpp
 * Author: bhitt
 * Created on February 16, 2018, 9:55 PM
 */

#include <iostream>
using namespace std;

/*
 * 
 */
int main() {
    cout << "Credit Card Validation" << endl;
    string credit = "344053814204172";   //test cases
    //string credit = "35738dfjsbnd472";

    cout << "Input a credit card number: ";
    cin>>credit;

    int length = credit.size();
    int array[length];

    for(int i = 0; i < length;i++) {
            array[i] = credit[i] - '0';
    }

    // 
    int total = 0;

    //reverse loop
    bool s = true;
    for(int i = length-2; i >= 0;i--){
            if(s) {
                    array[i] *=2;
                    if(array[i] > 9) array[i]-=9;;
            }
            s = !s;
            total+=array[i];
    }
    if((total + array[length-1]) %10 == 0) cout << "Valid Card" <<endl;
    else cout << "Failed Validation" << endl;

    return 0;
}