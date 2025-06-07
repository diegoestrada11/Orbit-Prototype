/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "test.h"
#include <cmath>
using namespace std;

static constexpr double PI = 3.14159265358979323846;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight)
      : ptUpperRight(ptUpperRight),
      orbitRadiusPixels(ptUpperRight.getPixelsX() * 0.4),
      angleEarth(0.0)
   {
   }

   Position ptUpperRight;
   double    orbitRadiusPixels;
   double    angleEarth;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Demo* pDemo = static_cast<Demo*>(p);

   // Advance the orbit angle
   pDemo->angleEarth += 0.01;
   if (pDemo->angleEarth > 2 * PI)
      pDemo->angleEarth -= 2 * PI;

   // Compute satellite position
   Position satPos = rotate(
      Position(0.0, 0.0),
      pDemo->orbitRadiusPixels,
      0.0,
      pDemo->angleEarth
   );

   // Draw
   Position scratch;
   ogstream gout(scratch);

   gout.drawSputnik(satPos, 0.0);

   scratch.setMeters(0.0, 0.0);
   gout.drawEarth(scratch, pDemo->angleEarth);
}

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   testRunner();

   Position ptUpperRight;
   ptUpperRight.setPixelsX(500.0);
   ptUpperRight.setPixelsY(500.0);

   Interface ui(argc, argv,
      "Single‐Satellite Orbit Simulator",
      ptUpperRight);

   Demo demo(ptUpperRight);
   ui.run(callBack, &demo);

   return 0;
}
