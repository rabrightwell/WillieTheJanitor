#include "4_drink.h"
#include "3_lunch.h"
#include "2_janitor.h"
#include "1_school.h" 

/* Constructor
----------------------------------------------------------------------*/
  /* Default Constructor: Creates janitor with object given input name and representation.

    Post: BAC, bruises, states and states set to default values. Location set to (-1,-1). 

  */
  janitor::janitor(string n, char r): name(n), representation(r)
  {
    bac = 0.05 ;
    bruises = 0 ;
    drunk = false ;
    dead = false ;
    hungry = true ;
    location.row = -1 ;
    location.column = -1 ;
  }

/* Public
----------------------------------------------------------------------*/

/* Initialize Janitor: Sets janitor locaiton to equivalent location on map.
    Pre: School with declared size

    Post: Updates janitor location coordinates (does NOT stream location to school map)
*/
    void janitor::initJanitor(school & mySchool)
    {
      list<coord> temp = mySchool.getLocList() ;

      int medLocation = (mySchool.getSize()-1) /2 ; //Finds middle (rounded down)
      
      location.row = medLocation ;
      location.column = medLocation ;

      temp.remove(location) ;
      /* Information on remove function from:
          http://www.cplusplus.com/reference/list/list/remove/

          Figured out that I needed to use an == operator on my own though :)
      */

      mySchool.setLocList(temp) ;

      return ;
    }

/* Next Move:
    Pre: 

    Post: 
*/
    void janitor::nextMove(school & mySchool, lunch & l, drink drinkContainer[])
    {
      mySchool.map[location.row][location.column] = ' ' ;
      if(drunk)
      {
        moveDrunk() ;
      }
      else
      {
        moveSober(l) ;
      }
      effectMovement(mySchool, drinkContainer) ;
      mySchool.map[location.row][location.column] = representation ;
      checkDrunk() ;
      checkDead() ;

      return ;
    }

/* Private
----------------------------------------------------------------------*/
void janitor::moveSober(lunch & l)
{
  coord goal = l.getLocation() ;
  
  toLocation = location ;

  //Move left, right
    if((location.column - goal.column) > 0)
    {
      toLocation.column = location.column - 1 ; //move left
    }
    
    if((location.column - goal.column) < 0)
    {
      toLocation.column = location.column + 1 ; //move right
    }
  //Move up, down  
    if((location.row - goal.row) > 0)
    {
      toLocation.row = location.row - 1 ; //move up
    }

    if((location.row - goal.row) < 0)
    {
      toLocation.row = location.row + 1 ; //move down
    }

  return ;
}

void janitor::moveDrunk()
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

  }
  
void janitor::effectMovement(school & mySchool, drink container[])
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

    case 'L' :
      moveToL() ;
    break ;

    case 'D' :
      moveToD(container) ;
    break ;

    case 'B' :
      moveToB(mySchool) ;
    break ;

    case 'T' :
      moveToT() ;
    break ;
  }
}

  void janitor::moveTo_()
  {
    location = toLocation ;
    return ;
  }

  void janitor::moveToW()
  {
    location = toLocation ;
    defenestrated = true ;
    return ;
  }

  void janitor::moveToL()
  {
    location = toLocation ;
    hungry = false ;
    return ;
  }

  void janitor::moveToD(drink container[])
  {
    float effect ;
    
    location = toLocation ;
    drink temp = chooseDrink(container) ;
    effect = temp.getEffect() ;
    bac += effect ;
    return ;
  }

  void janitor::moveToB(school & mySchool)
  {
    bruises++ ;
  }

  void janitor::moveToT()
  {
    location = toLocation ;
    bruises += 5 ;
  }

  drink janitor::chooseDrink(drink container[])
    {
      bool isFound = false ;
      
      int i = 0 ;
      while(!isFound)
      {
        if (location == container[i].getLocation())
        {
          isFound = true ;
        }
        i++ ;
      }
      
      return container[i] ;
    }


void janitor::checkDrunk()
{
  if(bac > 0.08)
  {
    drunk = true ;
    cout << name << " is drunk! In school?? Shame on you!" << endl ;
  }
  if((bac < 0.08) && (drunk == true))
  {
    drunk = false ;
    cout << name << " is no longer drunk." << endl ;
  }

  return ;
}

void janitor::checkDead()
{
  if(bac > 0.25)
  {
    dead = true ;
    cout << name << " is dead! Oh, what will the children think?!" << endl ;
  }

  return ;
}



//Overloaded Operator for Testing
ostream& operator<< (ostream& out, janitor j)
{
  out << j.name << " Stats\n\t Location: " << j.location << "\n\tBruises: " << j.bruises << "\n\tDrunk? " << (j.drunk ? "Yes" : "No") << "\n\tBAC: " << j.bac << "\n\tDefenestrated? " << (j.defenestrated ? "Yes" : "No") ; 
  return out ;
}