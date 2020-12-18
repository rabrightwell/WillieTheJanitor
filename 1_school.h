#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <string>
#include <list>
#include "_coord.h"
#include "1_school.h"
using namespace std ;

class janitor ;
class lunch ;
class drink ;

const int MAX_TRAPS = 20 ;

class school
{
  public:
    //Constructor -------------
      /* Default Constructor
        Pre: Requires input of size, window frequency, number of drinks, and number of traps

        Post: Updates school object with given inputs. Initializes location list to be used for object placement within the map. Sets all map values to '\0'. Sets boundaries and windows based on size.
        Kills program if declared inputs cannot all fit on the declared map size or if greater than maximum size of 25, numDrinks of 20, or numTraps of 10. 
      */
      school (const int s = MAX, const int w = 4,  const int d = 4, const int t = 0) ;

    //Public -------------------
      //Accessors
      inline int getSize() const {return size; };
      inline int getNum_Drinks() const {return num_drinks ;} ;
      inline char getMapChar(int a, int b) {return map[a][b];} ;
      inline list<coord> getLocList() const {return locList;} ;

      //Mutators
      inline void setLocList(list<coord> updateList) {locList = updateList ; return;} ;

      //Initialization
        /* Initialize Traps: 
        */
        void initTraps() ;

        //Overloaded Place Function + PlaceTrap Function
          /* Janitor Place: Places janitor and appropriate character on board.
            Pre: Representation character for janitor, coordinate location of janitor.

            Post: Updates jrepresentation for terminal display; map array element at corresponding janitor location updated to 'J'.
          */
          void place(janitor j) ;

          /* Lunch Place: Places lunch and appropriate character on board.
            Pre: Representation character for lunch, coordinate location of janitor.

            Post: Updates lrepresentation for terminal display; map array element at corresponding janitor location updated to 'L'.
          */
          void place(lunch l) ;

          /* Drink Place: Places one drink on board.
            Pre: Object of drink class with location

            Post: Updates Map array element at corresponding janitor location updated to 'D'.
          */
          void place(drink d) ;

          /* Place Traps: Places numTraps traps on board.
            Pre: 

            Post: Updates 
          */
          void placeTraps() ;
    
    //Friend ---------------

      friend class janitor ;
      friend class lunch ;

      /* School << Overload: Overloads << so that representation of school is printed when cout << school performed.
      Pre: 2D character array with meaningful data represented by:
        'B' (boundary)
        'W' (window)
        ' ' (blank space within map)
        'J' (janitor)
        'L' (lunch)
        'D' (drink)
        'T' (trap)

      Post: No change to array; output displayed on terminal
      */
      friend ostream& operator << (ostream & out, school & mySchool) ;

  private:
    //Build Variables
    static const int MAX = 25 ;
    char map[MAX][MAX] ;
    short size ;
    list<coord> locList ; //list of all spaces within borders, updated during initialization as locations are filled

    //Game Variables
    short num_drinks ;
    short num_traps ;
    short freq_windows ;
    string jrepresentation ; //Streamed in by place(janitor j), represents janitor on map
    string lrepresentation ;

    coord trapContainer[MAX_TRAPS] ; //


    //Build Functions ------------------

      /* Clear Function: Sets elements of array of MAX x MAX size to '\0'.

        Pre: Array of [MAX][MAX] size.

        Post: Elements of array all set to '\0'
      */
      void clearSchool() ;

      /* Assign Function: Uses user-defined size to construct array with B/W boundaries.
        Pre: Statically declared square 2D character array with max size declared and less than MAX size.

        Post: Array values set to:
          'B' if border and not window
          'W' if border and window
          ' ' if inside border
      */
      void assignSchool() ; //Builds basic school grid with B/W boundaries based on assigned size.

      /* Initialize List: Creates a list of all available spaces based on size of map.

        Pre: Dimensions of used map (must be square)

        Post: Update locList with array values
      */
      void initLocList() ; 
      

      
  

} ;

#endif