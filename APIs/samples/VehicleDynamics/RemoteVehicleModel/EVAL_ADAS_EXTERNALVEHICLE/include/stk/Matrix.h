
#pragma once

#include "stk/STK.h"

#include <iostream>

#include "stk/Vector3.h"
#include <assert.h>

namespace stk {

//structure representant une matrice x.x de doubles
class STK_API Matrix
{
public:
	Matrix(int sizei=0, int sizej=0, bool reset = true);
	Matrix(const Matrix& Mat);
	virtual ~Matrix();

	void resize(int sizei, int sizej, bool reset = true);

	double& operator()(int i, int j);
	const double& operator()(int i, int j) const;

	int sizeI() const;
	int sizeJ() const;

	Matrix operator+(const Matrix& Mat) const;
	Matrix operator-(const Matrix& Mat) const;

	Matrix& operator+=(const Matrix& Mat);
	Matrix& operator-=(const Matrix& Mat);

	Matrix& operator=(const Matrix& Mat);

	Matrix operator*(const Matrix& Mat) const;
	Matrix operator*(double val) const;
	
	Matrix& operator*=(const Matrix& Mat);
	Matrix& operator*=(double val);

	void transpose();

	virtual bool inverse();

	bool isInversible() const;

	// Computes a submatrix in order to get determinant recursively
	void minorMatrix(stk::Matrix &matrix, int line, int col) const;
	void lmatrix(stk::Matrix &lmat, int n, int l) const;
	double determinant() const;

	void dump(std::ostream& out) const;

protected:
	int sizei; int sizej;
	double* data;

friend STK_API void Mult(Matrix& C, const Matrix& A, const Matrix& B);
friend STK_API void Add(Matrix& C, const Matrix& A, const Matrix& B);
friend STK_API void Sub(Matrix& C, const Matrix& A, const Matrix& B);

friend STK_API Matrix toMatrix41(const Vector3& P);
friend STK_API Matrix toMatrix31(const Vector3& P);
friend STK_API Vector3 toVector3(const Matrix& M);
};


class STK_API Matrix33 : public Matrix
{
public:
	Matrix33();
	virtual ~Matrix33();
	
	Matrix33(double m00, double m01, double m02,
			 double m10, double m11, double m12,
			 double m20, double m21, double m22);

	Matrix& operator=(const Matrix& Mat);
//optimized inversion for 3x3 Matrix
	virtual bool inverse();
};

STK_API bool isZero(const Matrix& mat);

//C = A*B
STK_API void Mult(Matrix& C, const Matrix& A, const Matrix& B);
//C = A+B
STK_API void Add(Matrix& C, const Matrix& A, const Matrix& B);
//C = A-B
STK_API void Sub(Matrix& C, const Matrix& A, const Matrix& B);

STK_API Matrix toMatrix31(const Vector3& P);
STK_API Matrix toMatrix41(const Vector3& P);
STK_API Vector3 toVector3(const Matrix& M);

STK_API void Transpose(Matrix& A, const Matrix& B);

STK_API void InitIdentity(Matrix& M);
STK_API void InitTranslation(Matrix& M, const Vector3& P);
STK_API void InitRotation(Matrix& M, const Vector3& Axe, double Angle);
STK_API void InitScale(Matrix& M, const Vector3& Scale);

}
