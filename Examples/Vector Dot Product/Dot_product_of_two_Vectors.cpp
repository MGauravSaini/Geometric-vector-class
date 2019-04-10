#include "geo_vector.h" //!Including geo_vector header

#include<iostream>

//!Headers from boost libraries

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/io.hpp>

#include <boost/geometry.hpp>

using namespace boost::units;
using namespace boost::units::si;

using namespace boost::geometry::model;
using namespace boost::geometry::cs;

int main() {

    //Defining a 3D point of force type and another of length type

    typedef point< quantity<force>, 3 , cartesian >  force_point3D;

    typedef point< quantity<length>, 3 , cartesian >  displacement_point3D;

    //Initialising a points of force type 

    force_point3D   force_pos(5 * newton, 3 * newton, 1 * newton);

    //initialising a position vectors of force type to above points

    geo_vector<force> Applied_force(force_pos);

    //Initialising a points of length type

    displacement_point3D   dis_pos(2 * meter, 4 * meter, 1 * meter);

    //A position vector to dis_pos point

    geo_vector<length> Displacement_occur(dis_pos);

    //!As we know that the result of the dot of force and displacement is a scalar and it is energy
    //!So it is better to define work done as

    //Declaring Work done quantity of energy type

      quantity<energy> Work_done;

    /*
    *  Now the dot_prod_with is a template function that require
    *  the return type 'quantity type', the calling object quantity type and passed object quantity type
    *   
    */
    
    Work_done = Applied_force.dot_prod_with<energy, force, length >(Displacement_occur);

    std::cout<<" Applied_force      : "<< Applied_force <<std::endl
             <<" Displacement_occur : "<< Displacement_occur <<std::endl

             <<" Work done          : "<< Work_done <<std::endl;

    return 0;
}


/* *  * OUTPUT * * * * * * * * * * *

Applied_force      : (5 N)i + (3 N)j + (1 N)k
Displacement_occur : (2 m)i + (4 m)j + (1 m)k
Work done          : 23 J

* * * * * * * * * * * * * * * * 
*/






