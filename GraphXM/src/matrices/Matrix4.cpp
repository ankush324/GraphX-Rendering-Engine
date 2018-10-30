#include "Matrix4.h"

#include <iostream>
#include "../vectors/Vector3.h"
#include "../vectors/Vector4.h"

namespace gm
{
	Matrix4::Matrix4()
	{
		Identity();
	}

	Matrix4::Matrix4(float Value)
	{
		Init(Value);
	}

	Matrix4::Matrix4(const Matrix4& OtherMat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				M[i][j] = OtherMat.M[i][j];
			}
		}
	}

	void Matrix4::Init(float Value)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				M[i][j] = Value;
			}
		}
	}

	void Matrix4::Identity()
	{
		M[0][0] = 1, M[0][1] = 0, M[0][2] = 0, M[0][3] = 0;
		M[1][0] = 0, M[1][1] = 1, M[1][2] = 0, M[1][3] = 0;
		M[2][0] = 0, M[2][1] = 0, M[2][2] = 1, M[2][3] = 0;
		M[3][0] = 0, M[3][1] = 0, M[3][2] = 0, M[3][3] = 1;
	}

	#pragma region Operators
	bool Matrix4::operator==(const Matrix4& OtherMat) const
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (M[i][j] != OtherMat.M[i][j])
					return false;
			}
		}

		return true;
	}

	bool Matrix4::operator!=(const Matrix4& OtherMat) const
	{
		return !(*this == OtherMat);
	}

	const Matrix4 Matrix4::operator+(const Matrix4& OtherMat) const
	{
		Matrix4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[i][j] = M[i][j] + OtherMat.M[i][j];
			}
		}

		return result;
	}

	const Matrix4 Matrix4::operator-(const Matrix4& OtherMat) const
	{
		Matrix4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[i][j] = M[i][j] - OtherMat.M[i][j];
			}
		}

		return result;
	}

	const Matrix4 Matrix4::operator*(const Matrix4& OtherMat) const
	{
		Matrix4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				float val = 0;

				for (int k = 0; k < 4; k++)
				{
					val += M[i][k] * OtherMat.M[k][j];
				}
				result.M[i][j] = val;
			}
		}

		return result;
	}

	const Matrix4 Matrix4::operator+(float Value) const
	{
		Matrix4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[i][j] = M[i][j] + Value;
			}
		}

		return result;
	}

	const Matrix4 Matrix4::operator-(float Value) const
	{
		Matrix4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[i][j] = M[i][j] - Value;
			}
		}

		return result;
	}

	const Matrix4 Matrix4::operator*(float Value) const
	{
		Matrix4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[i][j] = M[i][j] * Value;
			}
		}

		return result;
	}

	const Matrix4 Matrix4::operator/(float Value) const
	{
		Matrix4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[i][j] = (Value == 0) ? FLT_MAX : M[i][j] / Value;
			}
		}

		return result;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& OtherMat)
	{
		*this = *this + OtherMat;
		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& OtherMat)
	{
		*this = *this - OtherMat;
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& OtherMat)
	{
		*this = *this * OtherMat;
		return *this;
	}

	Matrix4& Matrix4::operator+=(float Value)
	{
		*this = *this + Value;
		return *this;
	}

	Matrix4& Matrix4::operator-=(float Value)
	{
		*this = *this - Value;
		return *this;
	}

	Matrix4& Matrix4::operator*=(float Value)
	{
		*this = *this * Value;
		return *this;
	}

	Matrix4& Matrix4::operator/=(float Value)
	{
		*this = *this / Value;
		return *this;
	}

	#pragma endregion

	Matrix4 Matrix4::Transpose() const
	{
		Matrix4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[j][i] = M[i][j];
			}
		}

		return result;
	}

	const Vector4 Matrix4::operator*(const Vector4& Vec) const
	{
		Vector4 result(
			M[0][0] * Vec.x + M[0][1] * Vec.y + M[0][2] * Vec.z + M[0][3] * Vec.w,
			M[1][0] * Vec.x + M[1][1] * Vec.y + M[1][2] * Vec.z + M[1][3] * Vec.w,
			M[2][0] * Vec.x + M[2][1] * Vec.y + M[2][2] * Vec.z + M[2][3] * Vec.w,
			M[3][0] * Vec.x + M[3][1] * Vec.y + M[3][2] * Vec.z + M[3][3] * Vec.w
		);

		return result;
	}

	float Matrix4::Determinant() const
	{
		return (
			  M[0][0] * (
				  M[1][1] * (M[2][2] * M[3][3] - M[3][2] * M[3][3])
				- M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])
				+ M[1][3] * (M[2][1] * M[3][2] - M[3][1] * M[2][2])
				)
			- M[0][1] * (
				  M[1][0] * (M[2][2] * M[3][3] - M[3][2] * M[2][3])
				- M[1][2] * (M[2][0] * M[3][3] - M[3][0] * M[2][3])
				+ M[1][3] * (M[2][0] * M[3][2] - M[3][0] * M[2][2])
				)
			+ M[0][2] * (
				  M[1][0] * (M[2][1] * M[3][3] - M[3][1] * M[2][3])
				- M[1][1] * (M[2][0] * M[3][3] - M[3][0] * M[2][3])
				+ M[1][3] * (M[2][0] * M[3][1] - M[3][0] * M[2][1])
				)
			- M[0][3] * (
				  M[1][0] * (M[2][1] * M[3][2] - M[3][1] * M[2][2])
				- M[1][1] * (M[2][0] * M[3][2] - M[3][0] * M[2][2])
				+ M[1][2] * (M[2][0] * M[3][1] - M[3][0] * M[2][1])
				)
			);
	}

	Matrix4 Matrix4::Adjoint() const
	{
		Matrix4 mat;

		/* First row */
		mat.M[0][0] =   (  M[1][1] * (M[2][2] * M[3][3] - M[3][2] * M[3][3])
					     - M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])
					     + M[1][3] * (M[2][1] * M[3][2] - M[3][1] * M[2][2]));

		mat.M[0][1] = - (  M[1][0] * (M[2][2] * M[3][3] - M[3][2] * M[2][3])
					     - M[1][2] * (M[2][0] * M[3][3] - M[3][0] * M[2][3])
						 + M[1][3] * (M[2][0] * M[3][2] - M[3][0] * M[2][2]));

		mat.M[0][2] =   (  M[1][0] * (M[2][1] * M[3][3] - M[3][1] * M[2][3])
						 - M[1][1] * (M[2][0] * M[3][3] - M[3][0] * M[2][3])
						 + M[1][3] * (M[2][0] * M[3][1] - M[3][0] * M[2][1]));

		mat.M[0][3] = - (  M[1][0] * (M[2][1] * M[3][2] - M[3][1] * M[2][2])
						 - M[1][1] * (M[2][0] * M[3][2] - M[3][0] * M[2][2])
						 + M[1][2] * (M[2][0] * M[3][1] - M[3][0] * M[2][1]));

		/* Second Row */
		mat.M[1][0] = - (  M[0][1] * (M[2][2] * M[3][3] - M[3][2] * M[3][3])
					     - M[0][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])
					     + M[0][3] * (M[2][1] * M[3][2] - M[3][1] * M[2][2]));

		mat.M[1][1] =   (  M[0][0] * (M[2][2] * M[3][3] - M[3][2] * M[2][3])
					     - M[0][2] * (M[2][0] * M[3][3] - M[3][0] * M[2][3])
						 + M[0][3] * (M[2][0] * M[3][2] - M[3][0] * M[2][2]));

		mat.M[1][2] = - (  M[0][0] * (M[2][1] * M[3][3] - M[3][1] * M[2][3])
						 - M[0][1] * (M[2][0] * M[3][3] - M[3][0] * M[2][3])
						 + M[0][3] * (M[2][0] * M[3][1] - M[3][0] * M[2][1]));

		mat.M[1][3] =   (  M[0][0] * (M[2][1] * M[3][2] - M[3][1] * M[2][2])
						 - M[0][1] * (M[2][0] * M[3][2] - M[3][0] * M[2][2])
						 + M[0][2] * (M[2][0] * M[3][1] - M[3][0] * M[2][1]));

		/* Third Row */
		mat.M[2][0] =   (  M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2])
					     - M[0][2] * (M[1][1] * M[3][3] - M[3][1] * M[1][3])
					     + M[0][3] * (M[1][1] * M[3][2] - M[3][1] * M[1][2]));

		mat.M[2][1] = - (  M[0][0] * (M[1][2] * M[3][3] - M[3][2] * M[1][3])
					     - M[0][2] * (M[1][0] * M[3][3] - M[3][0] * M[1][3])
						 + M[0][3] * (M[1][0] * M[3][2] - M[3][0] * M[1][2]));

		mat.M[2][2] =   (  M[0][0] * (M[1][1] * M[3][3] - M[3][1] * M[1][3])
						 - M[0][1] * (M[1][0] * M[3][3] - M[3][0] * M[1][3])
						 + M[0][3] * (M[1][0] * M[3][1] - M[3][0] * M[1][1]));

		mat.M[2][3] = - (  M[0][0] * (M[1][1] * M[3][2] - M[3][1] * M[1][2])
						 - M[0][1] * (M[1][0] * M[3][2] - M[3][0] * M[1][2])
						 + M[0][2] * (M[1][0] * M[3][1] - M[3][0] * M[1][1]));

		/* Fourth Row */
		mat.M[3][0] = - (  M[0][1] * (M[1][2] * M[2][3] - M[2][2] * M[1][3])
					     - M[0][2] * (M[1][1] * M[2][3] - M[2][1] * M[1][3])
					     + M[0][3] * (M[1][1] * M[2][2] - M[2][1] * M[1][2]));

		mat.M[3][1] =   (  M[0][0] * (M[1][2] * M[2][3] - M[2][2] * M[1][3])
					     - M[0][2] * (M[1][0] * M[2][3] - M[2][0] * M[1][3])
						 + M[0][3] * (M[1][0] * M[2][2] - M[2][0] * M[1][2]));

		mat.M[3][2] = - (  M[0][0] * (M[1][1] * M[2][3] - M[2][1] * M[1][3])
						 - M[0][1] * (M[1][0] * M[2][3] - M[2][0] * M[1][3])
						 + M[0][3] * (M[1][0] * M[2][1] - M[2][0] * M[1][1]));

		mat.M[3][3] =   (  M[0][0] * (M[1][1] * M[2][2] - M[2][1] * M[1][2])
						 - M[0][1] * (M[1][0] * M[2][2] - M[2][0] * M[1][2])
						 + M[0][2] * (M[1][0] * M[2][1] - M[2][0] * M[1][1]));

		mat = mat.Transpose();
		return mat;
	}

	Matrix4 Matrix4::Inverse() const
	{
		Matrix4 mat;

		// Get the adjoint of the matrix
		mat = this->Adjoint();

		// Divide the adjoint by determinant
		mat /= this->Determinant();

		return mat;
	}

	/* Non Member functions */
	std::ostream& operator<<(std::ostream& Out, const Matrix4& Mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				Out << Mat.M[i][j] << " ";

			Out << std::endl;
		}

		return Out;
	}
}