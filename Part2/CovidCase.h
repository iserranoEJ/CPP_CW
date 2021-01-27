#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
using std::ostream;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
#include<vector>
using std::vector;

#include <cmath>

class CovidCase {

private:
    double latitude, longitude;
    string name;
    int age, hoursPositive;
    constexpr static const double pi = 3.14159265358979323846;
    static const int R = 3960;

public:
    CovidCase(double latitudeIn, double longitudeIn, string nameIn, int ageIn, int hoursPositiveIn)
            : latitude(latitudeIn), longitude(longitudeIn), name(nameIn), age(ageIn),
              hoursPositive(hoursPositiveIn) {}

    CovidCase(const string& input){
       // Split the string into pieces.
       std::stringstream ss(input);

       string splitStr;

       vector <string> v;

       // Push each splitted part of the string to a vector.
       while (ss >> splitStr) {
           v.push_back(splitStr);
       }

       // Assign each value inside the vector to its corresponding member variable.
       latitude = stod(v[0]);
       longitude = stod(v[1]);
       name = v[2].substr(1,v[2].size()-3);
       age = (int)stod(v[3]);
       hoursPositive = (int)stod(v[4]);
    }

    // Getters for each member vaiable

    double getLatitude() const {
        return latitude;
    }
    // Version of the latitude getter that returns the value in radians.
    double getLatRad() const {
        return latitude *pi/180;
    }

    double getLongitude() const {
        return longitude;
    }
    // Version of the longitude getter that returns the value in radians.

    double getLonRad() const {
        return longitude *pi/180;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

   int getTime() const {
        return hoursPositive;
    }

    //Calculate distance from one case to another.
    double distanceTo(const CovidCase & other) const {
        double distLong = other.getLonRad() - getLonRad();
        double distLat = other.getLatRad() - getLatRad();

        double a = pow((sin(distLat/2)), 2) + cos(getLatRad()) * cos(other.getLatRad())
                                              * pow((sin(distLong/2)), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        double distance = R * c;

        return distance;

    }
    bool operator==( const  CovidCase & c) const{
    //Implementation of the equals operator inside the class scope (using member variables)
        if(latitude == c.latitude && longitude == c.longitude && age == c.age && hoursPositive == c.hoursPositive){
            return true;
        }
        return false;
    }

};

ostream & operator<<(ostream & o, const CovidCase & c){
    //Implementation of the put operator outside the class scope (using getters)
    o << "{" << c.getLatitude() << ", " << c.getLongitude() << ", " << "\"" <<  c.getName() << "\"" << ", "
      << c.getAge()<< ", " << c.getTime() << "}";
    return o;



}








// don't write any code below this line

#endif


