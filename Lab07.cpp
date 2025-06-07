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
#include <cmath>

#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for Position
#include "velocity.h"   // for Velocity
#include "acceleration.h" // for Acceleration
#include "test.h"

using namespace std;

static constexpr double PI = 3.14159265358979323846;
static constexpr double HOURS_PER_DAY = 24.0;
static constexpr double MINUTES_PER_HOUR = 60.0;
static constexpr double SIMULATOR_FPS = 30.0;
static constexpr double TIME_DILATION = (HOURS_PER_DAY * MINUTES_PER_HOUR * 60.0) / MINUTES_PER_HOUR;
static constexpr double DT = TIME_DILATION / SIMULATOR_FPS;
static constexpr double EARTH_RADIUS = 6378000.0;

/*************************************************************************
 * Demo
 * Holds all positions and state for a frame-by-frame orbit sim
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight)
      : ptUpperRight(ptUpperRight)
   {
      // Random initial placement of various satellites
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

      // Initial angles and animation phase
      angleShip = 0.0;
      angleEarth = 0.0;
      phaseStar = 0;

      // Geostationary orbit initial conditions
      ptGEO.setMeters(0.0, 42164000.0);
      velocityGEO.setDX(-3100.0);
      velocityGEO.setDY(0.0);
   }

   // Positions of all objects
   Position ptHubble;
   Position ptSputnik;
   Position ptStarlink;
   Position ptCrewDragon;
   Position ptShip;
   Position ptGPS;
   Position ptStar;
   Position ptUpperRight;
   Position ptGEO;

   unsigned char phaseStar;    // animation frame for star flicker
   double angleShip;           // rotation for ships/satellites
   double angleEarth;          // rotation of Earth texture
   Velocity velocityGEO;       // current GEO satellite velocity
};

/*************************************
 * callBack()
 * Called each frame: handle input, update physics, then draw.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Demo* pDemo = static_cast<Demo*>(p);

   // 1) Handle user input (move the ship)
   if (pUI->isUp())    pDemo->ptShip.addPixelsY(1.0);
   if (pUI->isDown())  pDemo->ptShip.addPixelsY(-1.0);
   if (pUI->isLeft())  pDemo->ptShip.addPixelsX(-1.0);
   if (pUI->isRight()) pDemo->ptShip.addPixelsX(1.0);

   // 2) Update Earth rotation (1 sim-day = 60s real @30fps → 1800 frames)
   pDemo->angleEarth += 2 * PI / (SIMULATOR_FPS * 60.0);

   // 3) Gravity-based centripetal acceleration for GEO satellite
   double x = pDemo->ptGEO.getMetersX();
   double y = pDemo->ptGEO.getMetersY();
   double r = sqrt(x * x + y * y);
   if (r > EARTH_RADIUS)
   {
      double ux = -x / r;
      double uy = -y / r;
      double a_mag = 9.81 * (EARTH_RADIUS * EARTH_RADIUS) / (r * r);
      Acceleration a;
      a.setDDX(ux * a_mag);
      a.setDDY(uy * a_mag);
      pDemo->velocityGEO.add(a, DT);
   }

   // 4) Advance GEO position by its velocity
   pDemo->ptGEO.addMetersX(pDemo->velocityGEO.getDX() * DT);
   pDemo->ptGEO.addMetersY(pDemo->velocityGEO.getDY() * DT);

   // 5) Advance other animations
   pDemo->angleShip += 0.02;
   pDemo->phaseStar++;

   // 6) Draw everything
   Position pt;
   ogstream gout(pt);

   gout.drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);
   gout.drawHubble(pDemo->ptHubble, pDemo->angleShip);
   gout.drawSputnik(pDemo->ptSputnik, pDemo->angleShip);
   gout.drawStarlink(pDemo->ptStarlink, pDemo->angleShip);
   gout.drawShip(pDemo->ptShip, pDemo->angleShip, pUI->isSpace());
   gout.drawGPS(pDemo->ptGPS, pDemo->angleShip);

   // Draw parts offset from each object
   pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
   gout.drawCrewDragonRight(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
   gout.drawHubbleLeft(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
   gout.drawGPSCenter(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
   gout.drawStarlinkArray(pt, pDemo->angleShip);

   // Fragments
   pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);

   // Star flicker
   gout.drawStar(pDemo->ptStar, pDemo->phaseStar);

   // Draw Earth at center
   pt.setMeters(0.0, 0.0);
   gout.drawEarth(pt, pDemo->angleEarth);

   // GEO satellite
   gout.drawHubble(pDemo->ptGEO, 0.0);
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
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);

   Interface ui(0, NULL,
      "Demo",
      ptUpperRight);

   Demo demo(ptUpperRight);
   ui.run(callBack, &demo);

   return 0;
}