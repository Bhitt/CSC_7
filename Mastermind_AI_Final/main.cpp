/*
 * Author: Branden Hitt
 * Purpose: implement an AI to play mastermind
 */

/* 
 * File:   main.cpp
 * Author: bhitt
 * Created on May 14, 2018, 11:34 AM
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
bool evaluate(string, string,char &, char &);       //check for game win
string aiGuess(char , char);                        //AI guessing function

int main(int argc, char** argv) {
    //declare variables
    const int XDIM=4;               //table dimensions (digits to guess + responses)
    const int YDIM=20;              //table dimensions (amount of possible guesses)
    char cDigW= 'X', cDigC= 'X';          //correct digit in wrong place or correct digit in correct place
    short turnC=1;                  //counter for turns until win
    short upper = 0, lower = 99;    //upper and lower ranges for turn count
    int average = 0;                //average turns to win the game
    int gameC=0;                    //number of games played
    int turnT=1;                    //total turns over every game
    int c=0;        //DELETE
    bool temp=true; //DELETE
    
    //set random seed
     srand(static_cast<unsigned int>(time(0)));
     
    //create 2d array, answer array, current guess array
    //int table[YDIM][XDIM] = {};
    string answerK = "    ";
    string guess = "    ";
    int range = 9;  //digits allowed from 0 to __
    
    //total guesses allowed
    //int guessC = 20;
    
    //initialize display table to zeros
//    for(int i=YDIM;i>=0;i--){
//        for(int j=XDIM;j>=0;j--){
//            table[i][j]=0;
//        }
//    }
    for(int i=0;i<200;i++){
        gameC++;
        turnC=0;
        //create answer key
        answerK = createK(range);
        cDigW = 'X', cDigC = 'X';
        //run through guesses
        do{
           //prompt for guess
           guess = aiGuess(cDigW,cDigC);
           //temp = evaluate(guess,answerK,cDigW,cDigC);
           //cout<<"cW: "<<cDigW<<"    cC: "<<cDigC<<endl;
           turnC++;
           //cout<<"turn count:"<<turnC<<endl;
           if(turnC > 25){
               cout<<"guess:"<<guess<<endl;
               cout<<"key:"<<answerK<<endl;
           }
           //check for win
        }while(evaluate(guess, answerK, cDigW, cDigC));
           //c++;
        //}while(c<20 && evaluate(guess, answerK, cDigW, cDigC));

        //find average
        turnT += turnC;
        //check for short or long game
        if(turnC < lower) lower = turnC;
        if(turnC > upper) upper = turnC;

        //single game testing output
        cout<<"********************"<<endl;
        cout<<"Turns this game: "<<turnC<<endl;
        cout<<"Final Guess: "<<guess<<endl;
        cout<<"Key: "<<answerK<<endl;
        cout<<endl;
        
        turnC=0;
    }
    
    average = turnT/gameC;
    
    //Output statistics
    cout<<"Average Turns To Win: "<<average<<endl;
    cout<<"Shortest game: "<<lower<<endl;
    cout<<"Longest game: "<<upper<<endl;
    cout<<"Games played: "<<gameC<<endl;
    
    return 0;
}

string createK(int range){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%range+'0';
    }
    return code;
}


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

/*string aiGuess(char cDigW, char cDigC){
    //declare statics
    static short index = 0;
    static string counts = "     ";
    static string running = "                ";
    static string guess = "    ";
    static bool narrow = false;
    static bool genesis = true;
    static bool threes = false;
    static bool fours = false;
    static bool flip=false;
    static short deadInd = 22;
    static short fIndex = 0; //final index
    static short inc=4;
    
    //variables
    short cW = cDigW - '0';
    short cC = cDigC - '0';
    short odds = 0;
    short evens = 0;
    short indC = 0;
    short temp=0;
    //cout<<"cW: "<<cW<<"    cC: "<<cC<<endl;
    
    if(cDigW == 'X'){//reset statics for new game
        //cout<<"First turn of new game"<<endl;
        index=0;
        counts="     ";
        running="                ";
        guess="    ";
        narrow=false;
        genesis = true;
        threes = false;
        fours = false;
        flip = false;
        deadInd = 22;
        fIndex = 0;
        inc=4;
    }else{//use information gained from previous guess
        
        if(genesis){//genesis responses
            //cout<<"cW: "<<cW<<"      cC:"<<cC<<endl;
            counts[index] =  (cW  + cC ) + '0';
            if((cW + cC) == 0) deadInd = index;
            //cout<<"Counts: "<<counts<<endl;
            if(index > 3){
                //cout<<"Counts: "<<counts<<endl;
                for(int i=0;i<5;i++){
                    if(counts[i] != '0'){ 
                        index = i;
                        //cout<<"counts: "<<counts<<endl;
                        //cout<<"Index at end of genesis: "<<index<<endl;
                        genesis = false;
                        //check for threes or fours
                        for(int t=0;t<4;t++){
                           temp+=counts[i]-'0'; 
                        }
                        if(temp==2) fours=true, flip=true;
                        if(temp==3) threes=true, flip=true;
                        break;
                    }
                }
            }else{
                index++;
            }
        }else if(!narrow){//narrow responses
            evens = cC;
            odds = (counts[index]-'0') - evens;
            indC = (counts[index]-'0');
            
            //check for threes or fours
            if(threes || fours){
                cout<<"index count:"<<indC<<" at index:"<<index<<endl;
                if(indC < cC+cW) counts[index] = (cC+cW) + '0';
                indC = (counts[index]-'0');
                odds = indC - evens;
            }
            
            //cout<<"Evens: "<<evens<<"      Odds:"<<odds<<"     IndC:"<<indC<<endl;
            //cout<<"Evens: "<<evens<<"     Odds: "<<odds<<endl;
            
            //cout<<"Narrow index: "<<index<<endl;
            if(evens == indC){ //all evens
                for(int j=1; j <= evens;j++){
                    for(int i=0;i<4;i++){
                        if(running[i] == ' '){
                            if(!flip){
                                running[i] = index*2 + '0';
                                running[i+4] = index*2 + '0';
                                running[i+8] = index*2 + '0';
                                running[i+12] = index*2 + '0';
                                //cout<<"Count: "<<counts<<endl;  //debug output
                                break;
                            }
                            running[i] = index*2 + 1 + '0';
                            running[i+4] = index*2 + 1 + '0';
                            running[i+8] = index*2 + 1 + '0';
                            running[i+12] = index*2 + 1 + '0';
                            //cout<<"Count: "<<counts<<endl;  //debug output
                            break;

                        }
                    }  
                }
            }
            
            if(odds > 0){  //odd is correct for some or all
                for(int j=1;j <= odds;j++){
                    for(int i=0;i<4;i++){
                        if(running[i] == ' '){
                            if(!flip){
                                running[i] = index*2 + 1 + '0';
                                running[i+4] = index*2 + 1 + '0';
                                running[i+8] = index*2 + 1 + '0';
                                running[i+12] = index*2 + 1 + '0';
                                //cout<<"Count: "<<counts<<endl;  //debug output
                                break;
                            }
                            running[i] = index*2 + '0';
                            running[i+4] = index*2 + '0';
                            running[i+8] = index*2 + '0';
                            running[i+12] = index*2 + '0';
                            //cout<<"Count: "<<counts<<endl;  //debug output
                            break;
                        }
                    }  
                }
            }
            
            if( (evens > 0) && (evens != indC) ){   //only some even are correct
                for(int j=1; j <= evens;j++){
                    for(int i=0;i<4;i++){
                        if(running[i] == ' '){
                            if(!flip){
                                running[i] = index*2 + '0';
                                running[i+4] = index*2 + '0';
                                running[i+8] = index*2 + '0';
                                running[i+12] = index*2 + '0';
                                //cout<<"Count: "<<counts<<endl;  //debug output
                                break;
                            }
                            running[i] = index*2 + 1 + '0';
                            running[i+4] = index*2 + 1 + '0';
                            running[i+8] = index*2 + 1 + '0';
                            running[i+12] = index*2 + 1 + '0';
                            //cout<<"Count: "<<counts<<endl;  //debug output
                            break;
                        }
                    }  
                }
            }
            
            cout<<"Running: "<<running<<endl;
            
            //step up indexing
            if(!flip){
               for(int i=index+1;i<5;i++){
                    if( counts[i] - '0' > 0 ){
                        index = i;
                        //cout<<"Stepped up index: "<<index<<endl;
                        break;
                    }
                }
            }
            if(fours || threes) !flip;
            
            
            for(int i=3;i>0;i--){
                if(running[i] == ' '){
                    break;
                }
                //cout<<"Is now narrowed down"<<endl;
                narrow=true;
            }

            
        }else{//exodus
            cout<<"running:"<<running<<endl;
            cout<<"counts:"<<counts<<endl;
            if(cC == 1 && fIndex == 0){
                //cout<<"first found: "<<guess[0]<<endl;
                running[0] = guess[0];
                //running[1] = guess[0];
                //running[2] = guess[0];
                //running[3] = guess[0];
                fIndex++;
                //cout<<"running:"<<running<<endl;
            }else if(cC == 2 && fIndex == 1){
                //cout<<"second found: "<<guess[1]<<endl;
                running[1] = guess[1];
                //running[5] = guess[1];
                //running[6] = guess[1];
                //running[7] = guess[1];
                fIndex++;
            }else if(cC == 3 && fIndex == 2){
                //cout<<"third found: "<<guess[2]<<endl;
                running[2] = guess[2];
                //running[9] = guess[2];
                //running[10] = guess[2];
                //running[11] = guess[2];
                fIndex++;
            }
        }
    }

    //craft a guess
    if(genesis){        //genesis
        guess[0]=(index)*2 +'0';
        guess[1]=(index)*2 +'0';
        guess[2]=(index)*2 +1 + '0';
        guess[3]=(index)*2 +1 + '0';
        //cout<<"index:"<<index<<endl;
    }else if(!narrow){  //narrow down to 4 final digits
        if(!flip){
            guess[0]=index*2 + '0';
            guess[1]=index*2 + '0';
            guess[2]=index*2 + '0';
            guess[3]=index*2 + '0';
        }else if(flip){
            guess[0]=index*2 + 1 + '0';
            guess[1]=index*2 + 1 + '0';
            guess[2]=index*2 + 1 + '0';
            guess[3]=index*2 + 1 + '0';
        }

    }else{              //exodus
        if(fIndex == 0){
            guess[0]=running[inc];
            guess[1]=deadInd*2 + '0';
            guess[2]=deadInd*2 + '0';
            guess[3]=deadInd*2 + '0';
        }else if(fIndex == 1){
            guess[0]=running[0];
            if(running[inc] == running[0]){
                inc++;
                if(inc>7) inc=4;
            }
            guess[1]=running[inc];
            guess[2]=deadInd*2 + '0';
            guess[3]=deadInd*2 + '0';
        }else if(fIndex == 2){
            guess[0]=running[0];
            guess[1]=running[1];
            if(running[inc] == running[0]){
                inc++;
                if(inc>7) inc=4;
            }
            if(running[inc] == running[1]){
                inc++;
                if(inc>7) inc=4;
            }
            guess[2]=running[inc];
            guess[3]=deadInd*2 + '0';
        }else{
            guess[0]=running[0];
            guess[1]=running[1];
            guess[2]=running[2];
            if(running[inc] == running[0]){
                inc++;
                if(inc>7) inc=4;
            }
            if(running[inc] == running[1]){
                inc++;
                if(inc>7) inc=4;
            }
            if(running[inc] == running[2]){
                inc++;
                if(inc>7) inc=4;
            }
            guess[3]=running[inc];
        }
        inc++;
        if(inc > 7) inc =4;
        
    }
    //send next guess
    //cout<<"Current Guess: "<<guess<<endl;
    //cout<<"----------------"<<endl;
    return guess;
}*/

string aiGuess(char cDigW, char cDigC){
    static string guess  = "    ";
    static string counts = "     ";
    static string poss   = "                ";
    static bool hold1 = false;
    static bool hold2 = false;
    static bool genesis = false;
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
        cout<<"NEW GAME START"<<endl;
        guess = "    ";
        counts = "     ";
        poss = "                ";
        hold1 = false;
        hold2 = false;
        genesis = false;
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
    //cout<<"cC:"<<cC<<"     cW:"<<cW<<endl;
    if((cC + cW > 0) && !hold1) hold1=true;
    if((cC + cW == 0) && !hold1 && !exodus) deadInd = index;
    
    if(hold1 && !hold2 && !exodus){
        //cout<<"In hold1"<<endl;
        //add to counts
        if(!exodus)counts[index] = cC + cW + '0';
        //set hold2 flag
        hold2=true;
        pastCW = cW;
        pastCC = cC;
        //cout<<"Counts:"<<counts<<endl;
    }else if(hold2 && !exodus){
        //cout<<"In hold2"<<endl;
        indC = counts[index] - '0';
        evens = cC;
        odds = indC - evens;
        //add to poss
        if(evens == indC){   //only evens from the pair
            if(pastCC > 0){
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
            if(pastCW >0){
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
                }
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
            for(int j=0;j<4;j++){
                if(poss[j]==' '&& poss[j+8]==' '){
                    poss[j] = index*2 + 1 + '0';
                    poss[j+4] = index*2 + 1 + '0';
                    poss[j+8] = index*2 + 1 + '0';
                    poss[j+12] = index*2 + 1 + '0';
                    break;
                } 
            }
//            if(cC == 2){    //two evens in their correct spots
//                for(int i=0;i<2;i++){
//                    for(int j=0;j<4;j++){
//                        if(poss[j]==' '&& poss[j+8]==' '){
//                            poss[j] = index*2 + '0';
//                            poss[j+4] = index*2 + '0';
//                            poss[j+8] = index*2 + '0';
//                            poss[j+12] = index*2 + '0';
//                            break;
//                        }
//                    }
//                }
//                for(int i=0;i<2;i++){   //the rest are odd if correct
//                    for(int j=0;j<odds;j++){
//                        if(poss[j]==' '&& poss[j+8]==' '){
//                            poss[j] = index*2 + 1 + '0';
//                            poss[j+4] = index*2 + 1 + '0';
//                            poss[j+8] = index*2 + 1 + '0';
//                            poss[j+12] = index*2 + 1 + '0';
//                            break;
//                        } 
//                    }
//                }
//            }
        }
        if(evens == 3){
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
        //cout<<"No holds bar"<<endl;
        //add to counts
        //counts[index] = cC + cW + '0';
        index++;
        if(index>4) index=4, exodus=true;
    }
    
    //catch to go into exodus
//    exodus = true;
//    for(int i=poss.length()-1;i>-1;i--){
//        if(poss[i] == ' ') exodus = false;
//        if(index==4) exodus = true;
//    }
    //cout<<"poss: "<<poss<<endl;
    
    //construct new guess
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
        //if(fInd1>4) fInd1=3;
        //if(fInd2>4) fInd2=4;
        //if(fInd3>4) fInd3=4;
        //if(fInd4>4) fInd4=4;
        
        //final round of guessing
//        do{
//            guess[0] = poss[fInd1];
//        }while(guess[0] == ' ');
//        do{
//            guess[1] = poss[fInd2 + 4];
//        }while(guess[1] == ' ');
//        do{
//            guess[2] = poss[fInd3 + 8];
//        }while(guess[2] == ' ');
//        do{
//            guess[3] = poss[fInd4 + 12];
//        }while(guess[3] == ' ');
        if(!oneTime){
            if(cC == 1 && fIndex!=1) fIndex = 1, fInd1--;
            if(cC == 2 && fIndex!=2) fIndex = 2, fInd2--;
            if(cC == 3 && fIndex!=3) fIndex = 3, fInd3--; 
        }else{
            //cout<<"This is oneTime"<<endl;
            cout<<"poss:"<<poss<<endl;
        }
        //utilizing dead index
        if(fIndex == 0){
            guess[0]=poss[fInd1];
            guess[1]=deadInd*2 + '0';
            guess[2]=deadInd*2 + '0';
            guess[3]=deadInd*2 + '0';
            fInd1++;
            oneTime=false;
        }else if(fIndex == 1){
            guess[0]=poss[fInd1];
            guess[1]=poss[fInd2 + 4];
            guess[2]=deadInd*2 + '0';
            guess[3]=deadInd*2 + '0';
            fInd2++;
        }else if(fIndex == 2){
            guess[0]=poss[fInd1];
            guess[1]=poss[fInd2 + 4];
            guess[2]=poss[fInd3 + 8];
            guess[3]=deadInd*2 + '0';
            fInd3++;
        }else{
            guess[0]=poss[fInd1];
            guess[1]=poss[fInd2 + 4];
            guess[2]=poss[fInd3 + 8];
            guess[3]=poss[fInd4 + 12];
            fInd4++;
        }
    }
    
    //cout<<"guess:"<<guess<<endl;
    return guess;
}