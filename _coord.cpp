#include "_coord.h"
#include <ostream>
#include <list>

using namespace std;

bool operator == (coord lhs, coord rhs)
{
  bool row = false ;
  bool column = false ;

  row = (lhs.row == rhs.row) ;
  column = (lhs.column == rhs.column) ;

  return (row && column) ;
}

ostream & operator << (ostream & out, coord location)
{
  out << "( " << location.row << " , " << location.column << " )" << endl ;
  return out ;
}

ostream & operator << (ostream & out, list<coord> locList)
{
  for(list<coord>::iterator it = locList.begin(); it!=locList.end(); it++)
  {
    cout << ' ' << *it << "\n" ;
  }
  return out ;
}
