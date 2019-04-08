/*
*   geo_vector.h
*
*   Created by Gaurav Saini - 2019.
*
*   Copyright 2019 Gaurav Saini. All rights reserved.
*
*/

#ifndef _GEO_VECTOR_
#define _GEO_VECTOR_

#include <iostream>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/io.hpp>

#include <boost/geometry.hpp>

using namespace boost::units;
using namespace boost::units::si;


using namespace boost::geometry::model;
using namespace boost::geometry::cs;

/*
* Below change_dimension() is a temporary template function
* it is used to make quantities dimensionless from dimension and vice versa
* this fuction is needed because some fuction from boost::geometry 
* are not able to resolve the dimensions of quantities example in cross product
*/

template<typename change_to,typename current_dim>
point<quantity<change_to> , 3 ,cartesian> change_dimension(const point<quantity<current_dim> , 3 ,cartesian> &input_point);


template <typename quant_type>
class geo_vector {

private: 
    
   typedef point<quantity <quant_type>, 3, cartesian> Point3D; 

   Point3D p; //This class create a position vector of this point 
   

   void set_abscissa(const quantity <quant_type> &init_abscissa);  //Function to initialise the abscissa of point
   
   void set_ordinate(const quantity <quant_type> &init_ordinate);  //Similaraly for y coordinate

   void set_applicate(const quantity <quant_type> &init_applicate); //for z coordinate

public:

   quantity <quant_type> get_abscissa() const;  // This function returns the abscissa of point

   quantity <quant_type> get_ordinate() const;  // Returns y coordinate

   quantity <quant_type> get_applicate() const; //Return z coordinate

   
  //======================= Constructor section ================


   geo_vector();         //Default constructor create a zero vector object
   
   geo_vector(const geo_vector<quant_type> &init_v);   //Copy constructor
   
   geo_vector(Point3D m_point);     //Constructor if a object of point type is passed
   
   geo_vector(Point3D initial_point,Point3D terminal_point);//Constructing a vector if two points are passed 

   
  //=================   Member function section =============================
 
   quantity <quant_type> magnitude(); //Returns the magnitude of calling vector
   
   void normalize(); //Normalize(changed to unit vector) the calling vector
   
   void reset_magnitude(quantity <quant_type> new_mag); //Change the magnitude of calling vector to passed magnitude
    
    //Return the quantity getting by dot product of two passed vector
    
    /*template argument 
      1. type of quantity that a particular dot product is return e.g energy
      2. type of quantity that calling vector have e.g force 
      3. type of quantity that passed vector have e.g quant_type 
      Example call:- work = push.dot_prod_with<energy,force,quant_type>(displacement);
    */
   
	template<typename quant_rtn_type, typename a_unit,typename b_unit>
	quantity <quant_rtn_type> dot_prod_with(const geo_vector<b_unit> &b);

   //Return vector getting by cross product of two passed vector

   geo_vector<quant_type> cross_prod_with(const geo_vector<quant_type> &b); 

   
   //======================= Angle Handling subsection =======================  
   
                                 /* Coming soon */

   //====================   Operators overloading section section   ============



   geo_vector<quant_type> operator+(const geo_vector<quant_type> &a) const;
   
   geo_vector<quant_type> operator-(const geo_vector<quant_type> &a) const;

   //For product of a vector with a scalar e.g (v*5)
   geo_vector<quant_type> operator*(const double &scalar) const; 

   //For divide a vector by a scalar e.g (v/5)
   geo_vector<quant_type> operator/(const double &scalar) const;

   void operator=(const geo_vector<quant_type> &a);

   void operator+=(const geo_vector<quant_type> &a);
   
   void operator-=(const geo_vector<quant_type> &a);

   bool operator==(const geo_vector<quant_type>& v) const;
   
};

//overloading << operator for geo_vector

template<typename quant_type>
std::ostream &operator <<(std::ostream &os,geo_vector<quant_type> v);

#endif



   