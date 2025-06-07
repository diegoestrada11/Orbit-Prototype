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
#include "velocity.h"   // for VELOCITY
#include "acceleration.h" // for ACCELERATION
#include "test.h"
#include <cmath>
using namespace std;

<<<<<<< Updated upstream
static constexpr double PI = 3.14159265358979323846;
=======
static constexpr double HOURS_PER_DAY = 24.0;
static constexpr double MINUTES_PER_HOUR = 60.0;
static constexpr double SIMULATOR_FPS = 30.0;

static constexpr double TIME_DILATION =
   (HOURS_PER_DAY * MINUTES_PER_HOUR * 60.0) / MINUTES_PER_HOUR;

static constexpr double DT = TIME_DILATION / SIMULATOR_FPS;

static constexpr double EARTH_RADIUS = 6378000.0;
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
=======
      ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      angleShip = 0.0;
      angleEarth = 0.0;
      phaseStar = 0;

      ptGEO.setMeters(0.0, 42164000.0);

      velocityGEO.setDX(-3100.0);
      velocityGEO.setDY(0.0);
>>>>>>> Stashed changes
   }

   Position ptUpperRight;
<<<<<<< Updated upstream
   double    orbitRadiusPixels;
   double    angleEarth;
=======
   Position ptGEO;

   unsigned char phaseStar;

   double angleShip;
   double angleEarth;

   Velocity velocityGEO;
   
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
   // Advance the orbit angle
=======
   // accept input

   // move by a little
   if (pUI->isUp())
      pDemo->ptShip.addPixelsY(1.0);
   if (pUI->isDown())
      pDemo->ptShip.addPixelsY(-1.0);
   if (pUI->isLeft())
      pDemo->ptShip.addPixelsX(-1.0);
   if (pUI->isRight())
      pDemo->ptShip.addPixelsX(1.0);

   // perform all the game logic
   pDemo->angleEarth += 2 * M_PI / (SIMULATOR_FPS * 60.0);

   // 2) Compute gravity on GEO sat:
   double x = pDemo->ptGEO.getMetersX();
   double y = pDemo->ptGEO.getMetersY();
   double r = sqrt(x * x + y * y);
   if (r > EARTH_RADIUS)      // only if above surface
   {
      double ux = -x / r, uy = -y / r;
      // choose either GM/r≤ or g0 * (Re≤/r≤):
      double a_mag = 9.81 * (EARTH_RADIUS * EARTH_RADIUS) / (r * r);

      Acceleration a;
      a.setDDX(ux * a_mag);
      a.setDDY(uy * a_mag);
      pDemo->velocityGEO.add(a, DT);
   }
   else
   {
      // burned up!  handle removalÖ
   }

   pDemo->ptGEO.addMetersX(pDemo->velocityGEO.getDX() * DT);
   pDemo->ptGEO.addMetersY(pDemo->velocityGEO.getDY() * DT);


   // rotate the earth
>>>>>>> Stashed changes
   pDemo->angleEarth += 0.01;
   if (pDemo->angleEarth > 2 * PI)
      pDemo->angleEarth -= 2 * PI;

<<<<<<< Updated upstream
   // Compute satellite position
   Position satPos = rotate(
      Position(0.0, 0.0),
      pDemo->orbitRadiusPixels,
      0.0,
      pDemo->angleEarth
   );
=======
   // draw everything
>>>>>>> Stashed changes

   // Draw
   Position scratch;
   ogstream gout(scratch);

   gout.drawSputnik(satPos, 0.0);

<<<<<<< Updated upstream
   scratch.setMeters(0.0, 0.0);
   gout.drawEarth(scratch, pDemo->angleEarth);
=======
   // draw parts
   pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
   gout.drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
   pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
   gout.drawHubbleLeft(pt, pDemo->angleShip);      // notice only two parameters are set
   pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
   gout.drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
   pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
   gout.drawStarlinkArray(pt, pDemo->angleShip);   // notice only two parameters are set

   // draw fragments
   pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);

   // draw a single star
   gout.drawStar(pDemo->ptStar, pDemo->phaseStar);

   // draw the earth
   pt.setMeters(0.0, 0.0);
   gout.drawEarth(pt, pDemo->angleEarth);

   // draw the GEO satellite
   gout.drawHubble(pDemo->ptGEO, 0.0);
>>>>>>> Stashed changes
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
      "Single‚ÄêSatellite Orbit Simulator",
      ptUpperRight);

   Demo demo(ptUpperRight);
   ui.run(callBack, &demo);

   return 0;
}
