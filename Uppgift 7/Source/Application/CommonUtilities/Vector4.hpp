#pragma once
#include <math.h>
#include <assert.h>
namespace CommonUtilities
{
	template <class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;
		int arrayFormatSize = 4;

		//Creates a null-vector
		Vector4<T>();
		//Creates a vector (aX, aY, aZ, aW)
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);
		//Copy constructor (compiler generated)
		Vector4<T>(const Vector4<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;
		T& operator[](const int& aIndex);
		const T& operator[](const int& aIndex) const;

		T GetFromArrayFormat(const int& aNumber);
		//Destructor (compiler generated)
		~Vector4<T>() = default;
		//Returns the squared length of the vector
		T LengthSqr() const;
		//Returns the length of the vector
		T Length() const;
		//Returns a normalized copy of this
		Vector4<T> GetNormalized() const;
		//Normalizes the vector
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector4<T>& aVector) const;

	};


	template<class T>
	inline Vector4<T>::Vector4()
	{
		x = NULL;
		y = NULL;
		z = NULL;
		w = NULL;
	}
	template<class T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}



	template<class T>
	inline T& Vector4<T>::operator[](const int& aIndex)
	{
		assert(aIndex < arrayFormatSize && L"Number is bigger than array");
		assert(aIndex >= 0  && L"Number is below zero (minimum of array)");
		if (aIndex == 0)
		{
			return x;
		}
		else if (aIndex == 1)
		{
			return y;
		}
		else if (aIndex == 2)
		{
			return z;
		}
		else if (aIndex == 3)
		{
			return w;
		}
		
	}

	template<class T>
	inline const T& Vector4<T>::operator[](const int& aIndex) const
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
		else if (aIndex == 2)
		{
			return z;
		}
		else if (aIndex == 3)
		{
			return w;
		}
	}

	template<class T>
	inline T Vector4<T>::GetFromArrayFormat(const int& aNumber)
	{
		assert(aNumber < arrayFormatSize && L"Number is bigger than array");
		assert( aNumber >= 0 && L"Number is below zero (minimum of array)");
		if (0)
		{
			return x;
		}
		else if (1)
		{
			return y;
		}
		else if (2)
		{
			return z;
		}
		else if (3)
		{
			return w;
		}
	}

	template<class T>
	inline T Vector4<T>::LengthSqr() const
	{
		T lenghtSqr = (x * x) + (y * y) + (z * z) + (w * w);
		return lenghtSqr;
	}

	template<class T>
	inline T Vector4<T>::Length() const
	{
		T length = sqrt((x * x) + (y * y) + (z * z) + (w * w));
		return length;
	}

	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		T length = sqrt((x * x) + (y * y) + (z * z) + (w * w));

		if (length == 0)
		{
			return Vector4<T>(x, y, z, w);
		}
		else
		{
			T NormalScalar = T(1) / length;

			T NormX = x * NormalScalar;
			T NormY = y * NormalScalar;
			T NormZ = z * NormalScalar;
			T NormW = w * NormalScalar;
			Vector4<T> NormalizedVector = Vector4<T>(NormX, NormY, NormZ, NormW);
			return NormalizedVector;
		}

	}

	template<class T>
	inline void Vector4<T>::Normalize()
	{
		T length = sqrt((x * x) + (y * y) + (z * z) + (w * w));
		if (length == 0)
		{
			return;
		}
		else
		{
			T NormalScalar = T(1) / length;
			x *= NormalScalar;
			y *= NormalScalar;
			z *= NormalScalar;
			w *= NormalScalar;
		}
	}

	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		T dot = (this->x * aVector.x) + (this->y * aVector.y) + (this->z * aVector.z) + (this->w * aVector.w);

		return dot;
	}

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		T x = aVector0.x + aVector1.x;
		T y = aVector0.y + aVector1.y;
		T z = aVector0.z + aVector1.z;
		T w = aVector0.w + aVector1.w;
		Vector4<T> CombinedVectors = CommonUtilities::Vector4<T>(x, y, z, w);
		return CombinedVectors;
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		T x = aVector0.x - aVector1.x;
		T y = aVector0.y - aVector1.y;
		T z = aVector0.z - aVector1.z;
		T w = aVector0.w - aVector1.w;
		Vector4<T> DifferenceVector = CommonUtilities::Vector4<T>(x, y, z, w);
		return DifferenceVector;
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		T z = aVector.z * aScalar;
		T w = aVector.w * aScalar;
		Vector4<T> MultipliedVector = CommonUtilities::Vector4<T>(x, y, z, w);
		return MultipliedVector;
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		T z = aVector.z * aScalar;
		T w = aVector.w * aScalar;
		Vector4<T> MultipliedVector = CommonUtilities::Vector4<T>(x, y, z, w);
		return MultipliedVector;
	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1 / aScalar)
	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		T multiScalar = 1 / aScalar;
		T x = aVector.x * multiScalar;
		T y = aVector.y * multiScalar;
		T z = aVector.z * multiScalar;
		T w = aVector.w * multiScalar;
		Vector4<T> MultipliedVector = CommonUtilities::Vector4<T>(x, y, z, w);
		return MultipliedVector;
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		T multiScalar = 1 / aScalar;
		aVector.x *= multiScalar;
		aVector.y *= multiScalar;
		aVector.z *= multiScalar;
		aVector.w *= multiScalar;
	}


}