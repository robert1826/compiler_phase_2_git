#define _GLIBCXX_USE_CXX11_ABI 0
#include "TableBuilder.h"
#include "First_Follow_calc.h"
#include "InputReader.h"
bool found=false;
TableBuilder::TableBuilder()
{


}
map <string,vector<vector<string>>> TableBuilder::getTable()
{
    return table;
}

void TableBuilder:: buildTable(First_Follow_calc f,InputReader in)
{
    map<string, vector<string>> first=f.getFirst();

    map<string, vector<string>> follow=f.getFollow();

    vector<string> terminals=in.terminal;
    vector<string> nonTerminals=in.nonterminal;
    map <string,vector<vector<string>>> productions;

    for(string nt: nonTerminals) //fill table row by row
    {
        vector<vector<string>> row; //row of table

        vector<string> fir_ter=first[nt];
        vector<string> fol_ter=follow[nt];
        bool go_to_eps=go_to_epsl(nt,fir_ter);

        for(string t:terminals) //fill columns of this row
        {
            found=false;
            vector<string> cell;  //cell of table
            for(string s:fir_ter) //search if this terminal is in first of nonterminals or not
            {
                if(s.compare(t)==0)  //found in first
                {
                    found=true;
                    vector<vector<string>> trans= productions[nt]; //productions of this nonterminal
                    if(trans.size()>1) //has multiple productions
                    {
                        for(vector<string> v: trans)  //get every production of this nonterminal
                        {
                            string firproduction=v[0]; //first term in production
                            if(in.is_terminal(firproduction))  //check if it is terminal
                            {
                                if(v[0].compare(t)==0)
                                {
                                    cell=v;
                                    break;
                                }
                            }
                            else  //nonterminal
                            {
                                vector<string> termi=first[v[0]]; //first of this nonterminal to check its first
                                for(string fir: termi)
                                {
                                    if(fir.compare(t)==0)
                                    {
                                        cell=termi;
                                        break;
                                        break;
                                    }
                                }
                            }

                        }
                    }
                    else   //have one production
                    {
                        cell=trans[0];
                    }
                    break;
                }
            }
            if(!found)   //search for this terminal in follow
            {
                for(string s:fir_ter) //search if this terminal is in first of nonterminals or not
                {
                    if(s.compare(t)==0)  //found in first
                    {
                        if(go_to_eps){
                            cell.push_back("&");
                        }
                        else{
                            cell.push_back("synch");
                        }
                    }
                }
            }

            row.push_back(cell);
        }
        table[nt]=row;
    }
}
bool TableBuilder::go_to_epsl(string nt, vector<string> v){
    for(string s:v){
        if(s.compare("&")==0){
            return true;
        }
    }
    return false;
}
