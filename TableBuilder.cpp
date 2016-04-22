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

bool TableBuilder:: buildTable(First_Follow_calc f,InputReader in)
{
    map<string, vector<string>> first=f.getFirst();

    map<string, vector<string>> follow=f.getFollow();

   /* vector<string> E;
    E.push_back("(");
    E.push_back("id");
    first["E"]=E;

    vector<string> EE;
    EE.push_back("+");
    EE.push_back("&");
    first["EE"]=EE;

    vector<string> T;
    T.push_back("(");
    T.push_back("id");
    first["T"]=T;

    vector<string> TT;
    TT.push_back("*");
    TT.push_back("&");
    first["TT"]=TT;

    vector<string> F;
    F.push_back("(");
    F.push_back("id");
    first["F"]=F;

    vector<string> E1;
    E1.push_back("$");
    E1.push_back(")");
    follow["E"]=E1;

    follow["EE"]=E1;

    vector<string> T1;
    T1.push_back("$");
    T1.push_back(")");
    T1.push_back("+");
    follow["T"]=T1;

    follow["TT"]=T1;

    vector<string> F1;
    F1.push_back("$");
    F1.push_back(")");
    F1.push_back("+");
    F1.push_back("*");
    follow["F"]=F1;*/

    vector<string> terminals=in.terminal;
    terminals.push_back("$");
    for(string s: terminals)
        cout << s <<"\n";

    vector<string> nonTerminals=in.nonterminal;
    for(string s: nonTerminals)
        cout << s <<"\n";
    map <string,vector<vector<string>>> productions=in.getMap();

    for(string nt: nonTerminals) //fill table row by row
    {
        vector<vector<string>> row; //row of table

        vector<string> fir_ter=first[nt];
        vector<string> fol_ter=follow[nt];
        bool go_to_eps=go_to_epsl(nt,fir_ter);

        for(string t:terminals) //fill columns of this row
        {
            //found=false;
            vector<string> cell;  //cell of table
            for(string s:fir_ter) //search if this terminal is in first of nonterminals or not
            {
                if(s.compare(t)==0)  //found in first
                {
                    //found=true;
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
                                    if(cell.size()==0)
                                        cell=v;
                                    else
                                    {
                                        cout<<"1.error grammar is ambiguous\n";
                                        return false;
                                    }
                                }
                            }
                            else  //nonterminal
                            {
                                vector<string> termi=first[v[0]]; //first of this nonterminal to check its first
                                for(string fir: termi)
                                {
                                    if(fir.compare(t)==0)
                                    {
                                        if (cell.size()==0)
                                            cell=termi;
                                        else
                                        {
                                            cout<<"2.error grammar is ambiguous\n";
                                            return false;
                                        }
                                    }
                                }
                            }

                        }
                    }
                    else   //have one production
                    {
                        if (cell.size()==0)
                            cell=trans[0];
                        else
                        {
                            cout<<"3.error grammar is ambiguous\n";
                            return false;
                        }
                    }
                }
            }
            // if(!found)   //search for this terminal in follow
            //  {
            for(string s:fol_ter) //search if this terminal is in first of nonterminals or not
            {
                if(s.compare(t)==0)  //found in first
                {
                    if(go_to_eps)
                    {
                        if (cell.size()==0)
                            cell.push_back("&");
                        else
                        {
                            cout<<"4.error grammar is ambiguous\n";
                            return false;
                        }
                    }
                    else
                    {
                        if (cell.size()==0)
                            cell.push_back("synch");
                        else
                        {
                            cout<<"5.error grammar is ambiguous\n";
                            cout<< nt <<"\n";
                            cout<< t <<"\n";
                            return false;
                        }
                    }
                }
            }
            // }

            row.push_back(cell);
        }
        table[nt]=row;
    }
    cout << "\t";
    for(string s:terminals){
        cout << s << "\t";
    }
    cout << "\n";
    for(string s: nonTerminals){
        cout<<s << "\t";
        vector<vector<string>> temp=table[s];
        for(vector<string> v:temp){
            for(string ss:v){
                cout <<ss<<" ";
            }
            cout<<"\t";
        }
        cout<<"\n";

    }
    return true;
}
bool TableBuilder::go_to_epsl(string nt, vector<string> v)
{
    for(string s:v)
    {
        if(s.compare("&")==0)
        {
            return true;
        }
    }
    return false;
}
