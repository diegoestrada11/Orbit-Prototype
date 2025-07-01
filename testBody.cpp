/***********************************************************************
 * Source File:
 *    TEST BODY
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/
#include "TestBody.h"
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include <cmath>

/******************************************************
* TESTABLE BODY CLASS
* A simple Body subclass that exposes protected methods
*******************************************************/
class TestableBody : public Body {
public:
   TestableBody(const Position& p, const Velocity& v, double r)
      : Body(p, v, r) {
   }
   void draw() const override {}
   using Body::expire;                        // expose expire()
   using Body::computeAcceleration;           // expose computeAcceleration()
};

/******************************************************
* FAKEBODY CLASS
* A simple Body subclass that provides a constant acceleration
*******************************************************/
class FakeBody : public Body {
public:
   FakeBody()
      : Body(Position(0.0, 0.0), Velocity(0.0, 0.0), 1.0) {
   }
   void draw() const override {}
   bool canBurnUp() const override { return false; }
protected:
   Acceleration computeAcceleration() const override {
      return Acceleration(1.0, 2.0);
   }
};

void TestBody::run() {
   test_expire_setsExpired();
   test_onCollision_expires();
   test_breakUp_defaultEmpty();
   test_intersects_true();
   test_intersects_false();
   test_computeAcceleration_belowSurface();
   test_computeAcceleration_atSurface();
   test_update_burnUp();
   test_update_physicsIntegration();
   report("Body");
}

/******************************************************
* TEST EXPIRE SETS EXPIRED
* verify that expire() sets the expired flag
*******************************************************/
void TestBody::test_expire_setsExpired() {
   // Setup
   TestableBody b(Position(0, 0), Velocity(0, 0), 1.0);
   // Exercise
   b.expire();  // protected, but onCollision calls it
   // Verify
   assertUnit(b.isExpired());
   // Teardown
}

/******************************************************
* TEST ON COLLISION
*  verify that onCollision() expires the body
*******************************************************/
void TestBody::test_onCollision_expires() {
   // Setup
   TestableBody b(Position(1000, 1000), Velocity(0, 0), 1.0);
   // Exercise
   b.onCollision(nullptr);
   // Verify
   assertUnit(b.isExpired());
   // Teardown
}

/******************************************************
* TEST BREAK UP DEFAULT EMPTY
* verify that default breakUp() returns an empty vector
*******************************************************/
void TestBody::test_breakUp_defaultEmpty() {
   // Setup
   TestableBody b(Position(0, 0), Velocity(0, 0), 1.0);
   // Exercise
   auto parts = b.breakUp();
   // Verify
   assertEquals((int)parts.size(), 0);
   // Teardown
}

/******************************************************
* TEST INTERSECTS TRUE
* verify intersects return true when two bodies overlap
*******************************************************/
void TestBody::test_intersects_true() {
   // Setup
   TestableBody a(Position(0, 0), Velocity(0, 0), 5.0);
   TestableBody b(Position(3, 4), Velocity(0, 0), 5.0); // distance 5, sum radii=10
   // Exercise & Verify
   assertUnit(a.intersects(b));
   // Teardown
}

/******************************************************
* TEST INTERSECTS FALSE
* verify intersects returns false when bodies do not overlap
*******************************************************/
void TestBody::test_intersects_false() {
   // Setup
   TestableBody a(Position(0, 0), Velocity(0, 0), 2.0);
   TestableBody b(Position(10, 10), Velocity(0, 0), 2.0);
   // Exercise & Verify
   assertUnit(!a.intersects(b));
   // Teardown
}

/******************************************************
* TEST COMPUTE ACCELERATION BELOW SURFACE
* verify computeAcceleration() returns zero acceleration
*******************************************************/
void TestBody::test_computeAcceleration_belowSurface() {
   // Setup
   TestableBody b(Position(0, 0), Velocity(0, 0), 1.0);
   // Exercise
   Acceleration a = b.computeAcceleration();
   // Verify
   assertEquals(a.getDDX(), 0.0);
   assertEquals(a.getDDY(), 0.0);
   // Teardown
}

/******************************************************
* TEST COMPUTE ACCELERATION AT SURFACE
* verify computeAcceleration() at surface
*******************************************************/
void TestBody::test_computeAcceleration_atSurface() {
   // Setup
   double R = 6378000.0;
   TestableBody b(Position(0, R + 0.0), Velocity(0, 0), 1.0); // place at (0, R+0) -> h=0
   // Exercise
   Acceleration a = b.computeAcceleration();
   double expected = 9.80665 * std::pow(R / (R + 0.0), 2); // direction toward center yields dx=0, dy negative
   // Verify
   assertEquals(a.getDDX(), 0.0);
   assertEquals(a.getDDY(), -expected);
   // Teardown
}

/******************************************************
* TEST UPDATE BURN UP
* verify that update() burns up when inside Earth
*******************************************************/
void TestBody::test_update_burnUp() {
   // Setup
   double R = 6378000.0;
   TestableBody b(Position(0, 0), Velocity(0, 0), 1.0);
   // Exercise
   b.update(1.0);
   // Verify: expired
   assertUnit(b.isExpired());
   // Teardown
}

/******************************************************
* TEST UPDATE PHYSICS INTEGRATION
* verify that update() integrates velocity and position correctly
*******************************************************/
void TestBody::test_update_physicsIntegration() {
   // Setup
   FakeBody fb;
   double dt = 2.0;
   // Exercise
   fb.update(dt);
   // Verify
   assertEquals(fb.getVelocity().getDx(), 1.0 * dt); // velocity = a * dt = (2, 4)
   assertEquals(fb.getVelocity().getDy(), 2.0 * dt);
   // position = v*dt + .5*a*dt^2 = (2 + .5*1*4, 4 + .5*2*4) = (4,8)
   assertEquals(fb.getPosition().getMetersX(), 2.0);
   assertEquals(fb.getPosition().getMetersY(), 4.0);
   // Teardown
}
