/***********************************************************************
 * Source File:
 *    MAIN
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Main entry of program
 ************************************************************************/


#include <cassert>      // for ASSERT
#include <cmath>

#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for Position
#include "velocity.h"   // for Velocity
#include "acceleration.h" // for Acceleration
#include "satellite.h"  // for Satellite
#include "sputnik.h"
#include "orbitSimulator.h"
#include "test.h"

using namespace std;

/*************************************
 * callBack()
 * Called each frame: handle input, update physics, then draw.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   auto* sim = static_cast<OrbitSimulator*>(p);
   sim->input(pUI);
   sim->display();
}

/*********************************
 * main()
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
   testRunner();

   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);

   Interface ui(0, NULL,
      "Sputnik Orbit Simulator",
      ptUpperRight);

   OrbitSimulator sim(ptUpperRight);
   ui.run(callBack, &sim);

   return 0;
}