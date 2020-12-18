#ifndef DRINK_H
#define DRINK_H

#include <iostream>
#include <string>
#include <list>
#include "_coord.h"
using namespace std ;

class school;

class drink
{
  private:
    //Variables -------------------
      string type ; //whiskey or coffee
      float effect ; //added to bac
      coord location ;

  public:
    //Variables
      static int MAX_DRINKS ; 

    //Constructors --------------------
      /*Default Constructor: Constructs drink with random type allocation and effect.
        Post: Drink of either type "whiskey" or "coffee." Whiskey will have effect between range [0.05, 0.10] and coffee will have effect between range [-0.001, -0.010].
      */
      drink() ;

      //Accessor ------------
      inline coord getLocation() {return location ;} ;

      /*Initializer
      */
      void initDrink(school & mySchool) ;
      

    //Accessors ----------------
      inline string getType() {return type;} ;
      inline float getEffect() {return effect;} ;


  
} ;

//Non-Member Functions---------------------------------------------

  //Overloaded Operators
    /* Drink << Overload: Allows output of drink type and effect value.
      Pre: Requires input of drink with both type and effect.

      Post: Must be of type returnable to ostream.
    */
    ostream& operator<< (ostream & out, drink myDrink) ;
    

#endif