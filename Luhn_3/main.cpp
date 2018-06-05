/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bhitt
 *
 * Created on March 6, 2018, 8:47 PM
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
using namespace std;

/*
 * 
 */
enum CrdCard {American_Express,Visa,MasterCard, Discover, ALL};

char *genCC(CrdCard);
bool validCC(char []);
void flipDig(char []);
void transpose(char []);
void flip2(char []);
CrdCard picker();
void printC(char []);

int main(int argc, char** argv) {
    //set the random seed
    srand(static_cast<unsigned int>(time(0)));
    //declare some variables
    int count=0,vCount=0,ivCount=0; //various counters
    bool isALL = false;
    //pick card type
    CrdCard type = picker();
    cout<<"************"<<endl;
    //loop 10,000 times for each
    for(int i=0;i<2;i++){
        do{
            //generate a specific card
            if(type == ALL || isALL){
                type = static_cast<CrdCard>(rand()%4);
                isALL = true;
            }
            char *c = genCC(type);
                //printC(c);
            //randomly flip one digit
            //flipDig(c);
            if(i==0) transpose(c);
            else flip2(c);
                //printC(c);
            //check if card is still valid
            if(validCC(c))vCount++;
            else ivCount++;
            //increment counter
            count++;
        }while(count<10000);
        //output how many valid vs invalid
        if(i==0) cout<<"After transposing..."<<endl;
        else cout<<"After flipping 2 digits..."<<endl;
        cout<<"There were "<<vCount<<" valid cards and"<<endl;
        cout<<ivCount<<" invalid cards."<<endl;
        vCount=0;
        ivCount=0;
        count=0;
        cout<<endl;
    }

    //exit stage right
    return 0;
}

CrdCard picker(){
    short cho=0;
    CrdCard temp;
    do{ //American_Express,Visa,MasterCard, Discover, ALL
        cout<<"Enter a number for your credit card type:"<<endl;
        cout<<"1: American Express"<<endl;
        cout<<"2: Visa"<<endl;
        cout<<"3: MasterCard"<<endl;
        cout<<"4: Discover"<<endl;
        cout<<"5: ALL"<<endl;
        cin>>cho;
    }while(cho<1 || cho >5);
    switch(cho){
        case 1: temp = American_Express;
        cout<<"American Express"<<endl;
        break;
        case 2: temp = Visa;
        cout<<"Visa"<<endl;
        break;
        case 3: temp = MasterCard;
        cout<<"MaserCard"<<endl;
        break;
        case 4: temp = Discover;
        cout<<"Discover"<<endl;
        break;
        case 5: temp = ALL;
        cout<<"ALL"<<endl;
    }
    return temp;
}

void printC(char a[]){
    string temp = "";
    temp = a;
    cout<<temp<<endl;
}

//old tester function
//char *genCC(CrdCard c){
//    //American_Express,Visa,MasterCard, Discover, ALL - enum order
//    //declare some variables
//    int size=0, r=0;
//    string s = "";
//    //check for type
//    if(c==0){   //American Express
//        //size = 15;
//        s = "343393039356535";
//    }else if(c==1){   //Visa
//        //size = 16;
//        s = "4539176712776020";
//    }else if(c==2){   //MasterCard
//        //size = 16;
//        s = "5409736243652653";
//    }else if(c==3){   //Discover
//        //size = 16;
//        s = "6011801798197187";
//    }else if(c==4){
//        r = rand()% 4;
//        if(r==0)s = "343393039356535";
//        else if(r==1) s = "4539176712776020";
//        else if(r==2) s = "5409736243652653";
//        else s = "6011801798197187";
//    }else{
//        //default case
//        cout<<"Danger Will Robinson Danger"<<endl;
//        s = "0000000000000000";
//    }
//    //create char array
//    size = s.size();
//    char *a = new char[size+1];
//    for(int i=0;i<size;i++){
//        a[i]=s[i];
//    }
//    a[size]='\0';
//    return a;
//}

 char *genCC(CrdCard c) {
     int start = c + 3;
     int size = 16;
     if(c == 0)size = 15;
     else if (c == 1) size = (rand()%10)> 5? 13 : 16;
     else if (c == 4) {
             start = '0' +rand()%('3'-'6');
             size = (rand()%10)>= 3 ? 13 : (rand()%10 >=5 ? 15 : 16);
     }
     char *a = new char[size + 1];
     a[0] = start + '0';
     for(int i = 1; i < size;i++) {
             a[i] = '0' +rand()%('9'-'0');
     }
     a[size] = '\0';
     do{
             flipDig(a);
     }while(!validCC(a));
     return a;
 }

bool validCC(char c[]){
    int length = strlen(c);
    int array[length];
    for(int i = 0; i < length;i++) {
            array[i] = c[i] - '0';
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
    if((total + array[length-1]) %10 == 0) return true;
    else return false;
}

void flipDig(char a[]){
    //get length
    string temp = a;
    int length = temp.length();
    //get random index
    int index = 1 + rand()% (length-1);
        //cout<<"index:"<<index<<endl;
    //throw in new digit at the index
    int newNum = '0' +rand()%('9'-'0'+1);
        //cout<<"newNum:"<<newNum<<" ";
    a[index]=newNum;
        //cout<<"a[index]="<<a[index]<<endl;
        //temp = a;
        //cout<<"temp:"<<temp<<endl;
}


void transpose(char a[]){
    //get length
    string temp = a;
    int length = temp.length();
    //get random indexes
    int index = 1 + rand()% (length-1);
    int index2;
    do{
        index2 = 1 + rand()% (length-1);
    }while(index2==index);
    //swap two indexes
    char temp2 = a[index];
    a[index] = a[index2];
    a[index2] = temp2;
    //cout<<"index:"<<index<<endl;
    //cout<<"index2:"<<index2<<endl;
}


void flip2(char a[]){
    //get length
    string temp = a;
    int length = temp.length();
    //get random indexes
    int index = 1 + rand()% (length-1);
    int index2;
    do{
        index2 = 1 +rand()% (length-1);
    }while(index == index2);
    //throw in new digits at the indexes
    int newNum = '0' +rand()%('9'-'0'+1);
    int newNum2 = '0' +rand()%('9'-'0'+1);
    a[index]=newNum;
    a[index2]=newNum2;
}