#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"
#include <utility>
using std::pair;
#include <cmath>
#include <stack>
#include <list>
#include <map>
#include <iostream>
using std::cout;
using std::endl;

using std::list;
using std::stack;
using std::pow;

class TimeAndCaseData {
private:
    int time;
    int cases;
public:
    TimeAndCaseData(int timeIn, int casesIn)
            :time(timeIn), cases(casesIn){};
    int getTime() const{
        // Return the time of each case.
        return time;
    }
    int getNumberOfCases() const {
        // Return the number of cases.
        return cases;
    }
    void setNumberOfCases(int newCases) {
        cases = newCases;
    }
};


class CovidCaseMap {
private:
    vector<CovidCase> ccVector;
public:

    void addCase(const CovidCase &cc) {
        ccVector.push_back(cc);
    }

    vector<TimeAndCaseData> getCasesOverTime(int hours) {
        // We create two lists to store both the active cases and when they will be cured.
        list<TimeAndCaseData> casesActive{};
        list<TimeAndCaseData> casesCured{};
        // We also make a vector to store the values taken from both lists.
        vector<TimeAndCaseData> resultVector;
        // We create a 0 value to store in the result vector as indicated in the tests.
        TimeAndCaseData t0(0,0);
        resultVector.emplace_back(t0);
        // Make a variable to store the number of cases.
        int cases = 0;

        // We fill the lists with the initial values to start working on them.
        TimeAndCaseData patient1(ccVector[0].getTime(), cases);
        casesActive.emplace_back(patient1);
        TimeAndCaseData patient1Cured(patient1.getTime() + hours, cases);
        casesCured.emplace_back(patient1Cured);



            for(int i = 1; i <= 2 * ccVector.size()-2 ; ++i ) {
                if(!casesActive.empty()){
                auto casesActiveFront = casesActive.front();
                auto casesCuredFront = casesCured.front();


                // Check which of the lists first item comes first.
                cout << "Cases list front " << casesActiveFront.getTime() << "\n";
                cout << "Cured list front " << casesCured.front().getTime() << "\n";

                if (casesActiveFront.getTime() != 0) {

                    if (casesActive.front().getTime() < casesCured.front().getTime()) {
                        // If the one in the active cases is smaller (It comes first in cronological order).
                        // Increase the number of cases.
                        ++cases;
                        //Set the number of cases for the element on the frontal part
                        // of the list to the number stored in the cases variable
                        casesActive.front().setNumberOfCases(cases);
                        // Add the case to the result vector.
                        resultVector.push_back(casesActive.front());
                        // Erase the case from the cases list.
                        casesActive.pop_front();

                        // Add the next case and cured case to the lists.
                        casesActive.emplace_back(ccVector[i].getTime(), 0);
                        casesCured.emplace_back(ccVector[i].getTime() + hours, 0);

                    } else {
                        // Else decrease the number of cases.
                        --cases;

                        // Same as the other part but using the curedCases list.
                        casesCured.front().setNumberOfCases(cases);
                        resultVector.push_back(casesCured.front());
                        casesCured.pop_front();
                    }
                }
            }
            }
        if (!casesCured.empty()){
            for(auto el: casesCured){
                --cases;

                el.setNumberOfCases(cases);
                resultVector.push_back(el);
            }
        }
        return resultVector;

    }

   double supportVisitGreedyTSP(double lat, double lon,int time,  int hours ) {
        // As the distanceTo method uses two CovidCases object,
        // I make a CovidCase object with the lat and lon values provided as parameters
        CovidCase position(lat, lon,"StartPoint", 1, 1 );

        // Copy the cases vector in order to manipulate it later on.
        vector<CovidCase> casesCopy;
       for (const auto & el : ccVector) {
           if (el.getTime() + hours >= time && el.getTime() <= time) {
               casesCopy.push_back(el);
           }
       }

       // The final distance to be returned.
       double totalDis = 0;

       // Search while the cases vector copy is not empty.
       while(!casesCopy.empty()) {
           pair<int, double> minDis(0, -1);
           // Find the min distance from the position given and the CovidCase instance where it goes.
           for (int i = 0; i < casesCopy.size(); ++i) {
               if (i == 0 || position.distanceTo(casesCopy[i]) < minDis.second) {
                   minDis.first = i;
                   minDis.second = position.distanceTo(casesCopy[i]);
               }
           }
           totalDis += minDis.second;
           position = casesCopy[minDis.first];
           // Erase the CovidCase instance of the point reached from the vector in order not to visit it again.
           casesCopy.erase(casesCopy.begin() + minDis.first);
       }
       // Add the distance from the last case visited to the starting point to complete the circuit.
       totalDis += position.distanceTo(CovidCase(lat, lon,"ReturnPoint", 1, 1 ));
       return  totalDis;
   }


};


// don't write any code below this line

#endif

