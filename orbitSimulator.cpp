/***********************************************************************
 * Source File:
 *    ORBIT SIMULATOR
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "orbitSimulator.h"
#include <cmath>

static constexpr double SIMULATOR_FPS = 30.0;
static constexpr double HOURS_PER_DAY = 24.0;
static constexpr double MINUTES_PER_HOUR = 60.0;
static constexpr double TIME_DILATION = (HOURS_PER_DAY * MINUTES_PER_HOUR * 60.0) / MINUTES_PER_HOUR;
static constexpr double DT = TIME_DILATION / SIMULATOR_FPS;
static constexpr double EARTH_RADIUS = 6.378e6;  // meters

OrbitSimulator::OrbitSimulator(const Position& bounds)
   : bounds(bounds)
{
   // Geostationary orbit: radius = 42164000 m from Earth's center
   const double geoRadius = 42164000.0;
   // Initial position at (0, geoRadius)
   sputnik.setPosition(Position(0.0, geoRadius));
   // Geostationary orbital speed ~3100 m/s, moving westward (-x direction)
   sputnik.setVelocity(Velocity(-3100.0, 0.0));
}

void OrbitSimulator::input(const Interface* pUI)
{
   // No user controls yet
   (void)pUI;
}

void OrbitSimulator::display()
{
   // Advance physics and orientation
   sputnik.update(DT);

   // Draw Earth at center
   Position center(0.0, 0.0);
   ogstream gout(center);
   gout.drawEarth(center, 0.0);

   // Draw Sputnik
   sputnik.draw();
}
