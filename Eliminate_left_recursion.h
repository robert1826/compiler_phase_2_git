#ifndef ELIMINATE_LEFT_RECURSION_H
#define ELIMINATE_LEFT_RECURSION_H
#include "InputReader.h"


class Eliminate_left_recursion
{
    public:
        Eliminate_left_recursion();
        virtual ~Eliminate_left_recursion();
        void elimination(InputReader *r);
        void eliminate_imm_LR(string nt,vector<vector<string>> prods_of_nt);
        void print_productions();
    private:
        map <string,vector<vector<string>>> productions;
        vector<string> nonTerminals;
};

#endif // ELIMINATE_LEFT_RECURSION_H
