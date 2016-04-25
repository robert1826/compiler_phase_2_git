#define _GLIBCXX_USE_CXX11_ABI 0
#include <bits/stdc++.h>
#include "InputReader.h"
#include "First_Follow_calc.h"
#include "TableBuilder.h"
#include "Matcher.h"
#include "Eliminate_left_recursion.h"

using namespace std;

int main ( int argc, char **argv ) {
    InputReader r;
    Eliminate_left_recursion e;
    e.elimination(&r);
    First_Follow_calc calc(r);
    TableBuilder t;
    if(t.buildTable(calc, r)){
    	ifstream is("tokens.txt");
    	 string input ;
    	 vector<string> tokens;
    	  while(!is.eof()){
    	   	getline(is,input);
    	   	tokens.push_back(input);
        }
   	   is.close();
   	   vector<string> transitions;
   	   r.terminal.erase(r.terminal.begin() , r.terminal.begin()+1);
   	   r.terminal.push_back("$");
   	   for(int i = 0 ; i < r.terminal.size();i++){
   		   cout << "___" << r.terminal[i] << endl;
   	   }
   	   Matcher m = Matcher(tokens , r.terminal/* {"(" , ")" , "*" , "+" , "id" , "$"}*/ , t.getTable(),r.start);
    }

    cout << "5alas" << endl;

//     for(int i = 0; i < 70; i++)
//       cout << "#";
//     cout << "robert code\n";
//
//     for(auto i : r.getMap()){
//       cout << "[" << (i.first) << "]" << "\n";
//       for(vector<string> v : i.second){
// 	for(string s : v)
// 	  cout << s << " | ";
// 	cout << "\n";
//       }
//       cout << "END OF " << (i.first) << "\n\n";
//     }


//     for ( int i = 0; i < 70; i++ )
//         cout << "#";
//     cout << endl;

//     map<string, vector<string>> first_map = calc.getFirst();
//     for ( auto i : first_map ) {
//         cout << "[" << ( i.first ) << "]" << "\n";
//         for ( string s : ( i.second ) )
//             cout << s << " | ";
//         cout << "\nEND OF " << ( i.first ) << "\n\n";
//     }
//
//
//     for ( int i = 0; i < 70; i++ )
//         cout << "#";
//     cout << endl;
// //     cout << "robert code\n";
//
//
//     map<string, vector<string>> follow_map = calc.getFollow();
//     for ( auto i : follow_map ) {
//         cout << "[" << ( i.first ) << "]" << "\n";
//         for ( string s : ( i.second ) )
//             cout << s << " | ";
//         cout << "\nEND OF " << ( i.first ) << "\n\n";
//     }

    return 0;
}
