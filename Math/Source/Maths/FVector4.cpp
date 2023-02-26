#include <utility>
#include <string>
#include <stdexcept>

#include "Maths/FVector4.h"

using namespace Maths;

const FVector4 FVector4::One(1.0f, 1.0f, 1.0f, 1.0f);
const FVector4 FVector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);

FVector4::FVector4(float pX, float pY, float pZ, float pW) : x(pX), y(pY), z(pZ), w(pW)
{
}

FVector4::FVector4(const FVector4& pToCopy) : x(pToCopy.x), y(pToCopy.y), z(pToCopy.z), w(pToCopy.w)
{
}

FVector4 FVector4::operator-() const
{
	return operator*(-1);
}

FVector4 FVector4::operator=(const FVector4& pOther)
{
	x = pOther.x;
	y = pOther.y;
	z = pOther.z;
	w = pOther.w;

	return *this;
}

FVector4 FVector4::operator+(const FVector4& pOther) const
{
	return add(*this, pOther);
}

FVector4& FVector4::operator+=(const FVector4& pOther)
{
	*this = add(*this, pOther);
	return *this;
}

FVector4 FVector4::operator-(const FVector4& pOther) const
{
	return substract(*this, pOther);
}

FVector4& FVector4::operator-=(const FVector4& pOther)
{
	*this = substract(*this, pOther);
	return *this;
}

FVector4 FVector4::operator*(float pScalar) const
{
	return multiply(*this, pScalar);
}

FVector4& FVector4::operator*=(float pScalar)
{
	*this = multiply(*this, pScalar);
	return *this;
}

FVector4 FVector4::operator/(float pScalar) const
{
	return divide(*this, pScalar);
}

FVector4& FVector4::operator/=(float pScalar)
{
	*this = divide(*this, pScalar);
	return *this;
}

bool FVector4::operator==(const FVector4 & pOther)
{
	return x == pOther.x && y == pOther.y && z == pOther.z && w == pOther.w;
}

bool FVector4::operator!=(const FVector4 & pOther)
{
	return !operator==(pOther);
}

float& FVector4::operator[](int pIdx)
{
	if (pIdx >= 4)
		throw std::out_of_range("Invalid index : " + std::to_string(pIdx) + " is out of range");

	if (pIdx == 0)
		return x;
	else if (pIdx == 1)
		return y;
	else if (pIdx == 2)
		return z;
	return w;
}

float FVector4::operator[](int pIdx) const
{
	if (pIdx >= 4)
		throw std::out_of_range("Invalid index : " + std::to_string(pIdx) + " is out of range");

	if (pIdx == 0)
		return x;
	else if (pIdx == 1)
		return y;
	else if (pIdx == 2)
		return z;
	return w;
}

FVector4 FVector4::add(const FVector4& pLeft, const FVector4& pRight)
{
	return FVector4(pLeft.x + pRight.x, pLeft.y + pRight.y, pLeft.z + pRight.z, pLeft.w + pRight.w);
}

FVector4 FVector4::substract(const FVector4& pLeft, const FVector4& pRight)
{
	return FVector4(pLeft.x - pRight.x, pLeft.y - pRight.y, pLeft.z - pRight.z, pLeft.w - pRight.w);
}

FVector4 FVector4::multiply(const FVector4& pTarget, float pScalar)
{
	return FVector4(pTarget.x * pScalar, pTarget.y * pScalar, pTarget.z * pScalar, pTarget.w * pScalar);
}

FVector4 FVector4::divide(const FVector4& pLeft, float pScalar)
{
	FVector4 result(pLeft);

	if (pScalar == 0)
		throw std::logic_error("Division by 0");

	result.x /= pScalar;
	result.y /= pScalar;
	result.z /= pScalar;
	result.w /= pScalar;

	return result;
}

float FVector4::length(const FVector4& pTarget)
{
	return sqrtf(pTarget.x * pTarget.x + pTarget.y * pTarget.y + pTarget.z * pTarget.z + pTarget.w * pTarget.w);
}

float Maths::FVector4::length()
{
	return length(*this);
}

float FVector4::dot(const FVector4& pLeft, const FVector4& pRight)
{
	return pLeft.x * pRight.x + pLeft.y * pRight.y + pLeft.z * pRight.z + pLeft.w * pRight.w;
}

float Maths::FVector4::dot(const FVector4& pRight)
{
	return dot(*this, pRight);
}

FVector4 FVector4::normalize(const FVector4& pTarget)
{
	float aLength = length(pTarget);

	if (aLength > 0.0f)
	{
		float targetLength = 1.0f / aLength;

		return FVector4(pTarget.x * targetLength, pTarget.y * targetLength, pTarget.z * targetLength, pTarget.w * targetLength);
	}

	return FVector4::Zero;
}

FVector4 Maths::FVector4::normalize()
{
	return normalize(*this);
}

FVector4 FVector4::lerp(const FVector4& pA, const FVector4& pB, float pT)
{
	return (pA + (pB - pA) * pT);
}