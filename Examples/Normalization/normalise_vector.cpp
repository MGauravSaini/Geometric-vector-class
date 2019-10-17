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

int main(void) {

	//Defining a 3D point of displacement type

	typedef point< quantity<length>, 3 , cartesian >  Point3D; 

	//Creating Two P and Q points in 3D space 

	Point3D P(1 * meter, 9 * meter, 6 * meter);
	Point3D Q(4 * meter, 5 * meter, 6 * meter);

	//Constructing PQ vector with P as Initial point and Q as Terminal Point

	geo_vector<length> PQ(P,Q);

	std::cout<<"PQ : "<< PQ <<std::endl;

	//Using magnitude function to determine the initial Magnitude of Vector PQ

	std::cout<<"Magnitude of Vector PQ Before Normalisation : "<< PQ.magnitude() <<std::endl;
	
	//Normalising vector PQ using normalize function

	PQ.normalize();

	std::cout<<"Normalized PQ : "<< PQ <<std::endl; //PQ after get normalise

	std::cout<<"Magnitude of Vector PQ After Normalisation : "<< PQ.magnitude() <<std::endl;

  /**********************
   Alternate Way

   geo_vector.h consist of a reset_magnitude() function 
   this function can be used to change the length of a vector to a passed length
   since a unit vector have a length of one unit we use it like this

   PQ.reset_magnitude(1*meter);

  **********************/

	return 0;
}

/* *  * OUTPUT * * * * * * * * * * *

PQ : (3 m)i + (-4 m)j + (0 m)k
Magnitude of Vector PQ Before Normalisation : 5 m
Normalized PQ : (0.6 m)i + (-0.8 m)j + (0 m)k
Magnitude of Vector PQ After Normalisation : 1 m

* * * * * * * * * * * * * * * * 
*/
