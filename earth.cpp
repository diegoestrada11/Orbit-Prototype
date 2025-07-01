/***********************************************************************
* Source File:
*    Earth
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
************************************************************************/

#include "earth.h"
#include "uiDraw.h"
#include <cmath>

// Time dilation & frame rate constants
static constexpr double FRAME_RATE = 30.0;
static constexpr double TIME_DILATION = 24.0 * 60.0;   // 1440x real speed
static constexpr double SECONDS_PER_DAY = 86400.0;

// Earth rotation per frame: -(2?/frameRate)*(td/secondsDay)
static constexpr double EARTH_ROT_PER_FRAME =
-(2.0 * M_PI / FRAME_RATE) * (TIME_DILATION / SECONDS_PER_DAY);

static constexpr double EARTH_RADIUS_M = 6378 * 1000;
Earth::Earth()
   : Body(
      // Position at center (0,0) in meters
      Position(0.0, 0.0),
      // No movement
      Velocity(0.0, 0.0),
      // Real-world radius in meters
      EARTH_RADIUS_M
   )
{
   // Start with zero rotation
   setAngle(Angle(0.0));
}

void Earth::update(double /*dt*/) {
   // rotate Earth in place each frame
   rotateBy(EARTH_ROT_PER_FRAME);
}

void Earth::draw() const {
   // Draw centered at origin
   Position center;
   center.setPixelsX(0.0);
   center.setPixelsY(0.0);

   ogstream gout(center);
   gout.drawEarth(center, getAngle().toRadians());
}