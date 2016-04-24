/*
 * Matcher.cpp
 *
 *  Created on: 20 Apr 2016
 *      Author: Mahmoud
 */

#include "Matcher.h"
using namespace std;

Matcher::Matcher() {
	// TODO Auto-generated constructor stub

}

Matcher::Matcher(vector<string> tok , vector<string> trans , map< string , vector< vector<string>>> table , string start){
	tokens = tok;
	tokens.push_back("$");
	transitions = trans;
	state_stack.push("$");
	state_stack.push(start);
	int i = 0;
	while(i<tokens.size()){
		string state = state_stack.top();
		cout <<state << "  "  <<  tokens[i] << endl;
		state_stack.pop();
		if(state!="$"){
			int index = get_transition_index(tokens[i]);
			//vector<string> next_states = &table[state][index];
			if(table.find(state)==table.end()){
				cout << state << "____" << tokens[i] << endl;
				if(state != tokens[i] && state!="&"){
					output.push_back("Error: missing " + state);
				}
				else if (state!="&"){
					i++;
				}
			}
			else if(table[state][index].size()/*next_states.size()*/==0 || index ==-1){
				output.push_back("Error: Illegal " + state);
				if(i!=tokens.size()-1){
					i++;
					state_stack.push(state);
				}
			}
			else if(table[state][index].size()/*next_states.size()*/==1 && table[state][index][0]/*next_states[0]*/=="synch"){
				cout << index  << endl;
				//synchronization : state is popped only
			}
			else {
				string next = "";
				for(int j = 0 ; j < table[state][index].size()/*next_states.size()*/ ; j ++ ){
					next += table[state][index][j]/*next_states[j]*/;
					if(j!=table[state][index].size()/*next_states.size()*/-1)next+= " ";
				}
				output.push_back(next);
				for(int j = table[state][index].size()/*next_states.size()*/-1 ; j > -1 ; j--){

					if(state!="&")state_stack.push(table[state][index]/*next_states*/[j]);
				}

			}
		}
		else {
			if(i != tokens.size()-1 || tokens[i]!="$"){
				output.push_back("ERROR");
			}
			else if(state == tokens[i]){
				output.push_back("accept");
				i = tokens.size()+1;
			}
		}
	}

	print_output();
}


Matcher::~Matcher() {
	// TODO Auto-generated destructor stub
}

void Matcher::print_output(){
	ofstream is("output.txt");
	for(int i = 0 ; i < output.size() ; i ++){
		is << output[i] << endl;
	}
	is.close();
}


int Matcher::get_transition_index(string transition){
	int index = -1;
	for(int i = 0 ; i < transitions.size() ; i++){
		if(transitions[i] == transition){
			index = i;
			break;
		}
	}
	return index;
}
