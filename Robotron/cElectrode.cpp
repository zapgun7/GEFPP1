#include "cElectrode.h"
// Stationary enemy, only damages the player if the player themselves walk into this

void cElectrode::Action()
{

}

void cElectrode::Update(double deltaTime)
{
	// if time since last animate is less than a value, call animate
}

void cElectrode::Animate()
{
	// Cycles to the next model
	// Electrode is stationary, so don't need to worry about changing the model based on its current action
}
