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
#include "testBody.h"
#include "testSatellite.h"
#include "testSputnik.h"
#include "testAngle.h"
#include "testAcceleration.h"

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
   TestSatellite().run();
   TestSputnik().run();
   TestBody().run();
   TestAcceleration().run();
}
