#ifndef FIRST_FOLLOW_CALC_H
#define FIRST_FOLLOW_CALC_H

#include <bits/stdc++.h>
using namespace std;

class First_Follow_calc
{
public:
  First_Follow_calc();
  
  map<string, vector<string> > getFirst;
  map<string, vector<string> > getFollow;
  
private:
  map<string, vector<string> > first;
  map<string, vector<string> > follow;
};

#endif // FIRST_FOLLOW_CALC_H
