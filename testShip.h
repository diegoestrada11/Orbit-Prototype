/***********************************************************************
* Header File:
*    Test Ship
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Ship
************************************************************************/

#pragma once

#include "ship.h"
#include "projectile.h"
#include "unitTest.h"

/******************************************************************************
 * TEST Ship Class
 ******************************************************************************/
class TestShip : public UnitTest {
public:
   void run();

private:
   void test_constructor_initialValues();    // starting pos, vel, angle
   void test_rotateLeftRight();              // rotation changes angle
   void test_startStopThrust();              // thrust toggles flag
   void test_fireProjectile_velocityOffset(); // projectile velocity = parent + kick
   void test_fireProjectile_positionOffset(); // projectile spawns 19 px ahead
   void test_draw_invokesDraw();             // draw() calls drawShip()
};