#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <bits/stdc++.h>
using namespace std;

class InputReader {
public:
	InputReader();

	// creates the productions map
	// file_name is the name of the rules file
	InputReader(string file_name); // use this one NOT the one above
	vector<string> tokinze(string str, char* c, string origin);
	// returns the productions map
	map<string, vector<vector<string> > > getMap();
	//set the production map
	void setMap(map<string, vector<vector<string> > > p);
	bool is_terminal(string str);
	vector<string> terminal;
	vector<string> nonterminal;
	map<string, vector<string> > token_in; //NEED FIXING
	bool is_start(string s);
	void printing();
	string start;
private:
	map<string, vector<vector<string> > > productions;
	set<string> nonter;

};

#endif // INPUTREADER_H
