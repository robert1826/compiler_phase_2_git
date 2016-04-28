#ifndef FACTORIZE_H_
#define FACTORIZE_H_
#include "InputReader.h"

class Factorize {

public:
	Factorize();
	void fact(InputReader *r);
	set<int> check(vector< vector<string> >v);
private:
	map<string, vector<vector<string>>> productions;
};

#endif /* FACTORIZE_H_ */
