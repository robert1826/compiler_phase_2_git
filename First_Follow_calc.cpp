#include "InputReader.h"
#include "First_Follow_calc.h"

#include <bits/stdc++.h>
using namespace std;

#define EPS "&"

First_Follow_calc::First_Follow_calc() {

}

map<string, vector<string>> First_Follow_calc::getFollow(){}

map<string, vector<string>> First_Follow_calc::getFirst(){}

First_Follow_calc::First_Follow_calc(InputReader r) {
  this -> reader = r;
}

vector<string> First_Follow_calc::calcFirst(string s){
  if(this -> reader.is_terminal(s))
    return vector<string>{s};
  
  vector< vector<string> > next = this -> reader.getMap()[s];
  vector<string> res;
  
  for(vector<string> n : next)
    for(string i : n)
      if(i == EPS){
	res.push_back(EPS);
	break;
      }
  
  for(vector<string> n_next : next){
    int token_ind = 0;
    bool found_eps = 1;
    while(found_eps && token_ind < n_next.size()){
      found_eps = 0;
      vector<string> cur_next = calcFirst(n_next[token_ind]);
      for(string i : cur_next){
	res.push_back(i);
	if(i == EPS)
	  found_eps = 1;
      }
    }
    
    if(token_ind == n_next.size() && found_eps)
      res.push_back(EPS);
  }
  
  this -> first[s] = res;
  return res;
}

vector< string > First_Follow_calc::calcFollow ( string s ) {
  // TODO handle EPS
  // TODO handle follow(A) is to get follow(A) i.e cycle
  
  vector<string> from = this -> reader.token_in[s];
  vector<string> res;
  if(this -> reader.is_start(s))
    res.push_back("$");
  
  for(string prev : from){
    for(vector<string> production : this -> reader.getMap()[prev]){
      for(int i = 0; i < production.size() - 1; i++){
	if(production[i] == s){
	  vector<string> next = calcFirst(production[i + 1]);
	  for(string j : next)
	    if(j != EPS)
	      res.push_back(j);
	  break;
	}
      }
      
      if(production[production.size() - 1] == s){
	  vector<string> next = calcFollow(prev);
	  for(string j : next)
	    if(j != EPS)
	      res.push_back(j);
      }
     }
  }
      
  
  return res;
}
