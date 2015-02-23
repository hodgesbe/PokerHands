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
#include <list>

using namespace std;

string player1, player2;

void dealHands(string line){
    player1 = line.substr(0,14);
    player2 = line.substr(15,14);
}


int highCard(string playerCards){
    int highCard=0;
    
    for (int i=0; i<playerCards.length(); i+=3) {
        if (playerCards.at(i)=='2'&& 2>highCard) {
            highCard=2;
        }else if(playerCards.at(i)=='3'&& 3>highCard){
            highCard=3;
        }else if(playerCards.at(i)=='4'&& 4>highCard){
            highCard=4;
        }else if(playerCards.at(i)=='5'&& 5>highCard){
            highCard=5;
        }else if(playerCards.at(i)=='6'&& 6>highCard){
            highCard=6;
        }else if(playerCards.at(i)=='7'&& 7>highCard){
            highCard=7;
        }else if(playerCards.at(i)=='8'&& 8>highCard){
            highCard=8;
        }else if(playerCards.at(i)=='9'&& 9>highCard){
            highCard=9;
        }else if(playerCards.at(i)=='T'&& 10>highCard) {
            highCard=10;
        }else if(playerCards.at(i)=='J'&& 11>highCard){
            highCard=11;
        }else if(playerCards.at(i)=='Q'&& 12>highCard){
            highCard=12;
        }else if(playerCards.at(i)=='K'&& 13>highCard){
            highCard=13;
        }else if(playerCards.at(i)=='A'&& 14>highCard){
            highCard=14;
        }
    }
    return highCard;
}

bool hasPair(string playerCards){
    bool pair = false;
    for (int i=0; i<playerCards.length(); i+=3) {
        for (int j = i; j<playerCards.length(); j+=3) {
            if ((playerCards.at(i) == playerCards.at(j))&&!(i==j)) {
                pair = true;
            }
        }
    }
    return pair;
}

bool has2Pair(string playerCards){
    bool twoPair = false;
    int count = 0;
    
    for (int i=0; i<playerCards.length(); i+=3) {
        for (int j = 0; j<playerCards.length(); j+=3) {
            if ((playerCards.at(i) == playerCards.at(j))&&!(i==j)) {
                count ++;
            }
        }
    }
    if (count>=4) {
        twoPair = true;
    }
    return twoPair;
}

bool hasThree(string playerCards){
    bool threeKind = false;
    
    for (int i=0; i<playerCards.length(); i+=3) {
        for (int j = 0; j<playerCards.length(); j+=3) {
            for (int k = 0; k<playerCards.length(); k+=3){
                if ((playerCards.at(i) == playerCards.at(j))&&(playerCards.at(j)==playerCards.at(k))&&!(i==j)&&!(j==k)&&!(i==k)) {
                    threeKind=true;
                }
            }
        }
    }
    return threeKind;
}

bool hasStraight (string playerCards){
    list<int> cards;
    bool isStraight = true;
    int cardArr[5];
    int count;
    
    for (int i = 0; i<playerCards.length(); i+=3) {
        if(playerCards.at(i)=='A'){
            cards.push_back(1);
        }else if(playerCards.at(i)=='2'){
            cards.push_back(2);
        }else if(playerCards.at(i)=='3'){
            cards.push_back(3);
        }else if(playerCards.at(i)=='4'){
            cards.push_back(4);
        }else if(playerCards.at(i)=='5'){
            cards.push_back(5);
        }else if(playerCards.at(i)=='6'){
            cards.push_back(6);
        }else if(playerCards.at(i)=='7'){
            cards.push_back(7);
        }else if(playerCards.at(i)=='8'){
            cards.push_back(8);
        }else if(playerCards.at(i)=='9'){
            cards.push_back(9);
        }else if(playerCards.at(i)=='T'){
            cards.push_back(10);
        }else if(playerCards.at(i)=='J'){
            cards.push_back(11);
        }else if(playerCards.at(i)=='Q'){
            cards.push_back(12);
        }else if(playerCards.at(i)=='K'){
            cards.push_back(13);
        }
    }
    
    cards.sort();
    
    for (list<int>::iterator it = cards.begin(); it != cards.end(); ++it) {
        cardArr[count]=*it;
        count++;
    }
    
    while (isStraight) {
        for (int i = 0; i<5; ++i) {
            for (int j = 1; j<5; ++j) {
                if (cardArr[i]+1 == cardArr[j]) {
                    isStraight = true;
                }else{
                   isStraight = false;
                }
            }
        }
    }
    
    return isStraight;
}

bool hasFlush(string playerCards){
    bool isFlush = true;
    while (isFlush) {
        for (int i = 1; i<playerCards.length(); i+=3) {
            for (int j = 2; j<playerCards.length(); j+=3) {
                if (playerCards[i]==playerCards[j]) {
                    isFlush = true;
                }else{
                    isFlush = false;
                }
            }
        }
    }
    return isFlush;
}

bool hasFullHouse(string playerCards){
    if (hasThree(playerCards)&&has2Pair(playerCards)) {
        return true;
    }
    else{
        return false;
    }
}

bool hasFour(string playerCards){

    return true;
}

bool hasStraightFlush(string playerCards){
    
    return true;
}

bool hasRoyalFlush(string playerCards){
    
    return true;
}

//Main
int main(int argc, const char * argv[]) {
    
    ifstream infile("hands.txt");
    
    if (!infile) {
        cerr <<"Error Opening File"<<endl;
        exit(1);
    }
    
    
    int count = 0;
    string line;
    
    while (count<1000) {
        count++;
        getline(infile, line);
        dealHands(line);
        //cout<<"Player 1's hand: "<<player1<<endl;
        cout<<"Player 2's hand: "<<player2<<endl;
        //cout<<"Player 1 has Pair? " <<hasPair(player1)<<endl;
        //cout<<"Player 1 has 2Pair? " <<has2Pair(player1)<<endl;
        //cout<<"Player 2 has Three of a kind: "<<hasThree(player2)<<endl;
        //hasStraight(player2);
        //cout<<"Player 2's high card is: "<<highCard(player2)<<endl;
        cout<<"Has Straight?: "<<hasStraight(player2)<<endl;
        
    }
    
    infile.close();
    
    return 0;
}
