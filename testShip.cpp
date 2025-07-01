/***********************************************************************
 * Source File:
 *    Test Ship
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for TestShip
 ************************************************************************/

#include "testShip.h"
#include "projectile.h"
#include "position.h"
#include <cmath>

/*****************************************************************
 * SPY SHIP CLASS
 ****************************************************************/
class SpyShip : public Ship {
public:
   SpyShip() : drawn(false) {}
   void draw() const override {
      const_cast<SpyShip*>(this)->drawn = true;
      Ship::draw();
   }
   mutable bool drawn;
};

/*****************************************************************
 * TESTABLE SHIP CLASS
 ****************************************************************/
class TestableShip : public Ship {
public:
   using Ship::computeAcceleration;
};

void TestShip::run() 
{
   test_constructor_initialValues();
   test_rotateLeftRight();
   test_startStopThrust();
   test_fireProjectile_velocityOffset();
   test_fireProjectile_positionOffset();
   test_draw_invokesDraw();
   report("Ship");
}

/*****************************************************************
 * TEST CONSTRUCTOR INITIAL VALUES
 * verify ship starts at known initial pixel coords and velocity, angle 270°
 ****************************************************************/
void TestShip::test_constructor_initialValues()
{
   // Setup & Exercise
   Ship s;
   // Verify
   Position p = s.getPosition();
   Velocity v = s.getVelocity();
   double ang = s.getAngle().toDegrees();
   assertEquals(p.getPixelsX(), -450.0);
   assertEquals(p.getPixelsY(), 450.0);
   assertEquals(v.getDx(), 0.0);
   assertEquals(v.getDy(), -2000.0);
   assertEquals(ang, 270.0);
   // Teardown
}

/*****************************************************************
 * TEST ROTATE LEFT RIGHT
 * verify rotation changes angle by ±TURN_RAD
 ****************************************************************/
void TestShip::test_rotateLeftRight()
{
   // Setup
   Ship s;
   double orig = s.getAngle().toRadians();
   // Exercise
   s.rotateRight();
   double r1 = s.getAngle().toRadians();
   s.rotateLeft();
   s.rotateLeft();
   double r2 = s.getAngle().toRadians();
   // Verify
   assertEquals(r1, orig + 0.1); // right = orig + TURN
   assertEquals(r2, orig - 0.1); // left twice = orig - TURN
   // Teardown
}

/*****************************************************************
 * TEST START STOP THRUST
 * verify toggles mThrusting
 ****************************************************************/
void TestShip::test_startStopThrust() {
   // Setup
   TestableShip s;
   // Exercise & Verify
   // cast to access protected
   assertUnit(dynamic_cast<const TestableShip&>(s).computeAcceleration().getDDX() != 0.0);
   s.startThrust();
   auto a = s.computeAcceleration();
   assertUnit(fabs(a.getDDX()) > 0.0 || std::fabs(a.getDDY()) > 0.0); // magnitude >= THRUST_ACC
   s.stopThrust();
   // Teardown
}

/*****************************************************************
 * TEST FIRE PROJECTILE
 * verify projectile velocity = ship vel + kick
 ****************************************************************/
void TestShip::test_fireProjectile_velocityOffset() {
   // Setup
   Ship s;
   // Ensure no thrust, angle 270° => downwards
   Projectile* p = s.fireProjectile();
   // Exercise
   Velocity pv = p->getVelocity();
   Velocity sv = s.getVelocity();
   // The kick is PROJECTILE_KICK in direction of angle
   double theta = s.getAngle().toRadians();
   double expectedDx = sv.getDx() + sin(theta) * 9000;
   double expectedDy = sv.getDy() + cos(theta) * 9000;
   // Verify
   assertEquals(pv.getDx(), expectedDx);
   assertEquals(pv.getDy(), expectedDy);
   // Teardown
   delete p;
}

/*****************************************************************
 * TEST FIRE PROJECTILE POSITION OFFSET
 * verify projectile spawns PROJECTILE_OFFSET px ahead
 ****************************************************************/
void TestShip::test_fireProjectile_positionOffset() {
   // Setup
   Ship s;
   Position sp = s.getPosition();
   double zoom = sp.getZoom();
   Projectile* p = s.fireProjectile();
   // Exercise
   Position pp = p->getPosition();
   double dx = pp.getMetersX() - sp.getMetersX();
   double dy = pp.getMetersY() - sp.getMetersY();
   double dist = hypot(dx, dy);
   double expected = 19 * zoom;
   // Verify
   assertUnit(fabs(dist - expected) < 1e-6);
   // Teardown
   delete p;
}

/*****************************************************************
 * TEST DRAW INVOKES DRAW
 * verify draw() dispatches to drawShip()
 ****************************************************************/
void TestShip::test_draw_invokesDraw() {
   // Setup
   SpyShip s;
   // Exercise
   s.draw();
   // Verify
   assertUnit(s.drawn);
   // Teardown
}
