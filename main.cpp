#define _GLIBCXX_USE_CXX11_ABI 0
#include <bits/stdc++.h>
#include "InputReader.h"
#include "First_Follow_calc.h"
#include "TableBuilder.h"
#include "Matcher.h"
#include "Factorize.h"
#include "Eliminate_left_recursion.h"

using namespace std;

int main(int argc, char **argv) {
	InputReader r;
	//r.printing();cout << "################################" << endl;
	Eliminate_left_recursion e;
	e.elimination(&r);
	Factorize f;
	f.fact(&r);
	//r.printing();cout << "################################" << endl;
	r.token_in_cal();
	First_Follow_calc calc(r);
	TableBuilder t;
	if (t.buildTable(calc, r)) {
		ifstream is("tokens.txt");
		string input;
		vector<string> tokens;
		while (!is.eof()) {
			getline(is, input);
			tokens.push_back(input);
		}
		is.close();
		vector<string> transitions;
		r.terminal.push_back("$");
		//cout<<r.terminal[0];
		//r.terminal.erase(r.terminal.begin(), r.terminal.begin() + 1);
		for (int i = 0; i < r.terminal.size(); ++i) {
			if(r.terminal[i]=="&"){
				r.terminal.erase(r.terminal.begin()+i, r.terminal.begin()+ i + 1);
			}
		}
		/* for (int i = 0; i < r.terminal.size(); i++) {
		 cout << "___" << r.terminal[i] << endl;
		 }
		 */
		Matcher m = Matcher(tokens,r.terminal,t.getTable(), r.start);
	}

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
