#pragma once

class iProjectile
{
	~iProjectile() {};

	virtual void Update() = 0;
	virtual void Animate() = 0;
};