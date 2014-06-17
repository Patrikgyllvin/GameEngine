#include "Vector3f.h"

namespace Engine
{
	Vector3f::Vector3f()
	:
	x( 0 ),
	y( 0 ),
	z( 0 )
	{}

	Vector3f::Vector3f( float x, float y, float z )
	:
	x( x ),
	y( y ),
	z( z )
	{}

	Vector3f::~Vector3f(){}

	std::string Vector3f::toString( )
	{
		//return "(" + x + " " + y + " " + z + ")";
	}

	float Vector3f::dot( const Vector3f& otherVec )
	{
		return x * otherVec.getX() + y * otherVec.getY() + z * otherVec.getZ();
	}

	Vector3f Vector3f::cross( const Vector3f& otherVec )
	{
		float f0 = y * otherVec.getZ( ) - z * otherVec.getY( );
		float f1 = z * otherVec.getX( ) - x * otherVec.getZ( );
		float f2 = x * otherVec.getY( ) - y * otherVec.getX( );

		return Vector3f( f0, f1, f2 );
	}

	float Vector3f::length()
	{
		return (float)sqrt( dot( *this ) );
	}

	void Vector3f::normalize()
	{
		float len = length();

		if( len != 0 )
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}

	void Vector3f::setX( float x )
	{
		this->x = x;
	}

	void Vector3f::setY( float y )
	{
		this->y = y;
	}

	void Vector3f::setZ( float z )
	{
		this->z = z;
	}

	float Vector3f::getX() const
	{
		return this->x;
	}
	
	float Vector3f::getY() const
	{
		return this->y;
	}

	float Vector3f::getZ() const
	{
		return this->z;
	}

	Vector3f Vector3f::operator+( const Vector3f& otherVec )
	{
		return Vector3f( x + otherVec.getX(), y + otherVec.getY(), z + otherVec.getZ() );
	}

	Vector3f Vector3f::operator-( const Vector3f& otherVec )
	{
		return Vector3f( x - otherVec.getX(), y - otherVec.getY(), z - otherVec.getZ() );
	}

	Vector3f Vector3f::operator*( float factor )
	{

	}
	Vector3f Vector3f::operator/( float denominator ){}

	Vector3f& Vector3f::operator+=( const Vector3f& otherVec ){}
	Vector3f& Vector3f::operator-=( const Vector3f& otherVec ){}
	Vector3f& Vector3f::operator*=( float factor ){}
	Vector3f& Vector3f::operator/=( float denominator ){}
}