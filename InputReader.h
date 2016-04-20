#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <bits/stdc++.h>
using namespace std;

class InputReader
{
public:
  InputReader();
  
  // creates the productions map
  // file_name is the name of the rules file
  InputReader(string file_name); // use this one NOT the one above
 
  // returns the productions map
  map<string, vector< vector<string> > > getMap();
  bool is_terminal(string str);
  vector<string> terminal;
  vector<string> nonterminal;
private:
  map<string, vector< vector<string> > > productions;
  
};

#endif // INPUTREADER_H
