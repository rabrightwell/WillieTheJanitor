#include <iostream>
#include <fstream>
#include <unistd.h>

#include "1_school.h"
#include "2_janitor.h"
#include "3_lunch.h"
#include "4_drink.h"

using namespace std ;

int drink::MAX_DRINKS = 20 ;

int main() {

  srand(time(NULL)) ;
  //Input Variables (Stream In) 
    
    int numDays ;
    int size ;
    int numDrinks ;
    int numTraps ;
    int freqWindows ; 

  //Output Variables (Stream Out)
    //Output Stats per Game
    int didDefenestrate ;
    int didSucceed ;
    int didDie ;
    int bruises ;
    float bac ;

    //Output Stats Running Total
    int totDefenestrations = 0 ;
    int totSuccesses = 0 ;
    int totDeaths = 0 ;
    int totBruises = 0 ;
    float totBAC = 0 ;

    //Output Percentages
    float perDefenestrations ;
    float perSuccesses ;
    float perDeaths ;

    //Output Averages
    float avgBruises ;
    float avgBAC ;

  //Input File stream
    ifstream in ;
    ofstream out ;
    string test_run_name = "FINAL PROJECT RUN" ;

    in.open("inputs.dat") ;
    in >> numDays ;
    in >> size ;
    in >> numDrinks ;
    in >> numTraps ;
    in >> freqWindows ;

    in.close() ;

//Output File Setup
  out.open("outputs.dat") ;
  out << "Test File Run Name: " << test_run_name << "\n" << endl ;
  out.close() ;

  cout << "A simulation will now be run for " << numDays << " days in a school of size " << size << "x" << size << " with " << numDrinks << " drinks, " << numTraps << " traps, and windows every " << freqWindows << " blocks." << endl << endl ;
    
  //loop on number of days
    int day = 0 ;
    do
    {
      //Build Stage
        //Declarations
          //School/Trap Declaration
          school mySchool(size, freqWindows, numDrinks, numTraps) ;

          //Janitor Declaration
          janitor myJanitor("Willie",'J') ;

          //Lunch Declaration
          lunch moldyBoi('L') ;

          //Drink Declaration
          drink drinkContainer[drink::MAX_DRINKS] ;
          for (int i=0; i<numDrinks; i++)
          {
            drinkContainer[i] = drink() ;
          }
        //Placement of Pieces ------
          //Janitor Placement
          myJanitor.initJanitor(mySchool) ;
          mySchool.place(myJanitor) ;

          //Lunch Placement
          moldyBoi.initLunch(mySchool) ;
          mySchool.place(moldyBoi) ;
        
          //Drink Placement
          for(int i = 0; i<mySchool.getNum_Drinks(); i++)
          {
            drinkContainer[i].initDrink(mySchool) ;
            mySchool.place(drinkContainer[i]) ;
          }
        
          //Trap Placement
          mySchool.initTraps() ;
          mySchool.placeTraps() ;

          cout << "Day " << day+1 << " Setup:\n" << mySchool ;

      do
      {
        //Lunch Movement
        moldyBoi.nextMove(mySchool) ;
        //Janitor Movement
        myJanitor.nextMove(mySchool, moldyBoi, drinkContainer) ;
        if (day == 0)
        {
          cout << mySchool ;
          cout << myJanitor << endl ;
          usleep(1000000) ;
        }

        
      }
      while(!(myJanitor.getDead()) && !(myJanitor.getDefenestrated()) && myJanitor.getHungry()) ;
    
      //Stat Updates For Day
        didDefenestrate = (myJanitor.getDefenestrated() ? 1 : 0) ;
        didDie = (myJanitor.getDead() ? 1 : 0) ;
        didSucceed = (myJanitor.getHungry() ? 0 : 1) ;
        bruises = myJanitor.getBruises() ;
        bac = myJanitor.getBAC() ;

        totDefenestrations += didDefenestrate ;
        totSuccesses += didSucceed ;
        totDeaths += didDie ;
        totBruises += bruises ;
        totBAC += bac ;
      
      //Output Stats For Day
      out.open("outputs.dat", ios::app) ;
      out << "For Day " << day+1 << endl ;
      out << "\tJanitor Defenestrations: " << didDefenestrate << endl ;
      out << "\tDeaths: " << didDie << endl ;
      out << "\tCaptured Lunches: " << didSucceed << endl ;
      out << "\tNum Bruises: " << bruises << endl ;
      out << "\tEnd BAC: " << bac << "\n" << endl ;
      out.close() ;

      day++ ;
    
    } while (day<numDays) ;
  
  //Stat Averages
    perDefenestrations = totDefenestrations / numDays ;
    perSuccesses = totSuccesses / numDays ;
    perDeaths = totDeaths / numDays ;

    avgBruises = totBruises / numDays ;
    avgBAC = totBAC / numDays ;

  //Output Final Statistics
    out.open("outputs.dat", ios::app) ;
    out << "Game Statistics:" << endl ;
    out << "\tTotal Number of Days: " << numDays << endl ;
    out << "\n\tPercent of Games Ending w/ Defenestration: " << perDefenestrations << endl ;
    out << "\tPercent of Games Ending w/ Death: " << perDeaths << endl ;
    out << "\tPercent of Games Ending w/ Captured Lunch " << perSuccesses << endl ;
    out << "\n\tAverage Number of Bruises: " << avgBruises << endl ;
    out << "\n\tAverage Final BAC: " << avgBAC << endl ;
    out << "\nThanks for playing, and be safe out there!" ;


  return 0 ;

}