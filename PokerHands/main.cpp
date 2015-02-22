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

using namespace std;

string player1, player2;

void dealHands(string line){
    player1 = line.substr(0,14);
    player2 = line.substr(15,14);
}


int highCard(string playerCards){
    int highCard=0;
    
    for (int i=0; i<playerCards.length(); i+=3) {
        if (playerCards.at(i)=='T'&& 10>highCard) {
            highCard=10;
        }else if(playerCards.at(i)=='J'&& 11>highCard){
            highCard=11;
        }else if(playerCards.at(i)=='Q'&& 12>highCard){
            highCard=12;
        }else if(playerCards.at(i)=='K'&& 13>highCard){
            highCard=13;
        }else if(playerCards.at(i)=='A'&& 14>highCard){
            highCard=14;
        }else if((int)playerCards.at(i)>highCard){
            highCard=(int)playerCards.at(i);
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
        cout<<"Player 2 has Three of a kind: "<<hasThree(player2)<<endl;
    }
    
    infile.close();
    
    return 0;
}
