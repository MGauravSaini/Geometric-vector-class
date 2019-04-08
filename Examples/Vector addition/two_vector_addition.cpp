#include "geo_vector.h"

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

  //Creating Two points of force type 

  Point3D P( 3 * newton , 2 * newton , 4 * newton);
  Point3D Q( 5 * newton , 4 * newton , -3 * newton);

  //creating two position vectors of force type to above points 

  geo_vector<force> f1(P);

  geo_vector<force> f2(Q);

  //creating a zero vector of force type

  geo_vector<force> Resultant;

  // f1 + f2 returns a resultant addition vector

  Resultant = f1 + f2;

  std::cout<<"f1 : "<< f1 <<std::endl
           <<"f2 : "<< f2 <<std::endl

           <<"\nResultant : "<< Resultant<<std::endl;

  return 0;
}


/* *  * OUTPUT * * * * * * * * * * *

f1 : (3 N)i + (2 N)j + (4 N)k
f2 : (5 N)i + (4 N)j + (-3 N)k

Resultant : (8 N)i + (6 N)j + (1 N)k


* * * * * * * * * * * * * * * * 
*/







