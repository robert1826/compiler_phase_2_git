/*
 * Matcher.h
 *
 *  Created on: 20 Apr 2016
 *      Author: Mahmoud
 */

#ifndef COMPILER_PHASE_2_GIT_MATCHER_H_
#define COMPILER_PHASE_2_GIT_MATCHER_H_
#include<bits/stdc++.h>
using namespace std;

class Matcher {
public:
	Matcher();
	virtual ~Matcher();
	Matcher(vector<string> tokens , vector<string> transitions , map< string , vector< vector< string>>> table , string start);
	stack<string> state_stack;
	vector<string> output;
	vector<string> transitions;
	vector<string> tokens;
	void print_output();
	int get_transition_index(string transition);
};

#endif /* COMPILER_PHASE_2_GIT_MATCHER_H_ */
