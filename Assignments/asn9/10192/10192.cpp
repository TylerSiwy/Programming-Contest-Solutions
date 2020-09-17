//Author: Tyler Siwy
//Date: March 19, 2020
//Approach: Using dynamic programming, check from i,j to 0. Check if the spots in i-1 and j-1 are matching and increase the subtring length, then continue checking recursively, Otherwise check all substrings for i-1 and j-1 and pick the largest one.


#include <iostream>
#include <string>
#include <vector>
using namespace std;

int lcss(int i, int j, string s1, string s2, vector<vector<int>> &table);

int main(){
    int cases = 0;
    while(true){
        if(cases > 0)
            cout << endl;
        cases++;
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);
        vector<vector<int>> table(s1.length()+1, vector<int>(s2.length() + 1, - 1));
        if(s1[0]=='#')
            break;
        cout << "Case #" << cases << ": you can visit at most " <<
        lcss(s1.length(), s2.length(), s1,s2,table) << " cities.";
    }
    return 0;
}

int lcss(int i, int j, string s1, string s2, vector<vector<int>> &table){
    if(table[i][j] < 0){
        if(i == 0 || j == 0){
            table[i][j] = 0;
        }else{
            if(s1[i-1] == s2[j-1]){
                table[i][j] = lcss(i-1, j-1, s1, s2, table) + 1;
            }else{
                table[i][j] = max(
                    lcss(i-1, j, s1, s2, table),
                    lcss(i, j-1, s1, s2, table));
            }
        }
    }
    return table[i][j];
}