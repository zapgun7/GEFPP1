#include "cGraphicsMain.h"


int main(int argc, char** argv)
{
	cGraphicsMain graphics;
	graphics.Initialize();

	while (graphics.Update() == 0)
	{
		// Running...
	}
	graphics.Destroy();

	return 0;
}