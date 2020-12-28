#ifndef NUMERICALSOLUTION_H
#define NUMERICALSOLUTION_H

#include "gameObjects/GameObject.h"
#include "rowMath/rowMath.h"

namespace row
{

	static row::vector3 CalcuateAcceleration(GameObject* body1, GameObject* body2 , float scale = 1)
	{
		row::vector3 acceleration;
		row::vector3 directionalVector;
		row::vector3 pos1 = body1->GetPosition() * scale;
		row::vector3 pos2 = body2->GetPosition() * scale;
		//Calculate the direction of the force
		row::vector3 dir = pos2 - pos1;
		//Calculate the distance
		float distance = (float)dir.Magnitude();
		//r^3 for the calculation
		distance = distance * distance * distance;
		//Mass of the other body
		double mass = body2->GetMass();

		acceleration.x = ((GRAVITATIONAL_CONSTANT * mass) / distance);
		acceleration.x *= dir.x;
		acceleration.y = ((GRAVITATIONAL_CONSTANT * mass) / distance);
		acceleration.y *= dir.y;
		acceleration.z = ((GRAVITATIONAL_CONSTANT * mass) / distance);
		acceleration.z *= dir.z;
		return acceleration;
	}

	static row::vector3 CalculateBodyAccelerationImprovedEuler(GameObject* body1, GameObject* body2 , float scale = 1)
	{
		row::vector3 nextAcceleration = CalcuateAcceleration(body1, body2, scale);
		row::vector3 averageAcceleration = (nextAcceleration + body1->GetPrevAcceleration()) * 0.5f;
		body1->SetPrevAcceleration(nextAcceleration);
		return averageAcceleration;
	}

	static row::vector3 rkPartialStep(row::vector3 vector, row::vector3 dVector, float timeStep, float rkScale)
	{
		return vector + dVector * timeStep * rkScale;
	}

	static row::vector3 CalculateBodyAccelerationRK4(GameObject* body1, GameObject* body2,float timeStep, float scale = 1)
	{
		row::vector3 acceleration;
		row::vector3 k1, k2, k3, k4;
		row::vector3 directionalVector;
		row::vector3 tempVel;
		row::vector3 tempPos = body1->GetPosition() * scale;
		row::vector3 externalPos = body2->GetPosition() * scale;
		double temp;
		//Calculate the direction of the force
		row::vector3 dir = externalPos - tempPos;
		//Calculate the distance
		float distance = (float)dir.Magnitude();
		//r^3 for the calculation
		distance = distance * distance * distance;
		//Mass of the other body
		double mass = body2->GetMass();

		temp = ((GRAVITATIONAL_CONSTANT * mass) / distance);
		k1 = dir * temp;

		tempVel = body1->GetVelocity();
		tempVel = rkPartialStep(tempVel, k1, timeStep,0.5);
		tempPos = rkPartialStep(tempPos, tempVel, timeStep, 0.5);
		dir = externalPos - tempPos;
		distance = (float)dir.Magnitude();
		distance = distance * distance * distance;
		temp = ((GRAVITATIONAL_CONSTANT * mass) / distance);
		k2 = dir * temp;

		tempVel = rkPartialStep(tempVel, k2, timeStep, 0.5);
		tempPos = rkPartialStep(tempPos, tempVel, timeStep, 0.5);
		dir = externalPos - tempPos;
		distance = (float)dir.Magnitude();
		distance = distance * distance * distance;

		temp = ((GRAVITATIONAL_CONSTANT * mass) / distance);
		k3 = dir * temp;

		tempVel = rkPartialStep(tempVel, k3, timeStep, 1);
		tempPos = rkPartialStep(tempPos, tempVel, timeStep, 1);
		dir = externalPos - tempPos;
		distance = (float)dir.Magnitude();
		distance = distance * distance * distance;

		temp = ((GRAVITATIONAL_CONSTANT * mass) / distance);
		k4 = dir * temp;

		acceleration = (k1 + (k2 * 2) + (k3 * 2) + k4) / 6;
		return acceleration;
	}

	static row::vector3 CalculateBodyVelocity(row::vector3 acc, row::vector3 vel, float dt)
	{
		return (vel + acc * dt);
	}

	static row::vector3 CalculateBodyVelocity(GameObject body1, float dt)
	{
		return (body1.GetVelocity() + body1.GetAcceleration() * dt);
	}

	static row::vector3 CalculateBodyPosition(GameObject body1, float dt, float scale = 1)
	{
		row::vector3 posdelta = (body1.GetVelocity() * dt);
		posdelta = (posdelta / scale) + body1.GetPosition();
		return posdelta;
	}
	

	static void UpdateBodyImprovedEuler(GameObject* body1, GameObject* body2, float timeStep, float scale = 1)
	{
		row::vector3 avgAcceleration = CalculateBodyAccelerationImprovedEuler(body1, body2, scale);
		body1->SetAcceleration(avgAcceleration);
		row::vector3 newVelocity = CalculateBodyVelocity(*body1, timeStep);
		body1->SetVelocity(newVelocity);
		row::vector3 newPosition = CalculateBodyPosition(*body1, timeStep,scale);
		body1->SetPosition(newPosition);
	}

	static void UpdateBodyEuler(GameObject* body1, GameObject* body2, float timeStep, float scale = 1)
	{
		body1->SetAcceleration(CalcuateAcceleration(body1, body2, scale));
		row::vector3 newVelocity = CalculateBodyVelocity(*body1, timeStep);
		body1->SetVelocity(newVelocity);
		row::vector3 newPosition = CalculateBodyPosition(*body1, timeStep, scale);
		body1->SetPosition(newPosition);
	}

}

#endif