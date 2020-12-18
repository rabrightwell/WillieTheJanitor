#include "3_lunch.h"
#include "1_school.h" 

/* Table of Contents:

*/

/* Constructor
----------------------------------------------------------------------*/
  /* Default Constructor: Initializes lunch object

    Post: Creates lunch object with location set to coordinate (-1,-1)

  */

  lunch::lunch(char r): representation(r)
  {
    location.row = -1 ;
    location.column = -1 ;
  }


/* Initialize Lunch : Sets lunch location

  Pre: List of available locations, location variable to store.

  Post: Updates location variable, updates location list w/lunch locaiton removed.

*/
void lunch::initLunch(school & mySchool)
{
  
  //Pull in available locations
  list<coord> temp = mySchool.getLocList() ;

  list<coord>::iterator it ;
  
  it = temp.begin() ;
  advance (it, rand()%temp.size()) ;
  location = *it ;
  temp.erase(it) ;

  mySchool.setLocList(temp) ;

  return ;
}

void lunch::nextMove(school & mySchool)
    {
      mySchool.map[location.row][location.column] = ' ' ;
      move() ;
      effectMovement(mySchool) ;
      mySchool.map[location.row][location.column] = representation ;

      return ;
    }

/* Private Functions 
--------------------------------------------------------------------------------------------*/
//Movement Functions
void lunch::move()
{
  //Back Bools: Will determine whether movement sense is negative (T) or positive (F)
  bool rowBack = rand()%2 ;
  bool colBack = rand()%2 ;

  //Senses, based on bools, either -1 or 1
  int rowSense ; 
  int colSense ; 

  //Setting Row Sense
  if (rowBack)
  {
    rowSense = -1 ;
  }
  else
  {
    rowSense = 1 ;
  }

  //Setting Column Sense
  if (colBack)
  {
    colSense = -1 ;
  }
  else
  {
    colSense = 1 ;
  }

  toLocation.row = rowSense * rand()%2 + location.row ;
  toLocation.column = colSense * rand()%2 + location.column ;

  return ;
}

//Interaction Functions
  void lunch::effectMovement(school & mySchool)
    {
      if(!trapped)
      {
        int i = toLocation.row ;
        int j = toLocation.column ;

        char key = mySchool.getMapChar(i,j) ;

        switch (key)
        {
          case ' ':
            moveTo_() ;
          break ;

          case 'W' :
            moveToW() ;
          break ;

          case 'J' :
            moveToJ() ;
          break ;

          case 'D' :
            moveToD() ;
          break ;

          case 'B' :
            moveToB() ;
          break ;

          case 'T' :
            moveToT() ;
          break ;
        }
      }
    }

  void lunch::moveTo_()
    {
      if(location == toLocation)
      {
        cout << "The lunch is standing still. You better run 'fore I get ya!" << endl ;
      }
      else 
      {
        cout << "The lunch is moving to " << toLocation << endl ;
      }
      location = toLocation ;
      return ;
    }

  void lunch::moveToW()
    {
      cout << "The lunch is trying to jump out the window! Stupid lunch, you can't do that!" << endl ;
      return ;
    }

  void lunch::moveToJ()
  {
    cout << "The lunch is trying to jump on the janitor! Stupid lunch, you can't do that!" << endl ;
    return ;
  }

  void lunch::moveToD()
  {
    cout << "The lunch is trying to drink the drink! Stupid lunch, you can't do that!" << endl ;
    return ;
  }

  void lunch::moveToB()
  {
    cout << "The lunch is banging its head against the wall. Stupid lunch!" << endl ;
    return ;
  }

  void lunch::moveToT()
  {
    location = toLocation ;
    trapped = true ;
    cout << "The lunch is trapped!" << endl ;
    return ;
  }
