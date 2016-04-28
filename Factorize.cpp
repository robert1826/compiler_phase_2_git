/*
 * Factorize.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: A
 */

#include "Factorize.h"

Factorize::Factorize() {
}

void Factorize::fact(InputReader *r) {
	map<string, vector<vector<string>>> p = r->getMap();

	for (auto a : p) {
		vector< vector<string> >vv;
		set<int> st = check(a.second);
		if(st.empty()) {
			productions[a.first] = a.second;
		}
		else {
			for(int index = 0; index<a.second.size();index++) {
				if(st.find(index) == st.end()) {
					vv.push_back(a.second[index]);
				}
			}
			string newstr = a.first+"_3";
			vector<string> v;
			v.push_back(a.second[0][0]);
			v.push_back(newstr);
			vv.push_back(v);
			productions[a.first] = vv;

			//NEW Production rule
			vector< vector<string> >vv1;
			for(int index:st) {
				vector<string> v1;
				for (int i = 1; i < a.second[index].size(); ++i) {
					v1.push_back(a.second[index][i]);
				}
				if(v1.size()==0){
					v1.push_back("&");
				}
				vv1.push_back(v1);
			}
			r->nonterminal.push_back(newstr);
			productions[newstr] = vv1;
		}
	}
	r->setMap(productions);
}

set<int> Factorize::check(vector<vector<string> > v) {
	set<int> s;
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (v[i][0] == v[j][0]) {
				s.insert(i);
				s.insert(j);
			}
		}
	}
	return s;
}

