#include "1_school.h"
#include "2_janitor.h"
#include "3_lunch.h"
#include "4_drink.h"

/*Includes all school member functions.
  Constructors:
    1. Default Constructor
  
  Public Functions:
    Accessors:
      1. getSize  
    
    
    1.
    2.
    3.
  
  Private Functions:
    1.
    2.

*/

/* Constructor
----------------------------------------------------------------------*/
//Size, Window Freq, Num Drinks, Num Traps
school::school(const int s, const int w,  const int d, const int t): size(s), freq_windows(w), num_drinks(d), num_traps(t)
{
  //Error Handling -- Kills program if not physically possible
  //Lunch Can't Fit in Squares Alloted
    if (s>25)
    {
      cout << "Exceeds maximum allowable dimensions." << endl ;
      exit(1) ;
    }

    if (s<4)
    {
      cout << "Not enough space in school to run simulation" << endl ;
      exit(2) ;
    }

    if(d>drink::MAX_DRINKS)
    {
      cout << "Array Error: Declared drinks exceeds drink maximum of " << drink::MAX_DRINKS << endl ;
      exit(3) ;
    }

    if(t>MAX_TRAPS)
    {
      cout << "Array Error: Declared traps exceeds trap maximum of " << MAX_TRAPS << endl ;
      exit(4) ;
    }

    int sizeCheck = (s-2)*(s-2) ;

    if (sizeCheck-2-d-t < 0)
    {
      cout << "Number of requested elements exceeds possible spaces." << endl ;
      exit(5) ;
    }

  clearSchool() ;
  assignSchool() ;
  initLocList() ;
}


/* Public Functions
---------------------------------------------------------------------
*/
  //Initializaiton Functions ---------------------
    void school::initTraps()
    {
      for(int i = 0; i<num_traps ; i++)
      { 
        list<coord>::iterator it ;

        it = locList.begin() ;
        advance (it, rand()%locList.size()) ; 
        trapContainer[i] = *it ;
        locList.erase(it) ;
      }

      return ;
    }

    void school::place(janitor j)
    {
      coord location = j.getLocation() ;
      jrepresentation = j.representation ;
      map[location.row][location.column] = 'J' ; //No matter printed representation, underlying matrix carries J

      return ;
    }

    void school::place(lunch l)
    {
      coord location = l.getLocation() ;
      lrepresentation = l.representation ;
      map[location.row][location.column] = 'L' ; //No matter printed representation, underlying matrix carries L

      return ;
    }

    void school::place(drink d)
    {
      coord location = d.getLocation() ;
      map[location.row][location.column] = 'D' ;

      return ;
    }

    void school::placeTraps()
    {
      for (int i = 0; i<num_traps ; i++)
      { 
        map[trapContainer[i].row][trapContainer[i].column] = 'T' ;
      }
    }





/* Private Functions
----------------------------------------------------------------------
*/
  //Build Functions ----------------
    
    void school::clearSchool()
    {
      for (int i = 0; i<MAX; i++)
      {
        for(int j=0; j<MAX; j++)
        {
          map[i][j] = '\0' ;
        }
      }
      return ;
    }
      
    void school::assignSchool()
    {
      for (int i = 0; i<size; i++)
        for (int j = 0; j<size; j++)
        {
          if (i == 0 || i == (size-1)) //Assigns B/W to horizontal bounds
          {
            if (((j+1)%freq_windows) == 0) //Hor. Window
            {
              map[i][j] = 'W' ;
            }
            else
            {
              map[i][j] = 'B' ;
            }
          }
          else 
          {if (j == 0 || j == (size-1)) //Assigns B/W to vertical bounds
          {
          if (((i+1)%freq_windows) == 0) //Vert. Window
            {
              map[i][j] = 'W' ;
            }
            else
            {
              map[i][j] = 'B' ;
            }
          }
          else
          {
            map[i][j] = ' ' ;
          }}
      }
      //Corners Override
      map[0][size-1] = 'B' ;
      map[size-1][size-1] = 'B' ;
      return ;
    }

    void school::initLocList()
    {
      //Creating free area array to copy from.
      int area = (size-2)*(size-2) ;
      coord myArray[area] ;
      int h = 0 ;

      for (int i = 1; i<(size-1); i++)
      { 
        for (int j = 1; j<(size-1); j++)
        {   
          myArray[h].row = i ;
          myArray[h].column = j ;
          h++ ;
        }
      }

      list<coord> tempList (myArray, myArray+area);

      /*Assistance with initializing list from 
        http://www.cplusplus.com/reference/list/list/assign/

        http://www.cplusplus.com/reference/list/list/list/
      */

      locList = tempList ;
      
      return ;
    }

    


/* Friend Functions
------------------------------------------
*/
  //Overloaded Operators
    
    ostream& operator << (ostream & out, school & mySchool)
    {
      for (int i=0; i< mySchool.size; i++)
      {  for (int j=0; j<mySchool.size; j++)
        {
          switch (mySchool.map[i][j])
          {
            //Blank Spot on Map
            case ' ' :
              out << "   " ;
            break ;
            //Border Wall
            case 'B' :
              if (i == 0) //If horizontal boundary desired
                out << "---" ;
              else {
              if (i == (mySchool.size-1))
                out << "---" ; 
              else {
              if (j==0) //If vertical boundary desired
                out << "|  " ;
              else {
              if (j == (mySchool.size-1))
                out << "  |" ; }}}
            break ;
            //Window
            case 'W' :
              out << "   " ;
            break ;
            //Janitor
            case 'J' :
              out << " " << mySchool.jrepresentation << " ";
            break ;
            //Lunch
            case 'L' :
              out << " L " ;
            break ;
            //Drink
            case 'D' :
              out << " D " ;
            break ;
            //Trap
            case 'T' :
              out << " T " ;
            break ;
          }
        }
        cout << endl ;
      }
      return out ;
    }
