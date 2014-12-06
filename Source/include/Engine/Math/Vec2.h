#ifndef VEC2_H
#define VEC2_H

#include <sstream>
#include <string>

#include <cmath>

namespace Engine
{	
	class Vec2
	{
	public:
		Vec2();
		Vec2( float x, float y );

		~Vec2();

		const std::string toString() const;

		float dot( const Vec2& otherVec );
		Vec2 cross( const Vec2& otherVec );

		float length();
		Vec2 normalized();

		void setX( float x );
		void setY( float y );

		float getX() const;
		float getY() const;

		Vec2 operator+( const Vec2& otherVec );
		Vec2 operator+( float f );

		Vec2 operator-( const Vec2& otherVec );
		Vec2 operator-( float f );

		//Vec2 operator*( const Vec2& otherVec );
		Vec2 operator*( float factor );

		//Vec2 operator/( const Vec2& otherVec );
		Vec2 operator/( float denominator );


		Vec2& operator+=( const Vec2& otherVec );

		Vec2& operator-=( const Vec2& otherVec );

		Vec2& operator*=( const Vec2& otherVec );
		Vec2& operator*=( float factor );

	private:
		float x, y;
	};
}

#endif