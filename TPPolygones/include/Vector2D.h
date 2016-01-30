/*************************************************************************
                           Vector2D  -  description
                             -------------------
    début                : 13 Janvier 2016
    copyright            : (C) 2016 par Quentin "Johnny" Guye et Lucas Ono
*************************************************************************/

//---------- Interface de la classe <Vector2D> (fichier Vector2D.h) ------
#if ! defined ( VECTOR2D_H )
#define VECTOR2D_H


//------------------------------------------------------------------ Types
#include <cmath>
#include <iostream>
#include <sstream>

#define PI 3.1415927
//------------------------------------------------------------------------
///This class is a point.
//------------------------------------------------------------------------

class Vector2D
{
//----------------------------------------------------------------- PUBLIC

public:
//---------------------------------------------------- Méthodes publiques

/* ==== Surcharges ==== */

	Vector2D  		operator+(const Vector2D& other) const;
	Vector2D        operator-(const Vector2D& other) const;
	Vector2D        operator-() const;
    Vector2D        operator*(const double num) const;
	Vector2D        operator/(const double num) const;
	double 			operator*(const Vector2D& other) const;

	Vector2D&       operator=(const Vector2D& other);

	Vector2D&       operator+=(const Vector2D& other);
	Vector2D&       operator-=(const Vector2D& other);
	Vector2D&       operator*=(double num);
	Vector2D&       operator/=(double num);

	bool            operator==(const Vector2D& other) const;
	bool            operator!=(const Vector2D& other) const;

	Vector2D& 		normalize();
	double 			scalarProduct(const Vector2D & other) const;
/* ==== Methods ==== */

	static double 	angle(Vector2D const &vec1, Vector2D const &vec2);
	static double 	length(Vector2D const &vec2D);
	//static const Vector2D Zero = Vector2D(0,0);

	double length() const;
	std::string toString() const;

/* ==== Getters ==== */

	/// \brief Get the map of nodes
	/// @return : the m_nodesMap
	double GetX() const;
	double GetY() const;

/* ==== Constructors === */

	/**
	*** \brief Create a new Vector2D
	*** @param x : the x coordinate of the point
	*** @param y : the y coordinate of the point
	**/
	Vector2D (double const x = 0, double const y = 0);

	/**
	*** \brief Create a new Vector2D
	*** @param x : the x coordinate of the point
	*** @param y : the y coordinate of the point
	**/
	Vector2D(int const x, int const y);

	/**
	*** \brief Create a copy of the point
	*** @param point : the point to copy
	**/
	Vector2D(Vector2D const &vector2D);

	///Destroy the new Vector2D
	virtual ~Vector2D ( );

protected:
//------------------------------------------------------ Protected methods
//------------------------------------------------------------------ PRIVE

	double x;
	double y;

};


std::ostream &operator<<(std::ostream &flux, Vector2D const& point);
//----------------------------------------- Types dépendants de <Vector2D>

#endif // VECTOR2D_H
