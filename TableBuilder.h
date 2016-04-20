#define _GLIBCXX_USE_CXX11_ABI 0

#include "InputReader.h"
#include "Lexical_Dummy.h"
#include <bits/stdc++.h>
using namespace std;
#ifndef TABLEBUILDER_H
#define TABLEBUILDER_H
#include "First_Follow_calc.h"

// takes the rules file and builds the parsing table
// after calculating FIRST and FOLLOW for every non terminal
// how to check is a string is a terminal ?
// if(map.find(str) == m.end) -> it's a terminal

class TableBuilder {
public:
	TableBuilder();
	TableBuilder(InputReader reader); // use this one

	map <string,vector<vector<string>>> getTable();
	void buildTable(First_Follow_calc f,InputReader in);
	bool go_to_epsl(string nt, vector<string> v);
private:
    map <string,vector<vector<string>>> table;

};

#endif // TABLEBUILDER_H
