#define _GLIBCXX_USE_CXX11_ABI 0

#include "InputReader.h"
#include "Lexical_Dummy.h"

#ifndef TABLEBUILDER_H
#define TABLEBUILDER_H

// takes the rules file and builds the parsing table
// after calculating FIRST and FOLLOW for every non terminal
// how to check is a string is a terminal ?
// if(map.find(str) == m.end) -> it's a terminal

class TableBuilder
{
public:
  TableBuilder();
  TableBuilder(InputReader reader); // use this one
 
};

#endif // TABLEBUILDER_H
