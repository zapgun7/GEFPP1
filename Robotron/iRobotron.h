#pragma once


class iRobotron
{
public:
	virtual ~iRobotron() {};

	virtual void Update(double deltaTime) = 0;
	virtual void Attack() = 0;
	virtual void Animate() = 0;
};