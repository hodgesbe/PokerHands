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
        int hasPair(string);
        bool has2Pair(string);
        bool hasThree(string);
        bool hasStraight(string);
        bool hasFlush(string);
        bool hasFullHouse(string);
        bool hasFour(string);
        bool hasStFlush(string);
        bool hasRoyal(string);
        int whoWon(string, string);
    
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
int PokerHands::hasPair(string playerCards){
    int pairVal = 0;
    int *p = parseCardVal(playerCards);
    
        for (int i = 0; i<=handSize; i++) {
            for (int j = 0; j<=handSize; j++) {
                if ((p[i]==p[j]) && (i != j)) {
                    pairVal = p[i];
                }
            }
        }
    
    return pairVal;
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
    bool isStraight = false;
    int count = 0;
    
    for (int i = 0; i<4; i++) {
        if (p[i]+1 == p[i+1]) {
            count++;
        }
    }
    
    if (count == 4) {
        isStraight = true;
    }

    return isStraight;
}

bool PokerHands::hasFlush(string playerCards){
    bool isFlush = false;
    int count = 0;
    
    for (int i = 1; i<12; i+=3) {
        if (playerCards.at(i) == playerCards.at(i+3)) {
            count++;
        }
    }
    
    if (count == 4) {
        isFlush = true;
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

bool PokerHands::hasFour(string playerCards){
    int *p = parseCardVal(playerCards);
    bool isFour = false;
    
    if ( (p[0] == p[1]) && (p[1] == p[2]) && (p[2] == p[3])) {
        isFour = true;
    }else if ((p[1] == p[2]) && (p[2] == p[3]) && (p[3] == p[4])){
        isFour = true;
    }
    
    return isFour;
}


bool PokerHands::hasStFlush(string playerCards){
    bool isStFlush = false;
    
    if (hasFlush(playerCards) && hasStraight(playerCards)) {
        isStFlush = true;
    }
    
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

int PokerHands::whoWon(string player1Cards, string player2Cards){
    int numOfWins=0;
    
    if (hasRoyal(player1Cards) && !hasRoyal(player2Cards)) {
        numOfWins++;
    }else if (hasStFlush(player1Cards) && !hasStFlush(player2Cards)){
        numOfWins++;
    }else if (hasFour(player1Cards) && !hasFour(player2Cards)){
        numOfWins++;
    }else if (hasFullHouse(player1Cards) && !hasFullHouse(player2Cards)){
        numOfWins++;
    }else if (hasFlush(player1Cards) && !hasFlush(player2Cards)){
        numOfWins++;
    }else if (hasStraight(player1Cards) && !hasStraight(player2Cards)){
        numOfWins++;
    }else if (hasThree(player1Cards) && !hasThree(player2Cards)){
        numOfWins++;
    }else if (has2Pair(player1Cards) && !has2Pair(player2Cards)){
        numOfWins++;
    }else if (hasPair(player1Cards) && !hasPair(player2Cards)){
        numOfWins++;
    }else if (highCard(player1Cards)>highCard(player2Cards)){
        numOfWins++;
    }
    
    return numOfWins;
}



//Main
int main(int argc, const char * argv[]) {
    
    PokerHands play;
    string player1, player2, line;
    ifstream infile("test.txt");
    //ifstream infile("hands.txt");
    int count = 0;
    int p1GamesWon = 0;
    
    if (!infile) {
        cerr <<"Error Opening File"<<endl;
        exit(1);
    }
    
    

    
    while (count<1000) {
        count++;
        getline(infile, line);
        player1 = play.dealP1(line);
        player2 = play.dealP2(line);
        p1GamesWon+=play.whoWon(player1, player2);

        


    }
    
    cout<<"Player 1 won "<<p1GamesWon<<" hands!"<<endl;
    infile.close();
    
    return 0;
}
