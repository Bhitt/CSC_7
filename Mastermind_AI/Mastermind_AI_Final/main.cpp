/*
 * Author: Branden Hitt
 * Purpose: implement an AI to play mastermind
 */

/* 
 * File:   main.cpp
 * Author: bhitt
 * Created on June 01, 2018, 11:34 AM
 */

#include <iostream> //io
#include <cstdlib>  //rand
#include <regex>    //regular expression
#include <string>   //string.length

using namespace std;

/*
 * 
 */
//Function Prototypes
string createK( int);                          //create key (dupes allowed, four digits)
bool evaluate(string, string,char &, char &);  //check for game win
string aiGuess(char , char);                   //AI guessing function

int main(int argc, char** argv) {
    //declare variables
    char cDigW= 'X', cDigC= 'X';    //correct digit in wrong place or correct digit in correct place
    short turnC=1;                  //counter for turns until win
    short upper = 0, lower = 99;    //upper and lower ranges for turn count
    int average = 0;                //average turns to win the game
    int gameC=0;                    //number of games played
    int turnT=1;                    //total turns over every game
    
    //set random seed
     srand(static_cast<unsigned int>(time(0)));
     //variables
    string answerK = "    ";
    string guess = "    ";
    int range = 10;  //digits allowed
    
    //loop over the games played
    for(int i=0;i<1000;i++){
        gameC++;
        turnC=0;
        //create answer key
        answerK = createK(range);
        //default response to create a new game
        cDigW = 'X', cDigC = 'X';
        //run through guesses
        do{
           //prompt for guess
           guess = aiGuess(cDigW,cDigC);
           //increment turn count
           turnC++;
           //check for win
        }while(evaluate(guess, answerK, cDigW, cDigC));

        //find average
        turnT += turnC;
        //check for shortest or longest game
        if(turnC < lower) lower = turnC;
        if(turnC > upper) upper = turnC;

        //single game testing output
        cout<<"********************"<<endl;
        cout<<"Turns this game: "<<turnC<<endl;
        cout<<"Final Guess: "<<guess<<endl;
        cout<<"Key: "<<answerK<<endl;
        cout<<endl;
        
    }
    //compute average
    average = turnT/gameC;
    
    //Output statistics
    cout<<"Average Turns To Win: "<<average<<endl;
    cout<<"Shortest game: "<<lower<<endl;
    cout<<"Longest game: "<<upper<<endl;
    cout<<"Games played: "<<gameC<<endl;
    //exit stage right
    return 0;
}

//function to create a key
string createK(int range){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%range+'0';
    }
    return code;
}

//function to evaluate the most recent guess and provide feedback
bool evaluate(string guess, string code, char &cDigW, char &cDigC){
    int cW=0,cC=0;
    string check="    ";
    //Check how many are in the correct place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            cC++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                cW++;
                check[i]='x';
                break;
            }
        }
    }
    cDigC = cC + '0';
    cDigW = cW + '0';
    //Found or not
    if(cC==4)return false;
    return true;
}

string aiGuess(char cDigW, char cDigC){
    //static variables in ai function
    static string guess  = "    ";
    static string counts = "     ";
    static string poss   = "                ";
    static bool hold1 = false;
    static bool hold2 = false;
    static bool exodus = false;
    static bool oneTime = true;
    static short index = -1;
    static short deadInd = 0;
    static short fIndex = 0;
    static short pastCW = 0;
    static short pastCC = 0;
    static short fInd1 = 0;
    static short fInd2 = 0;
    static short fInd3 = 0;
    static short fInd4 = 0;
    if(cDigC == 'X'){ //new game reset
        //cout<<"NEW GAME START"<<endl;
        guess = "    ";
        counts = "     ";
        poss = "                ";
        hold1 = false;
        hold2 = false;
        exodus = false;
        oneTime = true;
        index = -1;
        deadInd = 0;
        fIndex = 0;
        pastCW = 0;
        pastCC = 0;
        fInd1 = 0;
        fInd2 = 0;
        fInd3 = 0;
        fInd4 = 0;
        cDigW = '0';
        cDigC = '0';
    }
    
    //variables
    short cC = cDigC -'0';
    short cW = cDigW - '0';
    short evens = 0;
    short odds = 0;
    short indC = 0;
    
    
    //evaluate response
    if((cC + cW > 0) && !hold1) hold1=true;
    if((cC + cW == 0) && !hold1 && !exodus) deadInd = index;
    
    //initial phase
    if(hold1 && !hold2 && !exodus){
        //add to counts
        if(!exodus)counts[index] = cC + cW + '0';
        //set hold2 flag
        hold2=true;
        pastCW = cW;
        pastCC = cC;
    }else if(hold2 && !exodus){
    //secondary phase
        indC = counts[index] - '0';
        evens = cC;
        odds = indC - evens;
        //add to poss
        if(evens == indC){   //only evens from the pair
            //rare case where 3 evens and one odd (5444)
            if(indC==3 && cC ==3){ //(4454 or 4445)
                for(int j=0;j<4;j++){
                    if(poss[j]==' ' && poss[j+8]==' '){
                        poss[j] = index*2 + '0';
                        poss[j+4] = index*2 + '0';
                        poss[j+8] = index*2 + '0';
                        poss[j+12] = index*2 + '0';
                        break;
                    }
                }//add odds
                for(int j=0;j<4;j++){
                    if(poss[j]==' ' && poss[j+8]==' '){
                        poss[j] = index*2 + 1 + '0';
                        poss[j+4] = index*2 + 1 + '0';
                        poss[j+8] = index*2 + 1 + '0';
                        poss[j+12] = index*2 + 1 + '0';
                        break;
                    }
                }
                
            }
            else{
                if(pastCC > 0){ //some evens were in the correct place
                    for(int i=0;i<pastCC;i++){
                        for(int j=0;j<4;j++){
                            if(poss[j]==' '){
                                poss[j] = index*2 + '0';
                                poss[j+4] = index*2 + '0';
                                break;
                            }
                        }
                    }
                }
                if(pastCW >0){ //some evens were in the wrong place
                    for(int i=0;i<pastCW;i++){
                        for(int j=8;j<12;j++){
                            if(poss[j]==' '){
                                poss[j] = index*2 + '0';
                                poss[j+4] = index*2 + '0';
                                break;
                            }
                        }
                    }
                }
            } 
            
        }
        if(evens == 0){   //only odds from the pair
            if(pastCW > 0){ // the odds were in the wrong place
                for(int i=0;i<pastCW;i++){
                    for(int j=0;j<4;j++){
                        if(poss[j]==' '&& poss[j+8]==' '){
                            poss[j] = index*2 + 1 + '0';
                            poss[j+4] = index*2 + 1 + '0';
                            break;
                        }
                    }
                }
            }
            if(pastCC >0){ //the odds were in the correct place
                for(int i=0;i<pastCC;i++){
                    for(int j=8;j<12;j++){
                        if(poss[j]==' '){
                            poss[j] = index*2 + 1 + '0';
                            poss[j+4] = index*2 + 1 + '0';
                            break;
                        }
                    }
                }
            }
        }
        if((evens > 0) && (evens < indC)){  //both evens and odds
            //add the evens
            for(int j=0;j<4;j++){
                if(poss[j]==' '&& poss[j+8]==' '){
                    poss[j] = index*2 + '0';
                    poss[j+4] = index*2 + '0';
                    poss[j+8] = index*2 + '0';
                    poss[j+12] = index*2 + '0';
                    break;
                }
            }
            //add the odds
            for(int j=0;j<4;j++){
                if(poss[j]==' '&& poss[j+8]==' '){
                    poss[j] = index*2 + 1 + '0';
                    poss[j+4] = index*2 + 1 + '0';
                    poss[j+8] = index*2 + 1 + '0';
                    poss[j+12] = index*2 + 1 + '0';
                    break;
                } 
            }
        }
        if(evens == 3){ //three evens
            for(int i=0;i<3;i++){
                for(int j=0;j<4;j++){
                    if(poss[j]==' '&& poss[j+8]==' '){
                        poss[j] = index*2 + '0';
                        poss[j+4] = index*2 + '0';
                        poss[j+8] = index*2 + '0';
                        poss[j+12] = index*2 + '0';
                        break;
                    }
                }
            }
        }
        if(evens == 4) { //all the same even number
            for(int j=0;j<4;j++){
                    if(poss[j]==' '&& poss[j+8]==' '){
                        poss[j] = index*2 + '0';
                        poss[j+4] = index*2 + '0';
                        poss[j+8] = index*2 + '0';
                        poss[j+12] = index*2 + '0';
                        exodus = true;
                        break;
                    }
                }
        }
        //reset both holds
        hold1=false;
        hold2=false;
        index++;
        if(index>4) index=4, exodus=true;
    }else{
        index++;
        if(index>4) index=4, exodus=true;
    }
    //construct a new guess
    if(!hold1 && !exodus){
        //guess half even, half odd to start
        guess[0] = index*2 + '0';
        guess[1] = index*2 + '0';
        guess[2] = index*2 + 1 + '0';
        guess[3] = index*2 + 1 + '0';
    }else if(hold2 && !exodus){
        //guess all even to narrow down
        guess[0] = index*2 + '0';
        guess[1] = index*2 + '0';
        guess[2] = index*2 + '0';
        guess[3] = index*2 + '0';
    }else if(exodus){
        //check for first guess during exodus phase
        if(!oneTime){
            if(cC == 1 && fIndex!=1) fIndex = 1, fInd1--;
            if(cC == 2 && fIndex!=2) fIndex = 2, fInd2--;
            if(cC == 3 && fIndex!=3) fIndex = 3, fInd3--; 
        }
        //utilizing dead index, narrow down from poss string
        if(fIndex == 0){
            //guessing first digit
            while(poss[fInd1]==' '){
                fInd1++;
            };
            guess[0]=poss[fInd1];
            guess[1]=deadInd*2 + '0';
            guess[2]=deadInd*2 + '0';
            guess[3]=deadInd*2 + '0';
            fInd1++;
            oneTime=false;
        }else if(fIndex == 1){
            //guessing second digit
            while(poss[fInd2 + 4]==' '){
                fInd2++;
            };
            guess[0]=poss[fInd1];
            guess[1]=poss[fInd2 + 4];
            guess[2]=deadInd*2 + '0';
            guess[3]=deadInd*2 + '0';
            fInd2++;
        }else if(fIndex == 2){
            //guessing third digit
            while(poss[fInd3 + 8]==' '){
                fInd3++;
            };
            guess[0]=poss[fInd1];
            guess[1]=poss[fInd2 + 4];
            guess[2]=poss[fInd3 + 8];
            guess[3]=deadInd*2 + '0';
            fInd3++;
        }else{
            //guessing fourth digit
            while(poss[fInd4 + 12]==' '){
                fInd4++;
            };
            guess[0]=poss[fInd1];
            guess[1]=poss[fInd2 + 4];
            guess[2]=poss[fInd3 + 8];
            guess[3]=poss[fInd4 + 12];
            fInd4++;
        }
    }
    //cout<<"poss:"<<poss<<endl;  (testing output)
    //cout<<"guess:"<<guess<<endl; (testing output)
    
    //return the guess
    return guess;
}