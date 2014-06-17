#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <string>

#include <cmath>

namespace Engine
{
	class Vector3f
	{
	public:
		Vector3f();
		Vector3f( float x, float y, float z );

		~Vector3f();

		std::string toString();

		float dot( const Vector3f& otherVec );
		Vector3f cross( const Vector3f& otherVec );

		float length();
		void normalize();

		void setX( float x );
		void setY( float y );
		void setZ( float z );

		float getX() const;
		float getY() const;
		float getZ() const;

		Vector3f operator+( const Vector3f& otherVec );
		Vector3f operator+( float f );

		Vector3f operator-( const Vector3f& otherVec );
		Vector3f operator-( float f );

		Vector3f operator*( const Vector3f& otherVec );
		Vector3f operator*( float factor );

		Vector3f operator/( const Vector3f& otherVec );
		Vector3f operator/( float denominator );


		Vector3f& operator+=( const Vector3f& otherVec );
		Vector3f& operator+=( float f );

		Vector3f& operator-=( const Vector3f& otherVec );
		Vector3f& operator-=( float f );

		Vector3f& operator*=( const Vector3f& otherVec );
		Vector3f& operator*=( float factor );

		Vector3f& operator/=( const Vector3f& otherVec );
		Vector3f& operator/=( float denominator );

	private:
		float x, y, z;
	};
}

#endif