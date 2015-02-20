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
        cout<<"Player 1's hand: "<<player1<<endl;
        cout<<"Player 2's hand: "<<player2<<endl;
    }
    
    infile.close();
    
    return 0;
}
