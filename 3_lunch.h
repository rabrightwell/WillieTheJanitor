#ifndef LUNCH_H
#define LUNCH_H

#include <iostream>
#include <string>
#include <list>
#include "_coord.h"
using namespace std ;

class school;

class lunch
{
  private:
    coord location ;
    coord toLocation ;
    bool trapped ; //T if lunch encounters trap, F else

    //Move Functions
      void move() ;

    //Interaction Functions
      void effectMovement(school & mySchool);
      void moveTo_() ;
      void moveToW() ;
      void moveToJ() ;
      void moveToD() ;
      void moveToB() ;
      void moveToT() ;
    

  public:
    //Variables
    char representation ;

    //Constructor
      lunch(char r = 'L') ;

    //Accessor
      inline coord getLocation() {return location ; } ;

    //Assignment
      void initLunch (school & mySchool) ;

    //Move Simulation
      void nextMove(school & mySchool) ;
} ;

#endif