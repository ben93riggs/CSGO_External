#pragma once
#include "Vector.h"
#include "Entity.h"
#include <emmintrin.h>

namespace Math
{
	//not my function
	inline Vector AngleToDirection(Vector angle) {
		angle.x *= float(M_PI / 180);
		angle.y *= float(M_PI / 180);

		float sinYaw = sin(angle.y);
		float cosYaw = cos(angle.y);

		float sinPitch = sin(angle.x);
		float cosPitch = cos(angle.x);

		Vector direction;
		direction.x = cosPitch * cosYaw;
		direction.y = cosPitch * sinYaw;
		direction.z = -sinPitch;

		return direction;
	}

	inline float ToRadians(float degrees)
	{
		return (degrees * M_PI) / 180;
	}

	inline float ToDegrees(float  radians)
	{
		return (radians * 180) / M_PI;
	}

	//scale new angle by percentage of DeltaTime / AimTime.
	inline void SmoothAngle(Vector From, Vector To, float Percent)
	{
		Vector temp;
		Vector VecDelta = From - To;

		VecDelta = VecDelta.NormalizeAngle();

		VecDelta.x *= Percent;
		VecDelta.y *= Percent;
		temp = From - VecDelta;

		SetAngle(temp);
	}

	inline Vector BadCalcAngle(Vector src, Vector dst)
	{
		Vector angles;
		Vector delta = src - dst;
		float hyp = sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
		angles.y = atanf(delta.y / delta.x) * (180.0f / M_PI); // YAW
		angles.x = atan2f(delta.z, hyp) * (180.0f / M_PI); // PITCH
		if (delta.x >= 0.0) { angles.y += 180.0f; }
		return angles;
	}

	inline Vector CalcAngle(register const Vector& src, register const Vector& dst)
	{
		const auto sqrtss = [](float in) {
			__m128 reg = _mm_load_ss(&in);
			return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
		};

		Vector angles;
		Vector delta = src - dst;
		float hyp = sqrtss(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
		angles.x = asinf(delta.z / hyp)		* (180.0f / M_PI);
		angles.y = atanf(delta.y / delta.x)	* (180.0f / M_PI) + !(*reinterpret_cast<DWORD*>(&delta.x) >> 31 & 1) * 180.0f;
		return angles;
	}

	inline float Get3dDistance(Vector myCoords, Vector enemyCoords)
	{
		return sqrt(
			pow(double(enemyCoords.x - myCoords.x), 2.0) +
			pow(double(enemyCoords.y - myCoords.y), 2.0) +
			pow(double(enemyCoords.z - myCoords.z), 2.0));
	}
}
