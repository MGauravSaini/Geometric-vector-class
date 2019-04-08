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

int main()
{

  //Defining a 3D point of length type

  typedef point< quantity<length>, 3 , cartesian >  Point3D; 

  //Creating Two points of length type 

  Point3D P( 7 * meters , -4 * meters , -6 * meters);
  Point3D Q( 2 * meters , 2 * meters , 10 * meters);

  //creating two position vectors of length type to above points (displacements)

  geo_vector<length> d1(P);

  geo_vector<length> d2(Q);

  //creating a zero vector of length type

  geo_vector<length> Displacement;

  // d2 - d1 returns a resultant displacement vector

  Displacement = d2 - d1;

  std::cout<<"d1 : "<< d1 <<std::endl
           <<"d2 : "<< d2 <<std::endl

           <<"\nDisplacement (d2 - d1) : "<< Displacement <<std::endl;

  return 0;
}


/* *  * OUTPUT * * * * * * * * * * *

d1 : (7 m)i + (-4 m)j + (-6 m)k
d2 : (2 m)i + (2 m)j + (10 m)k

Displacement (d2 - d1) : (-5 m)i + (6 m)j + (16 m)k



* * * * * * * * * * * * * * * * 
*/







