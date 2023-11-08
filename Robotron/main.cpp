#include "cGraphicsMain.h"
#include "cArena.h"
#include "time.h"


int main(int argc, char** argv)
{
	srand(time(NULL)); // makes random great again (MRaGA)
	cGraphicsMain* graphics = cGraphicsMain::getGraphicsMain();// This initializes it if not yet made 
	cArena* theArena = cArena::getArena();

	
	theArena->Initialize();
	while (graphics->Update() == 0)
	{
		// Running...
		theArena->Update();
	}
	graphics->Destroy();

	return 0;
}