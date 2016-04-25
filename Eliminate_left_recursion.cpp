#include "Eliminate_left_recursion.h"
#include "InputReader.h"


Eliminate_left_recursion::Eliminate_left_recursion()
{
    //ctor
}

Eliminate_left_recursion::~Eliminate_left_recursion()
{
    //dtor
}

void Eliminate_left_recursion::elimination(InputReader *r)
{
    productions=r->getMap();
    nonTerminals=r->nonterminal;

    for(int i=0; i<nonTerminals.size(); i++)
    {
        for(int j=0; j<=i-1; j++)
        {
            vector<vector<string>> v_Ai=productions[nonTerminals[i]];
            vector<vector<string>> v_Aj=productions[nonTerminals[j]];
            vector<vector<string>> new_v_Ai;

            for(vector<string> vi:v_Ai)
            {
                if(vi[0]==nonTerminals[j])
                {
                    for(vector<string> vj: v_Aj)
                    {
                        vector<string> prod;
                        prod.insert(prod.end(), vj.begin(), vj.end());
                        for(int k=1; k<vi.size(); k++)
                        {
                            prod.push_back(vi[k]);
                        }
                        new_v_Ai.push_back(prod);
                    }
                }
                else
                {
                    new_v_Ai.push_back(vi);
                }

            }
            productions[nonTerminals[i]]=new_v_Ai;
        }
        eliminate_imm_LR(nonTerminals[i],productions[nonTerminals[i]]);
    }
    r->setMap(productions);
    r->nonterminal=nonTerminals;
    r->printing();

}

void Eliminate_left_recursion:: eliminate_imm_LR(string nt,vector<vector<string>> prods_of_nt)
{
    //sort according to start
    for(int i=0; i<prods_of_nt.size(); i++)
    {
        vector<string> v=prods_of_nt[i];
        if(nt==v[0])
        {
            prods_of_nt.erase(prods_of_nt.begin()+i);
            prods_of_nt.insert(prods_of_nt.begin(),v);
        }
    }

    bool add_new_nt=false;
    int last_index;
    vector<vector<string>> prods_new_nt;
    for(int i=0; i<prods_of_nt.size(); i++ )
    {
        vector<string> v=prods_of_nt[i];
        vector<string> temp;
        if(nt==v[0])
        {
            last_index=i;
            if(!add_new_nt)
                nonTerminals.push_back(nt+"_2");
            for(int i=1; i<v.size(); i++)
            {
                temp.push_back(v[i]);
            }
            temp.push_back(nt+"_2");
            add_new_nt=true;
            prods_new_nt.push_back(temp);

        }
        else if(add_new_nt)
        {
            v.push_back(nt+"_2");
            prods_of_nt[i]=v;
        }
    }

    vector<string> eps;
    eps.push_back("&");
    if(prods_new_nt.size()>0)
        prods_new_nt.push_back(eps);

    if(add_new_nt){
        prods_of_nt.erase(prods_of_nt.begin(),prods_of_nt.begin()+last_index+1);
        productions[nt+"_2"]=prods_new_nt;
    }
    productions[nt]=prods_of_nt;


}

void Eliminate_left_recursion::print_productions()
{

    for(string nt:nonTerminals)
    {
        cout << nt << "\t";
        vector<vector<string>> vv=productions[nt];
        // cout << "size of productions "<< vv.size() << endl;
        for(vector <string> v: vv )
        {
            for (int k=0; k<v.size(); k++)
            {
                cout<<v[k]<< " ";
            }
            cout << "\t";
        }
        cout << endl;
    }
}
