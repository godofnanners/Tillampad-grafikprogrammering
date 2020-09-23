#pragma once
#include <math.h>
#include <assert.h>
namespace CommonUtilities
{
	template <class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		int arrayFormatSize = 3;
		//Creates a null-vector
		Vector3<T>();
		//Creates a vector (aX, aY, aZ)
		Vector3<T>(const T& aX, const T& aY, const T& aZ);
		//Copy constructor (compiler generated)
		Vector3<T>(const Vector3<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;
		T& operator[](const int& aIndex);
		const T& operator[](const int& aIndex) const;
		//Destructor (compiler generated)
		~Vector3<T>() = default;
		//Returns the squared length of the vector
		T LengthSqr() const;
		//Returns the length of the vector
		T Length() const;
		//Returns a normalized copy of this
		Vector3<T> GetNormalized() const;
		//Normalizes the vector
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const;
		//Returns the cross product of this and aVector
		Vector3<T> Cross(const Vector3<T>& aVector) const;
	};


	template<class T>
	inline Vector3<T>::Vector3()
	{
		x = NULL;
		y = NULL;
		z = NULL;
	}
	template<class T>
	inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<class T>
	inline T& Vector3<T>::operator[](const int& aIndex)
	{
		assert(aIndex < arrayFormatSize && L"Number is bigger than array");
		assert(aIndex >= 0 && L"Number is below zero (minimum of array)");
		if (aIndex == 0)
		{
			return x;
		}
		else if (aIndex == 1)
		{
			return y;
		}
		else
		{
			return z;
		}
	}

	template<class T>
	inline const T& Vector3<T>::operator[](const int& aIndex) const
	{
		assert(aIndex < arrayFormatSize && L"Number is bigger than array");
		assert(aIndex >= 0 && L"Number is below zero (minimum of array)");
		if (aIndex == 0)
		{
			return x;
		}
		else if (aIndex == 1)
		{
			return y;
		}
		else
		{
			return z;
		}
	}

	template<class T>
	inline T Vector3<T>::LengthSqr() const
	{
		T lenghtSqr = (x * x) + (y * y) + (z * z);
		return lenghtSqr;
	}

	template<class T>
	inline T Vector3<T>::Length() const
	{
		T length = sqrt((x * x) + (y * y) + (z * z));
		return length;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		T length = sqrt((x * x) + (y * y) + (z * z));

		if (length==0)
		{
			return Vector3<T>(x, y, z);
		}
		else
		{
			T NormalScalar = T(1) / length;

			T NormX = x * NormalScalar;
			T NormY = y * NormalScalar;
			T NormZ = z * NormalScalar;
			Vector3<T> NormalizedVector = Vector3<T>(NormX, NormY, NormZ);
			return NormalizedVector;

		}

	}

	template<class T>
	inline void Vector3<T>::Normalize()
	{
		T length = sqrt((x * x) + (y * y) + (z * z));
		if (length==0)
		{
			return;
		}
		else
		{
			T NormalScalar = T(1) / length;
			x *= NormalScalar;
			y *= NormalScalar;
			z *= NormalScalar;
		}
	}

	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		T dot = (this->x * aVector.x) + (this->y * aVector.y) + (this->z*aVector.z);
			
		return dot;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		T crossX= (this->y*aVector.z)-(this->z*aVector.y);
		T crossY= (this->z * aVector.x) - (this->x * aVector.z);
		T crossZ=(this->x * aVector.y) - (this->y * aVector.x);
		Vector3<T> CrossVector = Vector3<T>(crossX,crossY,crossZ);
		return CrossVector;
	}

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		T x = aVector0.x + aVector1.x;
		T y = aVector0.y + aVector1.y;
		T z = aVector0.z + aVector1.z;
		Vector3<T> CombinedVectors = CommonUtilities::Vector3<T>(x, y, z);
		return CombinedVectors;
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		T x = aVector0.x - aVector1.x;
		T y = aVector0.y - aVector1.y;
		T z = aVector0.z - aVector1.z;
		Vector3<T> DifferenceVector = CommonUtilities::Vector3<T>(x, y, z);
		return DifferenceVector;
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		T z = aVector.z * aScalar;
		Vector3<T> MultipliedVector = CommonUtilities::Vector3<T>(x, y, z);
		return MultipliedVector;
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		T z = aVector.z * aScalar;
		Vector3<T> MultipliedVector = CommonUtilities::Vector3<T>(x, y, z);
		return MultipliedVector;
	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1 / aScalar)
	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		T multiScalar = 1 / aScalar;
		T x = aVector.x * multiScalar;
		T y = aVector.y * multiScalar;
		T z = aVector.z * multiScalar;
		Vector3<T> MultipliedVector = CommonUtilities::Vector3<T>(x, y, z);
		return MultipliedVector;
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		T multiScalar = 1 / aScalar;
		aVector.x *= multiScalar;
		aVector.y *= multiScalar;
		aVector.z *= multiScalar;
	}
}
