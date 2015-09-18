#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "Engine/Math/Vec2.h"
#else
#include "Vec2.h"
#endif

namespace Engine
{
	Vec2::Vec2()
	:
	x( 0 ),
	y( 0 )
	{}

	Vec2::Vec2( float x, float y )
	:
	x( x ),
	y( y )
	{}

	Vec2::~Vec2()
	{}

	const std::string Vec2::toString() const
	{
		std::ostringstream oStr;
		oStr << x << ", " << y;

		return std::string( oStr.str() );
	}

	float Vec2::dot( const Vec2& otherVec )
	{
		return this->x * otherVec.getX() + this->y * otherVec.getY();
	}

	float Vec2::length()
	{
		return (float)sqrt( dot( *this ) );
	}

	Vec2 Vec2::normalized()
	{
		float len = length();

		if( len != 0 )
		{
			return Vec2( this->x / len, this->y / len );
		}

		return *this;
	}

	void Vec2::setX( float x )
	{
		this->x = x;
	}

	void Vec2::setY( float y )
	{
		this->y = y;
	}

	float Vec2::getX() const
	{
		return this->x;
	}

	float Vec2::getY() const
	{
		return this->y;
	}

	Vec2 Vec2::operator+( const Vec2& otherVec )
	{
		return Vec2( this->x + otherVec.getX(), this->y + otherVec.getY() );
	}

	Vec2 Vec2::operator+( float f )
	{
		return Vec2( this->x + f, this->y + f );
	}

	Vec2 Vec2::operator-( const Vec2& otherVec )
	{
		return Vec2( this->x - otherVec.getX(), this->y - otherVec.getY() );
	}

	Vec2 Vec2::operator-( float f )
	{
		return Vec2( this->x - f, this->y - f );
	}

	//Vec2 Vec2::operator*( const Vec2& otherVec ) {}
	Vec2 Vec2::operator*( float factor )
	{
		return Vec2( this->x * factor, this->y * factor );
	}

	//Vec2 operator/( const Vec2& otherVec );
	Vec2 Vec2::operator/( float denominator )
	{
		return Vec2();
	}

	Vec2& Vec2::operator+=( const Vec2& otherVec )
	{
		this->x += otherVec.getX();
		this->y += otherVec.getY();

		return *this;
	}

	Vec2& Vec2::operator-=( const Vec2& otherVec )
	{
		this->x -= otherVec.getX();
		this->y -= otherVec.getY();

		return *this;
	}

	Vec2& Vec2::operator*=( const Vec2& otherVec )
	{
		this->x *= otherVec.getX();
		this->y *= otherVec.getY();

		return *this;
	}

	Vec2& Vec2::operator*=( float factor )
	{
		this->x *= factor;
		this->y *= factor;

		return *this;
	}
}