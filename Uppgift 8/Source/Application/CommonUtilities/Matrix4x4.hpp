#pragma once
#include "Vector.h"
#include <initializer_list>
#include <math.h>
#include <Macro.h>
namespace CommonUtilities
{
#define MATRIX_FOUR_TWODIM_SIZE 4
#define MATRIX_FOUR_ONEDIM_SIZE 16

	template<class T>
	class Matrix4x4
	{
	public:
		// Creates the identity matrix.
		Matrix4x4<T>();
		// Copy Constructor.
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix);
		// () operator for accessing element (row, column) for read/write or read,respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		Matrix4x4<T> operator+(Matrix4x4<T>& aMatrix);
		void operator+=(Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator-(Matrix4x4<T>& aMatrix);
		void operator-=(Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator*(Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix)const;
		void operator*=(Matrix4x4<T>& aMatrix);
		/*Vector4<T> operator*(Vector4<T>& aVector4);*/
		void operator=(const Matrix4x4<T>& aMatrix);
		bool operator==(const Matrix4x4<T>& aMatrixlhs)const;
		// Static functions for creating rotation matrices.
		static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians);
		// Static function for creating a transpose of a matrix.
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);
		// Assumes aTransform is made up of nothing but rotations and translations.
		static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aTransform);
		Vector3<T> GetForward()const;
		Vector3<T> GetRight()const;
		Vector3<T> GetUp()const;
		Vector3<T> GetPosition()const;
		Vector4<T> GetDirectionOrPosition()const;
		void AddToTranslation(const Vector3<T>& aVector3);
		void SetTranslation(const Vector3<T>& aVector3);
		void SetRotation(const Vector3<T>& aVector3, bool ValuesAreRadians = true);
		void Scale(const Vector3<T>& aVector3);
		void AddToRotation(const Vector3<T>& aVector3, bool ValuesAreRadians = true);
	private:
		void ResetRotation();
		union
		{
			T twoDim[4][4];
			T oneDim[16];
		}myMatrix;
	};
	template<class T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			if (i == 0 || i == 5 || i == 10 || i == 15)
			{
				myMatrix.oneDim[i] = 1;
			}
			else
			{
				myMatrix.oneDim[i] = 0;
			}
		}
	}

	template<class T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] = aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		// TODO: insert return statement here
		return myMatrix.twoDim[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		// TODO: insert return statement here
		return myMatrix.twoDim[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator+(Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> addMatrix;
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			addMatrix.myMatrix.oneDim[i] = myMatrix.oneDim[i] + aMatrix.myMatrix.oneDim[i];
		}
		return addMatrix;
	}

	template<class T>
	inline void Matrix4x4<T>::operator+=(Matrix4x4<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] += aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator-(Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> subMatrix;
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			subMatrix.myMatrix.oneDim[i] = myMatrix.oneDim[i] - aMatrix.myMatrix.oneDim[i];
		}
		return subMatrix;
	}

	template<class T>
	inline void Matrix4x4<T>::operator-=(Matrix4x4<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] -= aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*(Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T>multMatrix;
		int multMatIndex = 0;
		T sum = 0;
		for (int lMatRow = 0; lMatRow < MATRIX_FOUR_TWODIM_SIZE; lMatRow++)
		{
			for (int rMatCol = 0; rMatCol < MATRIX_FOUR_TWODIM_SIZE; rMatCol++)
			{
				sum = 0;
				for (int lMatColrMatRow = 0; lMatColrMatRow < MATRIX_FOUR_TWODIM_SIZE; lMatColrMatRow++)
				{
					sum += myMatrix.twoDim[lMatRow][lMatColrMatRow] * aMatrix.myMatrix.twoDim[lMatColrMatRow][rMatCol];
				}
				multMatrix.myMatrix.oneDim[multMatIndex] = sum;
				++multMatIndex;
			}
		}
		return multMatrix;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& aMatrix) const
	{
		Matrix4x4<T>multMatrix;
		int multMatIndex = 0;
		T sum = 0;
		for (int lMatRow = 0; lMatRow < MATRIX_FOUR_TWODIM_SIZE; lMatRow++)
		{
			for (int rMatCol = 0; rMatCol < MATRIX_FOUR_TWODIM_SIZE; rMatCol++)
			{
				sum = 0;
				for (int lMatColrMatRow = 0; lMatColrMatRow < MATRIX_FOUR_TWODIM_SIZE; lMatColrMatRow++)
				{
					sum += myMatrix.twoDim[lMatRow][lMatColrMatRow] * aMatrix.myMatrix.twoDim[lMatColrMatRow][rMatCol];
				}
				multMatrix.myMatrix.oneDim[multMatIndex] = sum;
				++multMatIndex;
			}
		}
		return multMatrix;
	}

	template<class T>
	inline void Matrix4x4<T>::operator*=(Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T>multMatrix;
		int multMatIndex = 0;
		T sum = 0;
		for (int lMatRow = 0; lMatRow < MATRIX_FOUR_TWODIM_SIZE; lMatRow++)
		{
			for (int rMatCol = 0; rMatCol < MATRIX_FOUR_TWODIM_SIZE; rMatCol++)
			{
				sum = 0;
				for (int lMatColrMatRow = 0; lMatColrMatRow < MATRIX_FOUR_TWODIM_SIZE; lMatColrMatRow++)
				{
					sum += myMatrix.twoDim[lMatRow][lMatColrMatRow] * aMatrix.myMatrix.twoDim[lMatColrMatRow][rMatCol];
				}
				multMatrix.myMatrix.oneDim[multMatIndex] = sum;
				++multMatIndex;
			}
		}
		*this = multMatrix;
	}

	/*template<class T>
	inline Vector4<T> Matrix4x4<T>::operator*(Vector4<T>& aVector4)
	{
		Vector4<T>multVector;
		int multMatIndex = 0;
		T sum = 0;
		for (int lMatRow = 0; lMatRow < MATRIX_FOUR_TWODIM_SIZE; lMatRow++)
		{
			sum = 0;
			for (int lMatColrVectorRow = 0; lMatColrVectorRow < MATRIX_FOUR_TWODIM_SIZE; lMatColrVectorRow++)
			{
				sum += myMatrix.twoDim[lMatRow][lMatColrVectorRow] * aVector4[lMatColrVectorRow];
			}
			multVector[multVectorIndex] = sum;
			++multVectorIndex;
		}

		return multVector;
	}*/

	template<class T>
	inline Vector4<T> operator*(const Vector4<T>& aVector4, const Matrix4x4<T>& aMatrix)
	{

		Vector4<T>multVector;
		int multVectorIndex = 0;
		T sum = 0;

		for (int rMatCol = 0; rMatCol < 4; rMatCol++)
		{
			sum = 0;
			for (int lVectorColrMatRow = 0; lVectorColrMatRow < 4; lVectorColrMatRow++)
			{
				sum += aVector4[lVectorColrMatRow] * aMatrix(lVectorColrMatRow + 1, rMatCol + 1);
			}
			multVector[multVectorIndex] = sum;
			++multVectorIndex;
		}

		return multVector;
	}

	template<class T>
	inline void Matrix4x4<T>::operator=(const Matrix4x4<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] = aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	inline bool Matrix4x4<T>::operator==(const Matrix4x4<T>& aMatrixlhs) const
	{
		for (int i = 0; i < MATRIX_FOUR_ONEDIM_SIZE; i++)
		{
			if (myMatrix.oneDim[i] != aMatrixlhs.myMatrix.oneDim[i])
			{
				return false;
			}
		}
		return true;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix4x4<T> xRot;

		xRot.myMatrix.oneDim[5] = cos(aAngleInRadians);
		xRot.myMatrix.oneDim[6] = sin(aAngleInRadians);
		xRot.myMatrix.oneDim[9] = -sin(aAngleInRadians);
		xRot.myMatrix.oneDim[10] = cos(aAngleInRadians);

		return xRot;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix4x4<T> yRot;

		yRot.myMatrix.oneDim[0] = cos(aAngleInRadians);
		yRot.myMatrix.oneDim[2] = -sin(aAngleInRadians);
		yRot.myMatrix.oneDim[8] = sin(aAngleInRadians);
		yRot.myMatrix.oneDim[10] = cos(aAngleInRadians);

		return yRot;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix4x4<T> zRot;

		zRot.myMatrix.oneDim[0] = cos(aAngleInRadians);
		zRot.myMatrix.oneDim[1] = sin(aAngleInRadians);
		zRot.myMatrix.oneDim[4] = -sin(aAngleInRadians);
		zRot.myMatrix.oneDim[5] = cos(aAngleInRadians);

		return zRot;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMatrixToTranspose)
	{
		Matrix4x4<T> trans;
		for (int i = 0; i < MATRIX_FOUR_TWODIM_SIZE; i++)
		{
			for (int j = 0; j < MATRIX_FOUR_TWODIM_SIZE; j++)
			{
				trans.myMatrix.twoDim[j][i] = aMatrixToTranspose.myMatrix.twoDim[i][j];
			}
		}

		return trans;
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
	{
		Matrix4x4<T> InversTranslationMatrix;
		InversTranslationMatrix.myMatrix.oneDim[12] = -aTransform.myMatrix.oneDim[12];
		InversTranslationMatrix.myMatrix.oneDim[13] = -aTransform.myMatrix.oneDim[13];
		InversTranslationMatrix.myMatrix.oneDim[14] = -aTransform.myMatrix.oneDim[14];

		Matrix4x4<T> RotationMatrix;
		RotationMatrix.myMatrix.oneDim[0] = aTransform.myMatrix.oneDim[0];
		RotationMatrix.myMatrix.oneDim[1] = aTransform.myMatrix.oneDim[1];
		RotationMatrix.myMatrix.oneDim[2] = aTransform.myMatrix.oneDim[2];
		RotationMatrix.myMatrix.oneDim[4] = aTransform.myMatrix.oneDim[4];
		RotationMatrix.myMatrix.oneDim[5] = aTransform.myMatrix.oneDim[5];
		RotationMatrix.myMatrix.oneDim[6] = aTransform.myMatrix.oneDim[6];
		RotationMatrix.myMatrix.oneDim[8] = aTransform.myMatrix.oneDim[8];
		RotationMatrix.myMatrix.oneDim[9] = aTransform.myMatrix.oneDim[9];
		RotationMatrix.myMatrix.oneDim[10] = aTransform.myMatrix.oneDim[10];
		Matrix4x4<T> InversRotationMatrix = Transpose(RotationMatrix);

		return InversTranslationMatrix * InversRotationMatrix;
	}

	template<class T>
	inline Vector3<T> Matrix4x4<T>::GetForward() const
	{
		Vector3<T> forwardVector = { myMatrix.oneDim[8],myMatrix.oneDim[9],myMatrix.oneDim[10] };
		return forwardVector.GetNormalized();
	}

	template<class T>
	inline Vector3<T> Matrix4x4<T>::GetRight() const
	{
		Vector3<T> rightVector = { myMatrix.oneDim[0],myMatrix.oneDim[1],myMatrix.oneDim[2] };

		return rightVector.GetNormalized();
	}

	template<class T>
	inline Vector3<T> Matrix4x4<T>::GetUp() const
	{
		Vector3<T> upVector = { myMatrix.oneDim[4],myMatrix.oneDim[5],myMatrix.oneDim[6] };
		return upVector.GetNormalized();
	}

	template<class T>
	inline Vector3<T> Matrix4x4<T>::GetPosition() const
	{
		return Vector3<T>(myMatrix.oneDim[12], myMatrix.oneDim[13], myMatrix.oneDim[14]);
	}

	template<class T>
	inline Vector4<T> Matrix4x4<T>::GetDirectionOrPosition() const
	{
		return Vector4<T>(myMatrix.oneDim[12], myMatrix.oneDim[13], myMatrix.oneDim[14], myMatrix.oneDim[15]);
	}

	template<class T>
	inline void Matrix4x4<T>::AddToTranslation(const Vector3<T>& aVector3)
	{
		myMatrix.oneDim[12] += aVector3.x;
		myMatrix.oneDim[13] += aVector3.y;
		myMatrix.oneDim[14] += aVector3.z;
	}

	template<class T>
	inline void Matrix4x4<T>::SetTranslation(const Vector3<T>& aVector3)
	{
		myMatrix.oneDim[12] = aVector3.x;
		myMatrix.oneDim[13] = aVector3.y;
		myMatrix.oneDim[14] = aVector3.z;
	}

	template<class T>
	inline void Matrix4x4<T>::SetRotation(const Vector3<T>& aVector3, bool ValuesAreRadians)
	{
		ResetRotation();
		AddToRotation(aVector3, ValuesAreRadians);
	}
	template<class T>
	inline void Matrix4x4<T>::Scale(const Vector3<T>& aVector3)
	{
		Matrix4x4<float>scale;
		scale(1, 1) = aVector3.x;
		scale(2, 2) = aVector3.y;
		scale(3, 3) = aVector3.z;
		*this = scale* *this;
	}
	template<class T>
	inline void Matrix4x4<T>::AddToRotation(const Vector3<T>& aVector3, bool ValuesAreRadians)
	{
		Matrix4x4<T> matrix = *this;
		if (ValuesAreRadians == true)
		{
			matrix = CreateRotationAroundX(aVector3.x) * matrix;
			matrix = CreateRotationAroundY(aVector3.y) * matrix;
			matrix = CreateRotationAroundZ(aVector3.z) * matrix;
		}
		else
		{
			T convert = PI / 180;
			matrix = CreateRotationAroundX(aVector3.x * convert) * matrix;
			matrix = CreateRotationAroundY(aVector3.y * convert) * matrix;
			matrix = CreateRotationAroundZ(aVector3.z * convert) * matrix;
		}
		*this = matrix;
	}
	template<class T>
	inline void Matrix4x4<T>::ResetRotation()
	{
		myMatrix.oneDim[5] = 1;
		myMatrix.oneDim[6] = 0;
		myMatrix.oneDim[9] = 0;
		myMatrix.oneDim[10] = 1;

		myMatrix.oneDim[0] = 1;
		myMatrix.oneDim[2] = 0;
		myMatrix.oneDim[8] = 0;

		myMatrix.oneDim[1] = 0;
		myMatrix.oneDim[4] = 0;
	}
}