#include "4_drink.h" 
#include "1_school.h"

const float ALCOHOL_FACTOR = 0.01 ;
const float ALCOHOL_BASE = 0.05 ;

const float COFFEE_FACTOR = 0.001 ;
const float COFFEE_BASE = 0.001 ;

/* Constructor
----------------------------------------------------------------------*/
drink::drink()
{
  bool isWhiskey = rand()%2 ;

    if (isWhiskey)
    {
      type = "Whiskey" ;
      effect = rand()%5 * ALCOHOL_FACTOR + ALCOHOL_BASE ;
    }
    else
    {
      type = "Coffee" ;
      effect = -1*rand()%9 * COFFEE_FACTOR - COFFEE_BASE ;
    }
}

/* Public Functions
---------------------------------------------------------------------
*/
  //Initializaiton Functions ---------------------
    void drink::initDrink(school & mySchool)
    {
      list<coord> temp = mySchool.getLocList() ;

      list<coord>::iterator it ;

      it = temp.begin() ;
      advance (it, rand()%temp.size()) ; 
      location = *it ;
      temp.erase(it) ;
      
      mySchool.setLocList(temp) ;

      return ;
    }
      /* Disclaimer: Assistance with Assignment/Erasing http://www.cplusplus.com/reference/list/list/erase/
      */

/* Private Functions
----------------------------------------------------------------------
*/


/* Non-Member
----------------------------------------------------------------------
*/

  //Overloaded Operator
    ostream& operator << (ostream & out, drink myDrink)
    {
      out << "Drink is " << myDrink.getType() << " and will change bac by " << myDrink.getEffect() ;
      return out ;
    }

