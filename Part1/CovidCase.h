#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
using std::ostream;

#include <string>
using std::string;

#include <cmath>


// TODO: your code  goes here
class CovidCase {

private:
    double latitude, longitude;
    string name;
    int age, hoursPositive;
    const double pi = 3.14159265358979323846;
    const int R = 3960;

public:
    CovidCase(double latitudeIn, double longitudeIn, string nameIn, int ageIn, int hoursPositiveIn)
            : latitude(latitudeIn), longitude(longitudeIn), name(nameIn), age(ageIn),
              hoursPositive(hoursPositiveIn) {}

    double latRad = latitude *pi/180;
    double lonRad = longitude *pi/180;

    const double getLatitude() const {
        return latitude;
    }
    const double getLatRad() const {
        return latitude *pi/180;
    }

    const double getLongitude() const {
        return longitude;
    }
    const double getLonRad() const {
        return longitude *pi/180;
    }

    const string getName() const {
        return name;
    }

    const int getAge() const {
        return age;
    }

    const int getHoursPositive() const {
        return hoursPositive;
    }


    double distanceTo(const CovidCase & other) {
        double distLong = other.getLonRad() - getLonRad();
        double distLat = other.getLatRad() - getLatRad();

        double a = pow((sin(distLat/2)), 2) + cos(getLatRad()) * cos(other.getLatRad())
                * pow((sin(distLong/2)), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        double distance = R * c;

        return distance;

    }

};

ostream & operator<<(ostream & o, const CovidCase & c){
        o << "{" << c.getLatitude() << ", " << c.getLongitude() << ", " << "\"" <<  c.getName() << "\"" << ", "
        << c.getAge()<< ", " << c.getHoursPositive() << "}";
        return o;

    }








// don't write any code below this line

#endif

