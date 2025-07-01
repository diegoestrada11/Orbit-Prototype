/***********************************************************************
 * Source File:
 *    TEST SATELLITE
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/
#include "testSatellite.h"
#include "position.h"
#include "velocity.h"

/******************************************************
* DUMMY BODY CLASS
* A simple Body subclass that does nothing
*******************************************************/
class DummyBody : public Body {
public:
   DummyBody() : Body(Position(0, 0), Velocity(0, 0), 1.0) {}
   void draw() const override {}
};

/******************************************************
* TEST SATELLITE DOUBLE CLASS
* A concrete Satellite subclass for testing purposes
*******************************************************/
class TestSatelliteDouble : public Satellite {
public:
   TestSatelliteDouble(int num)
      : Satellite(Position(0, 0), Velocity(0, 0), 1.0), num(num), drawn(false) {
   }

   // track drawSatellite calls
   void drawSatellite() const override {
      const_cast<TestSatelliteDouble*>(this)->drawn = true;
   }

   // breakUp returns _num DummyBody instances
   vector<Body*> breakUp() override {
      vector<Body*> v;
      for (int i = 0; i < num; ++i)
         v.push_back(new DummyBody());
      return v;
   }

   bool drawn;
private:
   int num;
};

void TestSatellite::run() {
   test_onCollision_setsExpired();
   test_breakUp_customCount();
   test_angleToward_cardinal();
   test_draw_invokesDrawSatellite();
   test_inheritsBodyIntersects();
   report("Satellite");
}

/******************************************************
* TEST ON COLLISION SETS EXPIRED
* verify that onCollision() sets the expired flag
*******************************************************/
void TestSatellite::test_onCollision_setsExpired() {
   // Setup
   TestSatelliteDouble sat(0);
   // Exercise
   sat.onCollision(nullptr);
   // Verify
   assertUnit(sat.isExpired());
   // Teardown
}

/******************************************************
* TEST BREAK UP CUSTOM COUNT
* verify breakUp() returns a vector with the expected number of bodies
*******************************************************/
void TestSatellite::test_breakUp_customCount() {
   // Setup
   int count = 3;
   TestSatelliteDouble sat(count);
   // Exercise
   auto vec = sat.breakUp();
   // Verify
   assertEquals((int)vec.size(), count);
   // Teardown
   for (auto b : vec) delete b;
}

/******************************************************
* TEST ANGLE TOWARD CARDINAL
* verify angleToward returns expected angles for cardinal directions
*******************************************************/
void TestSatellite::test_angleToward_cardinal() {
   // Setup
   TestSatelliteDouble sat(0);
   Position target;

   // Exercise & Verify
   // North (0,1)
   target.setPixelsX(0); target.setPixelsY(100);
   assertEquals(sat.angleToward(target).toRadians(), 0.0);

   // East (1,0): dx=1,dy=0 => pi/2
   target.setPixelsX(100); target.setPixelsY(0);
   assertEquals(sat.angleToward(target).toRadians(), M_PI / 2);

   // South (0,-1): dx=0,dy=-1 => pi
   target.setPixelsX(0); target.setPixelsY(-100);
   assertEquals(sat.angleToward(target).toRadians(), M_PI);

   // West (-1,0): dx=-1,dy=0 => 3pi/2
   target.setPixelsX(-100); target.setPixelsY(0);
   assertEquals(sat.angleToward(target).toRadians(), 3 * M_PI / 2);

   // Teardown
}

/******************************************************
* TEST DRAW INVOKES DRAW SATELLITE
* verify draw() invokes drawSatellite()
*******************************************************/
void TestSatellite::test_draw_invokesDrawSatellite() {
   // Setup
   TestSatelliteDouble sat(0);
   // Exercise
   sat.draw();
   // Verify
   assertUnit(sat.drawn);
   // Teardown
}

/******************************************************
* TEST INHERITS BODY INTERSECTS
* verify intersects() works as expected for two satellites
*******************************************************/
void TestSatellite::test_inheritsBodyIntersects() {
   // Setup
   // two satellites with small radius overlapping by 1 meter
   TestSatelliteDouble a(0);
   TestSatelliteDouble b(0);

   // Compute pixel equivalent of 1 meter via zoom
   Position temp;
   double metersPerPixel = temp.getZoom();
   double oneMeterPx = 1.0 / metersPerPixel;

   // Set their pixel positions
   Position pa;
   pa.setPixelsX(0);
   pa.setPixelsY(0);
   Position pb;
   pb.setPixelsX(0);
   pb.setPixelsY(oneMeterPx);

   // Inject into the satellite bodies
   const_cast<Position&>(a.getPosition()) = pa;
   const_cast<Position&>(b.getPosition()) = pb;

   // Exercise & Verify
   assertUnit(a.intersects(b)); // radii are 1 meter each, so distance 1 <= 2 => intersects
   // Teardown
}
