#pragma once
#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include <math.h>

namespace CommonUtilities
{
#define MATRIX_THREE_TWODIM_SIZE 3
#define MATRIX_THREE_ONEDIM_SIZE 9
	template<class T>
	class Matrix3x3
	{
	public:
		// Creates the identity matrix.
		Matrix3x3<T>();
		// Copy Constructor.
		Matrix3x3<T>(const Matrix3x3<T>& aMatrix);
		// Copies the top left 3x3 part of the Matrix4x4.
		Matrix3x3<T>(const Matrix4x4<T>& aMatrix);

		// () operator for accessing element (row, column) for read/write or read,respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		Matrix3x3<T> operator+(Matrix3x3<T>& aMatrix);
		void operator+=(Matrix3x3<T>& aMatrix);
		Matrix3x3<T> operator-(Matrix3x3<T>& aMatrix);
		void operator-=(Matrix3x3<T>& aMatrix);
		Matrix3x3<T> operator*(Matrix3x3<T>& aMatrix);
		void operator*=(Matrix3x3<T>& aMatrix);
		Vector3<T> operator*(Vector3<T>& aVector3);
		void operator=(Matrix3x3<T>& aMatrix);
		bool operator==(const Matrix3x3<T>& aMatrix)const;

		// Static functions for creating rotation matrices.
		static Matrix3x3<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundZ(T aAngleInRadians);
		// Static function for creating a transpose of a matrix.
		static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose);
	private:
		union
		{
			T oneDim[9];
			T twoDim[3][3];
		}myMatrix;
	};
	template<class T>
	inline Matrix3x3<T>::Matrix3x3()
	{
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			if (i == 0 || i == 4 || i == 8)
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
	inline Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] = aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_THREE_TWODIM_SIZE; i++)
		{
			for (int j = 0; j < MATRIX_THREE_TWODIM_SIZE; j++)
			{
				myMatrix.twoDim[i][j] = aMatrix(i + 1, j + 1);
			}
		}
	}

	template<class T>
	inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		return myMatrix.twoDim[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		return myMatrix.twoDim[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator+(Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> addMatrix;
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			addMatrix.myMatrix.oneDim[i] = myMatrix.oneDim[i] + aMatrix.myMatrix.oneDim[i];
		}
		return addMatrix;
	}

	template<class T>
	inline void Matrix3x3<T>::operator+=(Matrix3x3<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] = myMatrix.oneDim[i] + aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator-(Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> subMatrix;
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			subMatrix.myMatrix.oneDim[i] = myMatrix.oneDim[i] - aMatrix.myMatrix.oneDim[i];
		}
		return subMatrix;
	}

	template<class T>
	inline void Matrix3x3<T>::operator-=(Matrix3x3<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] -= aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	Vector3<T> operator*(Vector3<T>& aVector3, Matrix3x3<T>& aMatrix)
	{
		Vector3<T>multVector;
		int multVectorIndex = 0;
		T sum = 0;

		for (int rMatCol = 0; rMatCol < MATRIX_THREE_TWODIM_SIZE; rMatCol++)
		{
			sum = 0;
			for (int lVectorColrMatRow = 0; lVectorColrMatRow < MATRIX_THREE_TWODIM_SIZE; lVectorColrMatRow++)
			{
				sum += aVector3[lVectorColrMatRow] * aMatrix(lVectorColrMatRow + 1, rMatCol + 1);
			}
			multVector[multVectorIndex] = sum;
			++multVectorIndex;
		}

		return multVector;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T>multMatrix;
		int multMatIndex = 0;
		T sum = 0;
		for (int lMatRow = 0; lMatRow < MATRIX_THREE_TWODIM_SIZE; lMatRow++)
		{
			for (int rMatCol = 0; rMatCol < MATRIX_THREE_TWODIM_SIZE; rMatCol++)
			{
				sum = 0;
				for (int lMatColrMatRow = 0; lMatColrMatRow < MATRIX_THREE_TWODIM_SIZE; lMatColrMatRow++)
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
	inline void Matrix3x3<T>::operator*=(Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T>multMatrix;
		int multMatIndex = 0;
		T sum = 0;
		for (int lMatRow = 0; lMatRow < MATRIX_THREE_TWODIM_SIZE; lMatRow++)
		{
			for (int rMatCol = 0; rMatCol < MATRIX_THREE_TWODIM_SIZE; rMatCol++)
			{
				sum = 0;
				for (int lMatColrMatRow = 0; lMatColrMatRow < MATRIX_THREE_TWODIM_SIZE; lMatColrMatRow++)
				{
					sum += myMatrix.twoDim[lMatRow][lMatColrMatRow] * aMatrix.myMatrix.twoDim[lMatColrMatRow][rMatCol];
				}
				multMatrix.myMatrix.oneDim[multMatIndex] = sum;
				++multMatIndex;
			}
		}
		*this = multMatrix;
	}

	template<class T>
	inline Vector3<T> Matrix3x3<T>::operator*(Vector3<T>& aVector3)
	{
		Vector43T > multVector;
		int multMatIndex = 0;
		T sum = 0;
		for (int lMatRow = 0; lMatRow < MATRIX_THREE_TWODIM_SIZE; lMatRow++)
		{
			sum = 0;
			for (int lMatColrVectorRow = 0; lMatColrVectorRow < twoDimSize; lMatColrVectorRow++)
			{
				sum += myMatrix.twoDim[lMatRow][lMatColrMatRow] * aVector[lMatColrVectorRow];
			}
			multVector[multVectorIndex] = sum;
			++multVectorIndex;
		}

		return multVector;
	}

	template<class T>
	inline void Matrix3x3<T>::operator=(Matrix3x3<T>& aMatrix)
	{
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			myMatrix.oneDim[i] = aMatrix.myMatrix.oneDim[i];
		}
	}

	template<class T>
	inline bool Matrix3x3<T>::operator==(const Matrix3x3<T>& aMatrix) const
	{
		for (int i = 0; i < MATRIX_THREE_ONEDIM_SIZE; i++)
		{
			if (myMatrix.oneDim[i] != aMatrix.myMatrix.oneDim[i])
			{
				return false;
			}
		}
		return true;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix3x3<T> xRot;

		xRot.myMatrix.oneDim[4] = cos(aAngleInRadians);
		xRot.myMatrix.oneDim[5] = sin(aAngleInRadians);
		xRot.myMatrix.oneDim[7] = -sin(aAngleInRadians);
		xRot.myMatrix.oneDim[8] = cos(aAngleInRadians);

		return xRot;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix3x3<T> yRot;

		yRot.myMatrix.oneDim[0] = cos(aAngleInRadians);
		yRot.myMatrix.oneDim[2] = -sin(aAngleInRadians);
		yRot.myMatrix.oneDim[6] = sin(aAngleInRadians);
		yRot.myMatrix.oneDim[8] = cos(aAngleInRadians);

		return yRot;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix3x3<T> zRot;

		zRot.myMatrix.oneDim[0] = cos(aAngleInRadians);
		zRot.myMatrix.oneDim[1] = sin(aAngleInRadians);
		zRot.myMatrix.oneDim[3] = -sin(aAngleInRadians);
		zRot.myMatrix.oneDim[4] = cos(aAngleInRadians);

		return zRot;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMatrixToTranspose)
	{
		Matrix3x3<T> trans;
		for (int i = 0; i < MATRIX_THREE_TWODIM_SIZE; i++)
		{
			for (int j = 0; j < MATRIX_THREE_TWODIM_SIZE; j++)
			{
				trans.myMatrix.twoDim[j][i] = aMatrixToTranspose.myMatrix.twoDim[i][j];
			}
		}

		return trans;
	}

}