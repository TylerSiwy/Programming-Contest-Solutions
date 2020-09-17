//Author: Tyler Siwy
//Date: March 18, 2020
//Approach: Create a function for each case, check each one recursively and determine whether it is a slimp or slump, then check both in succession for the main.


#include <iostream>
#include <string>
using namespace std;


bool slump(string input);

bool slimp(string input);

bool slurpy(string input);

int main(){
    int noCases;
    cin >> noCases;
    cin.ignore();
    cout << "SLURPYS OUTPUT" << endl;
    for(int h=0; h < noCases; h++){
        string input;
        getline(cin, input);
        if(slurpy(input))
            cout << "YES" << endl;
        else 
            cout << "NO" << endl;
    }
    cout << "END OF OUTPUT"<<endl;
    return 0;
}

bool slump(string input){
    if(input.length() < 3)
        return false;
    if((input[0] != 'D' && input[0] != 'E') || input[1] != 'F')
        return false;
    int i=2;
    while(input[i]=='F'){
        i++;
        if(i >= input.length())
            return false;
    }
    return (input[i]=='G' && i == input.length()-1) || slump(input.substr(i));
}

bool slimp(string input){
    if(input.length() < 2)
        return false;
    if(input[0] != 'A')
        return false;
    //2 Character Slimp
    if(input.length() == 2 && input[1] == 'H')
        return true;

    if(input[1] == 'B')
        return input[input.length()-1]=='C' && slimp(input.substr(2, input.length()-3));
    else
        return input[input.length()-1]=='C' && slump(input.substr(1, input.length()-2));
}

bool slurpy(string input){
    for(int i = 1; i < input.length()-2; i++)
        if(slimp(input.substr(0,i)) && slump(input.substr(i, input.length()-1)))
            return true;
    return false;
}