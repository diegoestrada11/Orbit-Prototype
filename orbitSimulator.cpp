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
	// Earth center position
	Position earthCenter(0.0, 0.0);

	// Sputnik (Geostationary)
	sputnik.setPosition(Position(0.0, 42164000.0));
	sputnik.setVelocity(Velocity(-3100.0, 0.0));

	// GPS (~20200 km altitude)
	gps.setPosition(Position(0.0, EARTH_RADIUS + 20200000.0));
	gps.setVelocity(Velocity(-3870.0, 0.0));

	// Hubble (~569 km altitude)
	hubble.setPosition(Position(0.0, EARTH_RADIUS + 569000.0));
	hubble.setVelocity(Velocity(-7700.0, 0.0));

	// Starlink (~550 km altitude)
	starlink.setPosition(Position(0.0, EARTH_RADIUS + 550000.0));
	starlink.setVelocity(Velocity(-7750.0, 0.0));

	// ISS (~408 km altitude)
	iss.setPosition(Position(0.0, EARTH_RADIUS + 408000.0));
	iss.setVelocity(Velocity(-7700.0, 0.0));
}

void OrbitSimulator::input(const Interface* pUI)
{
   // No user controls yet
   (void)pUI;
}

void OrbitSimulator::display()
{
	// Time step
	sputnik.update(DT);
	gps.update(DT);
	hubble.update(DT);
	starlink.update(DT);
	iss.update(DT);

	Position center(0.0, 0.0);
	ogstream gout(center);

	// Draw Earth
	gout.drawEarth(center, 0.0);

	// Draw all satellites
	sputnik.draw();
	gps.draw();
	hubble.draw();
	starlink.draw();
	iss.draw();
}
