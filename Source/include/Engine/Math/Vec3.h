#ifndef VEC3_H
#define VEC3_H

#include <string>

#include <cmath>

namespace Engine::Math
{
	class Vec3
	{
	public:
		Vec3();
		Vec3( float x, float y, float z );

		~Vec3();

		std::string toString();

		float dot( const Vec3& otherVec );
		Vec3 cross( const Vec3& otherVec );

		float length();
		Vec3 normalized();

		void setX( float x );
		void setY( float y );
		void setZ( float z );

		float getX() const;
		float getY() const;
		float getZ() const;

		Vec3 operator+( const Vec3& otherVec );
		Vec3 operator+( float f );

		Vec3 operator-( const Vec3& otherVec );
		Vec3 operator-( float f );

		//Vec3 operator*( const Vec3& otherVec );
		Vec3 operator*( float factor );

		//Vec3 operator/( const Vec3& otherVec );
		Vec3 operator/( float denominator );


		Vec3& operator+=( const Vec3& otherVec );
		Vec3& operator+=( float f );

		Vec3& operator-=( const Vec3& otherVec );
		Vec3& operator-=( float f );

		Vec3& operator*=( const Vec3& otherVec );
		Vec3& operator*=( float factor );

		Vec3& operator/=( const Vec3& otherVec );
		Vec3& operator/=( float denominator );

	private:
		float x, y, z;
	};
}

#endif