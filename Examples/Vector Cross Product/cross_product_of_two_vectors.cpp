#include "geo_vector.h" //!Including geo_vector header

#include<iostream>

//Headers from boost libraries

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/io.hpp>

#include <boost/geometry.hpp>

using namespace boost::units;
using namespace boost::units::si;

using namespace boost::geometry::model;
using namespace boost::geometry::cs;

int main() {

    //Defining a 3D point of force type

    typedef point< quantity<force>, 3 , cartesian >  Point3D; 

    //Initialising Two points of force type 

    Point3D X(5 * newton, 3 * newton, 1 * newton);

    Point3D Y(2 * newton, 4 * newton, 1 * newton);

    //initialising two position vectors of force type to above points

    geo_vector<force> Fa(X);

    geo_vector<force> Fb(Y);

    //creating a zero vector of force type

    geo_vector<force> F_resultant;

    F_resultant = Fa.cross_prod_with(Fb);

    //!Fa.cross_prod_with(Fb) returns the resultant cross product vector

    std::cout<<"Fa : "<< Fa <<std::endl
             <<"Fb : "<< Fb <<std::endl

             <<"\nF_resultant : "<< F_resultant <<std::endl;

    return 0;
}


/* *  * OUTPUT * * * * * * * * * * *

Fa : (5 N)i + (3 N)j + (1 N)k
Fb : (2 N)i + (4 N)j + (1 N)k

F_resultant : (-1 N)i + (-3 N)j + (14 N)k



* * * * * * * * * * * * * * * * 
*/






