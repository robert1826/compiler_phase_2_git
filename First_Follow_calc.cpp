#include "InputReader.h"
#include "First_Follow_calc.h"

#include <bits/stdc++.h>
using namespace std;

#define EPS "&"

First_Follow_calc::First_Follow_calc() {

}

map<string, vector<string>> First_Follow_calc::getFollow(){
  return this -> follow;
}

map<string, vector<string>> First_Follow_calc::getFirst(){
  return this -> first;
}

First_Follow_calc::First_Follow_calc(InputReader r) {
  this -> reader = r;
  for(auto it : r.getMap()){
    visited.clear();
    calcFirst(it.first);
  }
  
  for(auto it : r.getMap()){
    visited_follow.clear();
    calcFollow(it.first);
  }
}

vector<string> First_Follow_calc::calcFirst(string s){
//   cout << "DEBUG : CALCULATING FIRST OF " << s << "\n";
  
  
  if(this -> reader.is_terminal(s)){
//     cout << "DEBUG : IT'S A TERMINAL DONE\n";
    return vector<string>{s};
  }
  
//   if(first.find(s) != first.end()){
// //     cout << "DEBUG : CACHED\n";
//     return first[s];
//   }
  
  if(visited.find(s) != visited.end()){
//     cout << "DEBUG : GOT HERE BEFORE\n";
    if(first.find(s) == first.end()){
//       cout << "DEBUG : NOT CALCULATED BEFORE RETURNING EMPTY VECTOR FOR " << s << endl;
      return vector<string>();
    }
    
    return first[s];
  }
  
  visited.insert(s);
  
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
      token_ind++;
    }
    
//     vector<string> cur_next = calcFirst(n_next[0]);
//     for(string i : cur_next)
// 	res.push_back(i);
    
    if(token_ind == n_next.size() && found_eps)
      res.push_back(EPS);
  }
  
//   cout << "DEBUG : TO RETURN\n";
  this -> first[s] = res;
  return res;
}

vector< string > First_Follow_calc::calcFollow ( string s ) {
//   cout << "DEBUG : CALCULATING FOLLOW OF " << s << endl;
  
  vector<string> res;
  if(this -> reader.is_start(s))
    res.push_back("$");
  
  if(visited_follow.find(s) != visited_follow.end()){
    if(this -> first.find(s) != this->follow.end())
      return this->follow[s];
    
    return vector<string>();
  }
  visited_follow.insert(s);
  
  vector<string> from = this -> reader.token_in[s];
  for(string prev : from){
    vector<vector<string>> productions = this -> reader.getMap()[prev];
    for(vector<string> production : productions){
      for(int i = 0; i < production.size() - 1; i++){
	if(production[i] == s){
	  visited.clear();
	  vector<string> next = calcFirst(production[i + 1]);
	  for(string j : next)
	    if(j != EPS)
	      res.push_back(j);
	    
	  bool found_eps = 1;
	  for(int j = i + 1; j < production.size() && found_eps; j++){
	    vector<string> v = calcFirst(production[j]);
	    found_eps = 0;
	    for(string u : v)
	      if(u == EPS)
		found_eps = 1;
	    
	  }
	  
	  if(found_eps){
	    vector<string> next = calcFollow(prev);
	    for(string j : next)
	    if(j != EPS)
	      res.push_back(j);
	  }
	  
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
  
  // for debug
//   if(s == "EE" and follow[s].size() > 0 and res.size() == 0)
//     cout << "OVERWRITE WITH EMPTY RES\n";
  
  this -> follow[s] = res;
  return res;
}
