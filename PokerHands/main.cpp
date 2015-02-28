//
//  main.cpp
//  PokerHands
//
//  Created by Brett Hodges on 2/19/15.
//  Copyright (c) 2015 Brett Hodges. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

using namespace std;

class PokerHands{
    
    const int handSize = 5;

    public:
    
        string dealP1(string);
        string dealP2(string);
        int *parseCardVal(string);
        int highCard(string);
        bool hasPair(string);
        bool has2Pair(string);
        bool hasThree(string);
        bool hasStraight(string);
        bool hasFlush(string);
        bool hasFullHouse(string);
        bool hasFour(string);
        bool hasStFlush(string);
        bool hasRoyal(string);
    
};

string PokerHands::dealP1(string line){
    return line.substr(0,14);
}

string PokerHands::dealP2(string line){
    return line.substr(15,14);
}

int* PokerHands::parseCardVal(string playerCards){
    static int cardArr[5];
    int count=0;
    
    for (int i = 0; i<playerCards.length(); i+=3) {
        if(playerCards.at(i)=='2'){
            cardArr[count]= 2;
            count++;
        }else if(playerCards.at(i)=='3'){
            cardArr[count]= 3;
            count++;
        }else if(playerCards.at(i)=='4'){
            cardArr[count]= 4;
            count++;
        }else if(playerCards.at(i)=='5'){
            cardArr[count]= 5;
            count++;
        }else if(playerCards.at(i)=='6'){
            cardArr[count]= 6;
            count++;
        }else if(playerCards.at(i)=='7'){
            cardArr[count]= 7;
            count++;
        }else if(playerCards.at(i)=='8'){
            cardArr[count]= 8;
            count++;
        }else if(playerCards.at(i)=='9'){
            cardArr[count]= 9;
            count++;
        }else if(playerCards.at(i)=='T'){
            cardArr[count]= 10;
            count++;
        }else if(playerCards.at(i)=='J'){
            cardArr[count]= 11;
            count++;;
        }else if(playerCards.at(i)=='Q'){
            cardArr[count]= 12;
            count++;
        }else if(playerCards.at(i)=='K'){
            cardArr[count]= 13;
            count++;
        }else if(playerCards.at(i)=='A'){
            cardArr[count]= 14;
            count++;
        }
    }
    
    sort(cardArr, cardArr+handSize);

    return cardArr;
}

int PokerHands::highCard(string playerCards){
    int card = parseCardVal(playerCards)[4];
    return card;
}

//Need to fix returns true at 3 of a kind
bool PokerHands::hasPair(string playerCards){
    
    bool isPair = false;
    int *p = parseCardVal(playerCards);
    
        for (int i = 0; i<=handSize; i++) {
            for (int j = 0; j<=handSize; j++) {
                if ((p[i]==p[j]) && (i != j)) {
                    isPair = true;
                }
            }
        }
    
    return isPair;
}

bool PokerHands::has2Pair(string playerCards){
    int *p = parseCardVal(playerCards);
    bool is2Pair = false;
    int firstPair = 0;
    int pairCount = 0;
    
    for (int i = 0; i<=handSize; i++) {
        for (int j = 0; j<=handSize; j++) {
            if ((p[i]==p[j]) && (i != j) && (p[i] != firstPair)) {
                firstPair = p[i];
                pairCount++;
            }
            if (pairCount>1) {
                is2Pair = true;
                break;
            }
        }
    }
    
    
    return is2Pair;
}

bool PokerHands::hasThree(string playerCards){
    int *p = parseCardVal(playerCards);
    bool threeAlike = false;
    
    for (int i = 0; i<=handSize; i++) {
        for (int j = 0; j<=handSize; j++) {
            for (int k = 0; k<=handSize; k++) {
                if ((p[i] == p[j]) && (p[j] == p[k]) && (i != j) && (j != k) && (i != k)) {
                    threeAlike = true;
                }
            }
        }
    }
    return threeAlike;
}

bool PokerHands::hasStraight(string playerCards){
    int *p = parseCardVal(playerCards);
    bool isStraight = true;
    int count = 0;
    
    while (isStraight && count<4) {
        if (p[count]+1 == p[count+1]) {
            count++;
            hasStFlush(playerCards);
        }else
            isStraight = false;
    }


    return isStraight;
}

bool PokerHands::hasFlush(string playerCards){

    bool isFlush = true;
    int count = 1;
    
    while (isFlush && count<12) {
        if (playerCards.at(count) == playerCards.at(count+3)) {
            count+=3;
            hasStFlush(playerCards);
        }else
            isFlush = false;
    }
    
    return isFlush;
}

//Should work once hasPair fixed
bool PokerHands::hasFullHouse(string playerCards){
    bool isFullHouse = false;
    
    if (hasThree(playerCards) && hasPair(playerCards)) {
        isFullHouse = true;
    }
    
    return isFullHouse;
}

//Need to finish hasFour
bool PokerHands::hasFour(string playerCards){
    int *p = parseCardVal(playerCards);
    bool isFour = false;
    int count = 0;
    
    for (int i = 0; i<handSize; i++) {
        for (int j = 0; j<handSize; j++) {
            if ((i != j) && (p[i] == p[j])) {
                count++;
            }
        }
    }
    
    if (count == 4) {
        isFour = true;
    }
    
    return isFour;
}

// Program explodes for some reason
bool PokerHands::hasStFlush(string playerCards){
    bool isStFlush = false;

    /*
    if (hasStraight(playerCards) && hasFlush(playerCards)) {
        isStFlush = true;
    }
    */
    return isStFlush;
}


bool PokerHands::hasRoyal(string playerCards){
    int *p = parseCardVal(playerCards);
    bool isRoyal = false;
    
    if (hasFlush(playerCards) && (p[0] == 10)) {
        if (hasStraight(playerCards)) {
            isRoyal = true;
        }
        
    }
    
    return isRoyal;
}




//Main
int main(int argc, const char * argv[]) {
    
    PokerHands play;
    string player1, player2, line;
    ifstream infile("test.txt");
    //ifstream infile("hands.txt");
    int count = 0;
    
    if (!infile) {
        cerr <<"Error Opening File"<<endl;
        exit(1);
    }
    
    

    
    while (count<1000) {
        count++;
        getline(infile, line);
        player1 = play.dealP1(line);
        player2 = play.dealP2(line);
        cout<<"Deal #: "<<count<<" - Player 1's hand: "<<player1<<endl;
        cout<<"Deal #: "<<count<<" - Player 2's hand: "<<player2<<endl;
        cout<<endl;
        cout<<"Player 1 has Four?: "<<play.hasRoyal(player1)<<endl;
        cout<<endl;
        //cout<<"Player 1 has straight?: "<<play.hasStraight(player1)<<endl;
        cout<<endl;
        


    }
    
    infile.close();
    
    return 0;
}
