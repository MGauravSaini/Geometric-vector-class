
/*
*   geo_vector.cpp
*
*   Created by Gaurav Saini
*
*   Copyright 2019 Gaurav Saini. All rights reserved.
*
*/

#include "geo_vector.h"

#include <iostream>
using namespace boost::units;
using namespace boost::units::si;

namespace bg = boost::geometry;

using namespace bg::model;
using namespace bg::cs;

/*
* Below change_dimension() is a temporary template function
* it is used to make quantities dimensionless from dimension and vice versa
* this fuction is needed because some fuction from boost::geometry 
* are not able to resolve the dimensions of quantities example in cross product
*/

template<typename change_to,typename current_dim>
point<quantity<change_to> , 3 ,cartesian> change_dimension(const point<quantity<current_dim> , 3 ,cartesian> &input_point)
{
	current_dim C;
	change_to   X;

	quantity<current_dim> x = bg::get<0>(input_point);
	quantity<current_dim> y = bg::get<1>(input_point);
	quantity<current_dim> z = bg::get<2>(input_point);

	point<quantity<change_to> , 3 ,cartesian> A( ((x / C)*X) , ((y / C)*X) , ((z / C)*X) );
	return A;
}
   
//Function to initialise the abscissa of point i.e x coordinate

template <typename quant_type>
void geo_vector<quant_type>::set_abscissa(const quantity <quant_type> &init_abscissa) {

	bg::set<0>(p, init_abscissa);
}

template <typename quant_type>
void geo_vector<quant_type>::set_ordinate(const quantity <quant_type> &init_ordinate) {

	bg::set<1>(p, init_ordinate);

}

template <typename quant_type>
void geo_vector<quant_type>::set_applicate(const quantity <quant_type> &init_applicate) { 

	bg::set<2>(p, init_applicate);
}

// This function returns the abscissa(x coordinate) of point

template <typename quant_type>
quantity <quant_type> geo_vector<quant_type>::get_abscissa() const {

	return ( bg::get<0>(p) );
}

template <typename quant_type>
quantity <quant_type> geo_vector<quant_type>::get_ordinate() const {

	return ( bg::get<1>(p) );
}

template <typename quant_type>
quantity <quant_type> geo_vector<quant_type>::get_applicate() const {

	return ( bg::get<2>(p) );
}

 //======================= Constructor section ================

//Default constructor create a zero vector object

template <typename quant_type>
geo_vector<quant_type>::geo_vector() {

	quant_type q_unit;
	set_abscissa(0 * q_unit);
	set_ordinate(0 * q_unit);
	set_applicate(0 * q_unit); 
}

//Copy constructor

template <typename quant_type>
geo_vector<quant_type>::geo_vector(const geo_vector<quant_type> &init_v) {

	set_abscissa(init_v.get_abscissa());
	set_ordinate(init_v.get_ordinate());
	set_applicate(init_v.get_applicate());
}

//Constructor if an object of point type is passed

template <typename quant_type>
geo_vector<quant_type>::geo_vector(Point3D m_point) {

	set_abscissa(bg::get<0>(m_point));
	set_ordinate(bg::get<1>(m_point));
	set_applicate(bg::get<2>(m_point));
}

//Constructing a vector if two points are given

template <typename quant_type>
geo_vector<quant_type>::geo_vector(Point3D initial_point,Point3D terminal_point) {

	set_abscissa(bg::get<0>(terminal_point) - bg::get<0>(initial_point));
	set_ordinate(bg::get<1>(terminal_point) - bg::get<1>(initial_point));
	set_applicate(bg::get<2>(terminal_point) - bg::get<2>(initial_point));
}

//=================   Member function section ========================

 
//Returns the magnitude of calling vector

template <typename quant_type>
quantity <quant_type> geo_vector<quant_type>::magnitude() {

	quant_type q_unit;
	dimensionless d;

	Point3D X(get_abscissa(),get_ordinate(),get_applicate()); //getting points from vector

	typedef point<quantity<dimensionless> , 3 ,cartesian> unitless_point;

	unitless_point origin(0 * d,0 * d,0 * d); //create a dimensionless origin point
    
    /*
    * Since the distance function from boost::geometry is not able to resolve units
    *  we have to make quantities dimensionless before passing to the function
    *  because length*length = area <== boost::geometery.distace() not able to resolve
    *  dimensionless*dimensionless = dimensionless <== boost::geometery.distance()
    *  returns dimensionless quantity which we further rechange to our original dimension
    */

	unitless_point P = change_dimension<dimensionless,quant_type>(X);

	quantity<dimensionless> D =  bg::distance<unitless_point,unitless_point>(origin,P);

	return (D*q_unit); //multiplying to get our unit back

	/* An alternate way is to use root() and pow() functions from boost.units.cmath 
	*                                
	* return ( root<2> ( pow<2>(get_abscissa()) + pow<2>(get_ordinate()) + pow<2>(get_applicate()) ) );
    *
	*/

} 

template <typename quant_type>
void geo_vector<quant_type>::normalize() {

	quantity <quant_type> l = magnitude();
	quant_type q_unit;
	if(l != 0 * q_unit) {

		//Dividing by l make coordinate dimensionless
		//To change them again to original unit I multiply with q_unit
		set_abscissa((get_abscissa() / l) * q_unit); 
		set_ordinate((get_ordinate() / l) * q_unit);
		set_applicate((get_applicate() / l) * q_unit);
	}
}

//Change the magnitude of calling vector to passed magnitude

template <typename quant_type>
void geo_vector<quant_type>::reset_magnitude(quantity <quant_type> new_mag) {

	quantity <quant_type> l = magnitude();
	quant_type q_unit;
	if(l == 0*q_unit) {
		set_abscissa(new_mag);
		set_ordinate(new_mag);
		set_applicate(new_mag);
	}
	else {
		set_abscissa ((get_abscissa() / l) * new_mag);
		set_ordinate ((get_ordinate() / l) * new_mag);
		set_applicate ((get_applicate() / l) * new_mag);
	}
}

//Dot product of two vectors
//Example call: quantity<energy> work = push.dot_prod_with<energy,force,length>(displacement);

template <typename quant_type>
template<typename quant_rtn_type, typename a_unit,typename b_unit>
quantity <quant_rtn_type> geo_vector<quant_type>::dot_prod_with(const geo_vector<b_unit> &b) {

  typedef point<quantity<a_unit>,3,cartesian> Apoint;
  typedef point<quantity<b_unit>,3,cartesian> Bpoint;

  Apoint A(get_abscissa(),get_ordinate(),get_applicate());
  Bpoint B(b.get_abscissa(),b.get_ordinate(),b.get_applicate());

  typedef point<quantity<dimensionless>,3,cartesian> unitless_point;

  /*
   * Again we have to make quanities dimensionless to use boost::geometry::dot_product();
  */

  unitless_point X = change_dimension<dimensionless,a_unit>(A);
  unitless_point Y = change_dimension<dimensionless,b_unit>(B);

  quantity<dimensionless> D = bg::dot_product<unitless_point,unitless_point>(X,Y);

  //changing to original dimension 
  quant_rtn_type qrt;

  return (D*qrt);
}

//cross product of two vectors
//Example call: geo_vector<force> Resultant = Force1.cross_prod_with(Force2);

template <typename quant_type>
geo_vector<quant_type> geo_vector<quant_type>::cross_prod_with(const geo_vector<quant_type> &b) {

	Point3D X(get_abscissa(),get_ordinate(),get_applicate());
	Point3D Y(b.get_abscissa(),b.get_ordinate(),b.get_applicate());

	typedef point<quantity<dimensionless> ,3, cartesian> unitless_point;

    //Making quantities dimensionless

	unitless_point A = change_dimension<dimensionless,quant_type>(X);
	unitless_point B = change_dimension<dimensionless,quant_type>(Y);
    
    //Storing returning point in a dimensionless point c; 

	unitless_point c = bg::cross_product<unitless_point,unitless_point,unitless_point>(A,B);
    
    //creating point C by changing dimension of c to original

	Point3D C = change_dimension<quant_type,dimensionless>(c);

	geo_vector<quant_type> result(C); //using geo_vector constructure 

	return result;
}



   //======================= Angle Handling subsection =======================  
                             
                                 /* Coming soon */

   //===================    Operator section section   ==========================


template <typename quant_type>
geo_vector<quant_type> geo_vector<quant_type>::operator+(const geo_vector<quant_type> &a) const {

	Point3D P(get_abscissa(),get_ordinate(),get_applicate());
	Point3D Q(a.get_abscissa(),a.get_ordinate(),a.get_applicate());
     
    /* boost::geometry::add_point() does not erase dimension conflict
    *  because length+length = length
    *  so we can call add_point without modifying dimensions
   */
	bg::add_point<Point3D,Point3D>(P,Q); //add_point changes P point

	geo_vector<quant_type> result(P);

	return result;

	/*
	*An alternate procedure is commented below in two lines of code.
	*i.e without using boost::geometry::add_point() function
	*
	*result.set_abscissa( get_abscissa() + a.get_abscissa() );
	*result.set_ordinate( get_ordinate() + a.get_ordinate() );
	*
	*/
}

template <typename quant_type>
geo_vector<quant_type> geo_vector<quant_type>::operator-(const geo_vector<quant_type> &a) const {

	Point3D P(get_abscissa(),get_ordinate(),get_applicate());
	Point3D Q(a.get_abscissa(),a.get_ordinate(),a.get_applicate());

	bg::subtract_point<Point3D,Point3D>(P,Q);

	geo_vector<quant_type> result(P);
	return result;

	/* 
	 * An alternate procedure is commented below in two lines of code.
	 * i.e without using boost::geometry::subtract_point() function
	 *
	 *result.set_abscissa( get_abscissa() - a.get_abscissa() );
	 *result.set_ordinate( get_ordinate() - a.get_ordinate() );
	 *
	 */
}

//for product of a geo_vector with a scalar (f*5)

template <typename quant_type>
geo_vector<quant_type> geo_vector<quant_type>::operator*(const double &scalar) const {

	geo_vector<quant_type> result;
	result.set_abscissa( scalar * get_abscissa() );
	result.set_ordinate( scalar * get_ordinate() );
	result.set_applicate( scalar * get_applicate() );
	return result;
}

//for divide of a geo_vector with scalar

template <typename quant_type>
geo_vector<quant_type> geo_vector<quant_type>::operator/(const double &scalar) const {

	if(scalar!=0) {
		
		geo_vector<quant_type> result;
		result.set_abscissa( get_abscissa() / scalar );
		result.set_ordinate( get_ordinate() / scalar );
		result.set_applicate( get_applicate() / scalar );
		return result;
	}
	else 
		return *this;
}

template <typename quant_type>
void geo_vector<quant_type>::operator=(const geo_vector<quant_type> &a) {

	set_abscissa(a.get_abscissa());
	set_ordinate(a.get_ordinate());
	set_applicate(a.get_applicate());
}

template <typename quant_type>
void geo_vector<quant_type>::operator+=(const geo_vector<quant_type> &a) {

   	set_abscissa( get_abscissa() + a.get_abscissa() );
   	set_ordinate( get_ordinate() + a.get_ordinate() );
    set_applicate( get_applicate() + a.get_applicate() );
}

template <typename quant_type>
void geo_vector<quant_type>::operator-=(const geo_vector<quant_type> &a) {

   	set_abscissa( get_abscissa() - a.get_abscissa() );
   	set_ordinate( get_ordinate() - a.get_ordinate() );
    set_applicate( get_applicate() - a.get_applicate() );
}

template <typename quant_type>
bool geo_vector<quant_type>::operator==(const geo_vector<quant_type>& v) const {

	return ( get_abscissa() == v.get_abscissa() && get_ordinate() == v.get_ordinate() && get_applicate() == v.get_applicate() );
}

template<typename quant_type>
std::ostream &operator <<(std::ostream &os,geo_vector<quant_type> v)
{
  os<<"("<<v.get_abscissa()<<")i + ("<<v.get_ordinate()<<")j + ("<<v.get_applicate()<<")k";
  return os;
}



