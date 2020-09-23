#pragma once
#include <math.h>
namespace CommonUtilities
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;
		
		//Creates a null-vector
		Vector2<T>();
		//Creates a vector (aX, aY, aZ)
		Vector2<T>(const T& aX, const T& aY);
		//Copy constructor (compiler generated)
		Vector2<T>(const Vector2<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;
		//Destructor (compiler generated)
		~Vector2<T>() = default;
		//Returns the squared length of the vector
		T LengthSqr() const;
		//Returns the length of the vector
		T Length() const;
		//Returns a normalized copy of this
		Vector2<T> GetNormalized() const;
		//Normalizes the vector
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector2<T>& aVector) const;
		//Returns the cross product of this and aVector
	};


	template<class T>
	inline Vector2<T>::Vector2()
	{
		x = NULL;
		y = NULL;
	}
	template<class T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY)
	{
		x = aX;
		y = aY;
	}

	template<class T>
	inline T Vector2<T>::LengthSqr() const
	{
		T lenghtSqr = (x * x) + (y * y);
		return lenghtSqr;
	}

	template<class T>
	inline T Vector2<T>::Length() const
	{
		T length = sqrt((x * x) + (y * y));
		return length;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		T length = sqrt((x * x) + (y * y));

		if (length == 0)
		{
			return Vector2<T>(x, y);
		}
		else
		{
			T NormalScalar = T(1) / length;

			T NormX = x * NormalScalar;
			T NormY = y * NormalScalar;
			Vector2<T> NormalizedVector = Vector2<T>(NormX, NormY);

			return NormalizedVector;
		}
	}

	template<class T>
	inline void Vector2<T>::Normalize()
	{
		T length = sqrt((x * x) + (y * y));
		if (length == 0)
		{
			return;
		}
		else
		{
			T NormalScalar = T(1) / length;
			x *= NormalScalar;
			y *= NormalScalar;
		}
	}

	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		T dot = (this->x * aVector.x) + (this->y * aVector.y);

		return dot;
	}


	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		T x = aVector0.x + aVector1.x;
		T y = aVector0.y + aVector1.y;
		Vector2<T> CombinedVectors = CommonUtilities::Vector2<T>(x, y);
		return CombinedVectors;
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		T x = aVector0.x - aVector1.x;
		T y = aVector0.y - aVector1.y;
		Vector2<T> DifferenceVector = CommonUtilities::Vector2<T>(x, y);
		return DifferenceVector;
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		Vector2<T> MultipliedVector = CommonUtilities::Vector2<T>(x, y);
		return MultipliedVector;
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		Vector2<T> MultipliedVector = CommonUtilities::Vector2<T>(x, y);
		return MultipliedVector;
	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1 / aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		T multiScalar = 1 / aScalar;
		T x = aVector.x * multiScalar;
		T y = aVector.y * multiScalar;
		Vector2<T> MultipliedVector = CommonUtilities::Vector2<T>(x, y);
		return MultipliedVector;
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		T multiScalar = 1 / aScalar;
		aVector.x *= multiScalar;
		aVector.y *= multiScalar;
	}
}
