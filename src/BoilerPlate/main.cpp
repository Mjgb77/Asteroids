#if _MSC_VER && _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

// C++ STL
#include <cassert>
#include <iostream>

// 
#include "App.hpp"
#include "MathUtilities.h"

const int WIDTH = 1136;
const int HEIGHT = 640;

int main(int argc, char* argv[])
{
#if _MSC_VER && _DEBUG
	// https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx
	// This will help you detect leaks when using Visual C++
	// Uncomment this line to start getting reports!
	assert(_CrtCheckMemory());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//TEST MATHUTILITES CLASS

	cout << "Is 64 power of two?:		" << MathUtilities::isPowerOfTwo(16) << endl;
	cout << "Is 20 power of two?:		" << MathUtilities::isPowerOfTwo(20) << endl;
	cout << "Max of {-9.3, 4.0, 7.1, -5.2}:	" << MathUtilities::getMax(-9.3, 4.0, 7.1, -5.2) << endl;
	cout << "Interpolate 3.4994 to [5, 15]:	" << MathUtilities::interpolate(5, 15, 0.3494) << endl;
	cout << "Nearest even int to 2.7:	" << MathUtilities::nearestEven(2.7) << endl;

	system("PAUSE");
	
	//END TEST

	// Create Game Object
	//
	Engine::App* app = new Engine::App("Boiler Plate!", WIDTH, HEIGHT);

	// Initialize game
	//
	if(!app->Init())
	{
		std::cout << "App Init error!\n";
		return -1;
	}

	// Execute game
	//
	app->Execute();

	// Delete game object
	//
	delete app;

	return 0;
}