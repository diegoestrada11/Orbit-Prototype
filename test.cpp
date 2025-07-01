/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testVelocity.h"
#include "testAngle.h"
#include "testAcceleration.h"
#include "testBody.h"
#include "testSatellite.h"
#include "testSputnik.h"
#include "testGPS.h"
#include "testHubble.h"
#include "testCrewDragon.h"
#include "testStarLink.h"
#include "testShip.h"
#include "testEarth.h"

#ifdef _WIN32
#include <windows.h>
#include <iostream>
using namespace std;
#endif

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
#ifdef _WIN32
   AllocConsole();
   FILE* stream;
   errno_t err;
   err = freopen_s(&stream, "CONOUT$", "a", stdout);
#endif // _WIN32

   TestPosition().run();
   TestVelocity().run();
   TestAngle().run();
   TestAcceleration().run();
   TestBody().run();
   TestSatellite().run();
   TestSputnik().run();
   TestGPS().run();
   TestHubble().run();
   TestCrewDragon().run();
   TestStarlink().run();
   TestShip().run();
   TestEarth().run();
}
