#define _GLIBCXX_USE_CXX11_ABI 0
#include "InputReader.h"

InputReader::InputReader() {
	start = "&";
	string line;
	ifstream myfile("grammar.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line[0] == '#') {
				string name;
				stringstream ss(line);
				getline(ss, name, '=');
				name.erase(remove(name.begin(), name.end(), '#'), name.end());
				name.erase(remove(name.begin(), name.end(), ' '), name.end());

				string def;
				getline(ss, def);
				size_t start_pos = def.find(" | ");
				while (start_pos != std::string::npos) {
					def.replace(start_pos, 3, "|");
					start_pos = def.find(" | ");
				}
				if (def[0] == ' ') {
					def = def.substr(1, def.length());
				}
// 				cout << name << endl;
				if (start == "&")
					start = name;
				terminal.push_back(name);
// 				cout << def << endl;
				vector<string> v = tokinze(def, "|", name);

				for (int i = 0; i < v.size(); ++i) {
					vector<string> vv = tokinze(v[i], " ", name);
					productions[name].push_back(vv);
				}
// 				cout << endl;
			}
		}
		myfile.close();
		for (string s : nonter) {
			nonterminal.push_back(s);
// 			cout << s << endl;
		}
		cout << endl;
		for (auto s : terminal) {
// 			cout << s << endl;
		}
		cout << endl;
		vector<string> vvv = token_in["SIMPLE_EXPRESSION"];
		for (auto s : vvv) {
// 			cout << s << endl;
		}
	}
// 	cout << "============================" << endl;
	vector<vector<string> > vv = productions["SIMPLE_EXPRESSION"];
	for (int i = 0; i < vv.size(); ++i) {
		vector<string> v = vv[i];
		for (int j = 0; j < v.size(); ++j) {
// 			cout << v[j] << endl;
		}
// 		cout << endl;
	}
}

vector<string> InputReader::tokinze(string str, char* c, string origin) {
	unsigned int i;
	char s[str.length() + 1];
	for (i = 0; i < str.length(); ++i) {
		s[i] = str[i];
	}
	s[i] = '\0';
	vector<string> v;
	char *pch;
	pch = strtok(s, c);
	while (pch != NULL) {
		v.push_back(pch);
		pch = strtok(NULL, c);
	}
	for (int j = 0; j < v.size() && c[0] == ' '; ++j) {
		int size = v[j].size();
		v[j].erase(remove(v[j].begin(), v[j].end(), '\''), v[j].end());
		if (size != v[j].length()) {
			nonter.insert(v[j]);
		}
		else {
			token_in[v[j]].push_back(origin);
			//cout<<"*****"<<origin<<"<="<<v[j]<<endl;
		}
	}
	/*
	 for (i = 0; i < v.size(); ++i) {
	 cout << v[i] << "==";
	 }

	 cout<<"*" << endl;
	 */
	return v;
}

bool InputReader::is_terminal(string str) {
	if (productions.find(str) == productions.end()) {
		return true;
	}
	return false;
}
bool InputReader::is_start(string s) {
	if (s == start)
		return true;
	return false;
}

map<string, vector<vector<string> > > InputReader::getMap(){
  return this -> productions;
}
