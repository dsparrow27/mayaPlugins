#include "utils.h"


using namespace utils;
	MTransformationMatrix::RotationOrder utils::rotationOrderByIndex(int rotOrder)
	{
		MTransformationMatrix::RotationOrder rotationOrder;

		switch (rotOrder)
		{
		case(MTransformationMatrix::RotationOrder::kXZY):
			rotationOrder = MTransformationMatrix::RotationOrder::kXZY;
			break;
		case(MTransformationMatrix::RotationOrder::kYXZ) :
			rotationOrder = MTransformationMatrix::RotationOrder::kYXZ;
			break;
		case(MTransformationMatrix::RotationOrder::kYZX) :
			rotationOrder = MTransformationMatrix::RotationOrder::kYZX;
			break;
		case(MTransformationMatrix::RotationOrder::kZXY) :
			rotationOrder = MTransformationMatrix::RotationOrder::kZXY;
			break;
		case(MTransformationMatrix::RotationOrder::kZYX) :
			rotationOrder = MTransformationMatrix::RotationOrder::kZYX;
			break;
		default:
			rotationOrder = MTransformationMatrix::RotationOrder::kXYZ;
			break;
		}
		return rotationOrder;
	}

	float utils::remap(float value, float oldMin, float oldMax, float newMin, float newMax)
	{
		return (((value - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
	}

	bool utils::almostEqual(float x, float y, int tailCount)
	{
		return fabsf(x - y) < std::numeric_limits<float>::epsilon() * fabsf(x + y) * tailCount 
			|| fabsf(x - y) < std::numeric_limits<float>::min();
	}
	float utils::lerp(float goal, float current, float blend)
	{
		return (goal * blend) + ((1.0 - blend) * current);
	}

	MVector utils::lerp(MVector goal, MVector current, float blend)
	{
		return (goal * blend) + ((1.0 - blend) * current);
	}
	
	double utils::dot(MQuaternion qa, MQuaternion qb)
	{
		return qa.w * qb.w + qa.x*qb.x + qa.y*qb.y + qa.z*qb.z;
	}
	MQuaternion utils::slerp(MQuaternion qa, MQuaternion qb, float blend)
	{
		MQuaternion qc;
		double dot = utils::dot(qa, qb);
		if (abs(dot >= 1.0f))
		{
			qc.w = qa.w;
			qc.x = qa.x;
			qc.y = qa.y;
			qc.z = qa.z;
			return qc;
		}
		double halfTheta = acos(dot);
		double sinhalfTheta = sqrt(1.0 - dot* dot);
		if (utils::almostEqual(fabsf((float)sinhalfTheta), 0.0f, 2))
		{
			qc.w = (qa.w * 0.5 + qb.w * 0.5);
			qc.x = (qa.x * 0.5 + qb.x * 0.5);
			qc.y = (qa.y * 0.5 + qb.y * 0.5);
			qc.z = (qa.z * 0.5 + qb.z * 0.5);
			return qc;
		}
		double ratioA = sin((1.0 - (float)blend) * halfTheta) / sinhalfTheta;
		double ratioB = sin((float)blend * halfTheta) / sinhalfTheta;
		
		qc.w = (qa.w * ratioA + qb.w * ratioB);
		qc.x = (qa.x * ratioA + qb.x * ratioB);
		qc.y = (qa.y * ratioA + qb.y * ratioB);
		qc.z = (qa.z * ratioA + qb.z * ratioB);
		return qc;

	}
	MQuaternion utils::aimVector(MVector sourcePosition, MVector targetPosition, MVector aimVector, MVector upVector)
	{
		MVector aimDirection = targetPosition - sourcePosition;
		MVector eyeU = aimDirection.normal();
		MVector eyeW = eyeU ^ upVector;
		MVector eyeV = eyeW ^ eyeU;
		MQuaternion quatU = MQuaternion(aimVector, eyeU);

		MVector upRotated = upVector.rotateBy(quatU);
		double angle = acos(upRotated * eyeV);
		MQuaternion quatV = MQuaternion(angle, eyeU);
		if (!eyeV.isEquivalent(upRotated.rotateBy(quatV), 1.0e-5))
		{
			angle = (2 * M_PI) - angle;
			quatV = MQuaternion(angle, eyeU);
		}
		quatU *= quatV;

		return quatU;
	}
