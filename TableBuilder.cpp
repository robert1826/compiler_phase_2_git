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

    vector<string> terminals=in.terminal;
    terminals.push_back("$");

    vector<string> nonTerminals=in.nonterminal;

    map <string,vector<vector<string>>> productions=in.getMap();

    for(string nt: nonTerminals) //fill table row by row
    {
        vector<vector<string>> row; //row of table

        vector<string> fir_ter=first[nt];
        vector<string> fol_ter=follow[nt];

        sort( fir_ter.begin(), fir_ter.end() );      //remove duplicates
        fir_ter.erase( unique( fir_ter.begin(), fir_ter.end() ), fir_ter.end() );

        sort( fol_ter.begin(), fol_ter.end() );  //remove duplicates
        fol_ter.erase( unique( fol_ter.begin(), fol_ter.end() ), fol_ter.end() );

        first[nt]=fir_ter;
        follow[nt]=fol_ter;

        bool go_to_eps=go_to_epsl(nt,fir_ter);

        for(string t:terminals) //fill columns of this row
        {
            if(t!="&")
            {
                vector<string> cell;  //cell of table
                for(string s:fir_ter) //search if this terminal is in first of nonterminals or not
                {
                    if(s.compare(t)==0)  //found in first
                    {
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
                                                cell=v;
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
                            /*
                            else
                            {
                                cout<<"5.error grammar is ambiguous\n";
                                cout<< nt <<"\n";
                                cout<< t <<"\n";
                                return false;
                            }*/
                        }
                    }
                }

                row.push_back(cell);
            }
        }
        table[nt]=row;
    }
    //printFisrtFollow(first,follow,nonTerminals);
    //printTable(terminals,nonTerminals);

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

void TableBuilder::printFisrtFollow(map<string,vector<string>> first, map<string,vector<string>> follow,vector<string> nonTerminals){
    cout << "First\n";
    for(string s:nonTerminals)
    {
        cout << s <<"\t";
        vector<string> v=first[s];
        for(string ss:v)
        {
            cout << ss << "\t";
        }
        cout <<"\n";
    }

    cout << "Follow\n";
    for(string s:nonTerminals)
    {
        cout << s <<"\t";
        vector<string> v=follow[s];
        for(string ss:v)
        {
            cout << ss << "\t";
        }
        cout <<"\n";
    }
}

void TableBuilder::printTable(vector<string> terminals, vector<string> nonTerminals)
{
    cout << "\n\t";
    for(string s:terminals)
    {
        if(s!="&")
            cout << s << "\t";
    }
    cout << "\n";
    for(string s: nonTerminals)
    {
        cout<<s << "\t";
        vector<vector<string>> temp=table[s];
        for(vector<string> v:temp)    //print row
        {
            for(string ss:v)   //print cell
            {
                cout <<ss<<" ";
            }
            cout<<"\t";
        }
        cout<<"\n";

    }
}
