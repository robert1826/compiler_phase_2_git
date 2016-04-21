#define _GLIBCXX_USE_CXX11_ABI 0
#include <bits/stdc++.h>
#include "InputReader.h"
#include "First_Follow_calc.h"
using namespace std;

int main(int argc, char **argv) {
    InputReader r;
    First_Follow_calc calc(r); 
    
    
//     for(int i = 0; i < 70; i++)
//       cout << "#";
//     cout << "robert code\n";
//     
//     for(auto i : r.getMap()){
//       cout << (i.first) << "\n";
//       for(vector<string> v : i.second){
// 	for(string s : v)
// 	  cout << s << " | ";
// 	cout << "\n";
//       }
//       cout << "END OF " << (i.first) << "\n\n";
//     }
    
//     map<string, vector<string>> first_map = calc.getFirst();
//     for(auto i : first_map){
// 	cout << (i.first) << "\n";
// 	for(string s : (i.second))
// 	  cout << s << " | ";
// 	cout << "\nEND OF " << (i.first) << "\n\n";
//     }
    
    
//     map<string, vector<string>> follow_map = calc.getFollow();
//     for(auto i : follow_map){
// 	cout << (i.first) << "\n";
// 	for(string s : (i.second))
// 	  cout << s << " | ";
// 	cout << "\nEND OF " << (i.first) << "\n\n";
//     }
    
    return 0;
}
