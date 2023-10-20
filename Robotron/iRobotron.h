#pragma once


class iRobotron
{
public:
	virtual ~iRobotron() {};

	virtual void Update(double deltaTime) = 0;
	virtual void Attack() = 0;
	virtual void setID(int ID) = 0;
	virtual int getID() = 0;
};