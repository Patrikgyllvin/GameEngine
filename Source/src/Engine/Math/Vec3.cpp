#include "../../../include/Engine/Math/Vec3.h"

namespace Engine
{
	Vec3::Vec3()
	:
	x( 0 ),
	y( 0 ),
	z( 0 )
	{}

	Vec3::Vec3( float x, float y, float z )
	:
	x( x ),
	y( y ),
	z( z )
	{}

	Vec3::~Vec3(){}

	const std::string Vec3::toString( ) const
	{
		std::ostringstream oStr;
		oStr << x << ", " << y << ", " << z;

		return std::string( oStr.str() );
	}

	float Vec3::dot( const Vec3& otherVec )
	{
		return x * otherVec.getX() + y * otherVec.getY() + z * otherVec.getZ();
	}

	Vec3 Vec3::cross( const Vec3& otherVec )
	{
		float f0 = y * otherVec.getZ( ) - z * otherVec.getY( );
		float f1 = z * otherVec.getX( ) - x * otherVec.getZ( );
		float f2 = x * otherVec.getY( ) - y * otherVec.getX( );

		return Vec3( f0, f1, f2 );
	}

	float Vec3::length()
	{
		return (float)sqrt( dot( *this ) );
	}

	Vec3 Vec3::normalized()
	{
		float len = length();

		if( len != 0 )
		{
			return Vec3( this->x / len, this->y / len, this->z / len );
		}

		return *this;
	}

	void Vec3::setX( float x )
	{
		this->x = x;
	}

	void Vec3::setY( float y )
	{
		this->y = y;
	}

	void Vec3::setZ( float z )
	{
		this->z = z;
	}

	float Vec3::getX() const
	{
		return this->x;
	}

	float Vec3::getY() const
	{
		return this->y;
	}

	float Vec3::getZ() const
	{
		return this->z;
	}

	Vec3 Vec3::operator+( const Vec3& otherVec )
	{
		return Vec3( x + otherVec.getX(), y + otherVec.getY(), z + otherVec.getZ() );
	}

	Vec3 Vec3::operator-( const Vec3& otherVec )
	{
		return Vec3( x - otherVec.getX(), y - otherVec.getY(), z - otherVec.getZ() );
	}

	Vec3 Vec3::operator*( float factor )
	{
		return Vec3( x * factor, y * factor, z * factor );
	}

	Vec3 Vec3::operator/( float denominator )
	{
		return Vec3( x / denominator, y / denominator, z / denominator );
	}

	Vec3& Vec3::operator+=( const Vec3& otherVec )
	{
		this->x += otherVec.getX();
		this->y += otherVec.getY();
		this->z += otherVec.getZ();

		return *this;
	}

	Vec3& Vec3::operator-=( const Vec3& otherVec )
	{
		this->x -= otherVec.getX();
		this->y -= otherVec.getY();
		this->z -= otherVec.getZ();

		return *this;
	}

	Vec3& Vec3::operator*=( float factor )
	{
		this->x *= factor;
		this->y *= factor;
		this->z *= factor;

		return *this;
	}

	Vec3& Vec3::operator/=( float denominator )
	{
		this->x /= denominator;
		this->y /= denominator;
		this->z /= denominator;

		return *this;
	}
}
