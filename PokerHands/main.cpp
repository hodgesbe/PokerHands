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

char player1[5], player2[5];
int ccount=0;

void dealHands(string line){
    for (int i=0; i<line.length(); ++i) {
        cout<<line.at(i)<<endl;
    }
    cout<<endl;
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
    }
    
    infile.close();
    
    return 0;
}
