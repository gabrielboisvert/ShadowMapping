#pragma once


namespace Maths
{

	struct FVector4
	{
		static const FVector4 One;
		static const FVector4 Zero;

		float x;
		float y;
		float z;
		float w;

		FVector4(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f, float pW = 0.0f);

		FVector4(const FVector4& pToCopy);

		FVector4(FVector4&& pToMove) noexcept = default;

		FVector4 operator-() const;

		FVector4 operator=(const FVector4& pOther);

		FVector4 operator+(const FVector4& pOther) const;

		FVector4& operator+=(const FVector4& pOther);

		FVector4 operator-(const FVector4& pOther) const;

		FVector4& operator-=(const FVector4& pOther);

		FVector4 operator*(float pScalar) const;

		FVector4& operator*=(float pScalar);

		FVector4 operator/(float pScalar) const;

		FVector4& operator/=(float pScalar);

		bool operator==(const FVector4& pOther);

		bool operator!=(const FVector4& pOther);

		float& operator[](int pIdx);

		float operator[](int pIdx) const;

		static FVector4 add(const FVector4& pLeft, const FVector4& pRight);

		static FVector4 substract(const FVector4& pLeft, const FVector4& pRight);

		static FVector4 multiply(const FVector4& pTarget, float pScalar);

		static FVector4 divide(const FVector4& pLeft, float pScalar);

		static float length(const FVector4& pTarget);

		float length();

		static float dot(const FVector4& pLeft, const FVector4& pRight);

		float dot(const FVector4& pRight);

		static FVector4 normalize(const FVector4& pTarget);

		FVector4 normalize();

		static FVector4 lerp(const FVector4& pA, const FVector4& pB, float pT);
	};
}