#include "InputReader.h"
#ifndef FIRST_FOLLOW_CALC_H
#define FIRST_FOLLOW_CALC_H

#include <bits/stdc++.h>
using namespace std;

class First_Follow_calc
{
public:
  First_Follow_calc();
  First_Follow_calc(InputReader r);
  
  map<string, vector<string>> getFirst();
  map<string, vector<string>> getFollow();
  
private:
  InputReader reader;
  map<string, vector<string>> first;
  map<string, vector<string>> follow;
  
  vector<string> calcFirst(string s);
  vector<string> calcFollow(string s);
  
  set<string> visited;
  set<string> visited_follow;
};

#endif // FIRST_FOLLOW_CALC_H
