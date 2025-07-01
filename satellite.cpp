/***********************************************************************
 * Source File:
 *    Satellite
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "satellite.h"

// Constructor: forward to Body base class
Satellite::Satellite(const Position& pos, const Velocity& vel, double radius)
   : Body(pos, vel, radius)
{
}

// On collision: expire this satellite so the simulator will remove it.
void Satellite::onCollision(Body* /*other*/) noexcept
{
   // Mark this satellite as expired
   expire();
}
