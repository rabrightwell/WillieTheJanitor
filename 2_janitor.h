#ifndef JANITOR_H
#define JANITOR_H

#include <iostream>
#include <string>
#include <list>
#include "_coord.h"
using namespace std ;

class school;
class lunch ;
class drink ;

class janitor
{
  private:
    //Variables
      float bac ; //blood alchohol content
      int bruises ; //num of bruises 
      coord location ; //coordinates to be streamed to map
      coord toLocation ; //where Janitor will move to next
      
      //State Bools
      bool defenestrated ; //T if janitor out window, F if not 
      bool drunk ; //T if drunk, F if sober
      bool dead ; //T if dead, F if alive
      bool hungry ; //T if lunch not caught, F if caught
    
    //Movements
      void moveSober(lunch & l) ;
      void moveDrunk() ;

    //Interactions
      void effectMovement(school & mySchool, drink container[]) ;
      void moveTo_() ;
      void moveToW() ;
      void moveToL() ;
      void moveToD(drink container[]) ;
      void moveToB(school & mySchool) ;
      void moveToT() ;

      drink chooseDrink(drink container[]) ;
      

  public :
    //Variables
      char representation ;
      string name ;

    //Constructors
      janitor(string n = "Willie", char r = 'J') ;

    //Accessor
      inline coord getLocation() {return location ;} ;
      bool getHungry() {return hungry ;} ;
      bool getDead() {return dead ;} ;
      bool getDefenestrated() {return defenestrated ;} ;
      inline int getBruises() {return bruises ;} ;
      inline float getBAC() {return bac ;} ;
    //State
    void checkDrunk() ;
    void checkDead() ;

    //Assignment
      void initJanitor(school & mySchool) ;

    //Move Simulation
      void nextMove(school & mySchool, lunch & l, drink drinkContainer[]) ;

    //Friends
    friend ostream& operator<< (ostream& out, janitor j) ;


// a print() function or overloaded insertion operator.
} ;

#endif