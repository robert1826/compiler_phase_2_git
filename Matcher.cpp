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
		state_stack.pop();
		if(state!="$"){
			int index = get_transition_index(tokens[i]);
			vector<string> next_states = table[state][index];
			if(table.find(state)==table.end()){
				if(state != tokens[i]){
					output.push_back("Error: missing " + state);
				}
				else{
					i++;
				}
			}
			else if(next_states.size()==0){
				state_stack.push(state);
				output.push_back("Error: Illegal " + state);
				i++;
			}
			else if(next_states.size()==1 && next_states[0]=="sync"){
				//synchronization : state is popped only
			}
			else {
				string next = "";
				for(int j = 0 ; j < next_states.size() ; j ++ ){
					next += next_states[i];
					if(j!=next_states.size()-1)next+= " ";
				}
				for(int j = next_states.size()-1 ; j > -1 ; j--){
					state_stack.push(next_states[j]);
				}
			}
		}
		else {
			if(i != tokens.size()-1 || tokens[i]!="$"){
				output.push_back("ERROR");
			}
			else if(state == tokens[i]){
				output.push_back("accept");
				print_output();
				i = tokens.size()+1;
			}
		}
		//i++;
	}
}


Matcher::~Matcher() {
	// TODO Auto-generated destructor stub
}

void Matcher::print_output(){
	ifstream is("output.txt");
	for(int i = 0 ; i < output.size() ; i ++){
		cout << output[i] << endl;
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
