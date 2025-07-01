/***********************************************************************
 * Source File:
 *    TEST GPS
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for Test GPS
 ************************************************************************/

#include "testGPS.h"
#include "fragment.h"
#include "position.h"
#include "velocity.h"
#include <cmath>

/*****************************************************************
 * SPY GPS CLASS
 * A subclass of GPS that overrides drawSatellite to set a flag
 ****************************************************************/
class SpyGPS : public GPS {
public:
   SpyGPS() : drawn(false) {}
   void drawSatellite() const override {
      const_cast<SpyGPS*>(this)->drawn = true;
   }
   bool drawn;
};

void TestGPS::run() {
   test_constructor_initialValues();
   test_breakUp_count();
   test_breakUp_fragmentType();
   test_breakUp_offsetDistance();
   test_draw_invokesDrawGPS();
   report("GPS");
}

/*****************************************************************
 * TEST CONSTRUCTOR INITIAL VALUES
 * Verifies that the GPS constructor initializes position and velocity correctly.
 ****************************************************************/
void TestGPS::test_constructor_initialValues() {
   // Setup & Exercise
   GPS g;
   // Verify
   Position p = g.getPosition();
   Velocity v = g.getVelocity();
   assertEquals(p.getMetersX(), 0.0);
   assertEquals(p.getMetersY(), 26560000.0);
   assertEquals(v.getDx(), -3880.0);
   assertEquals(v.getDy(), 0.0);
   // Teardown
}

/*****************************************************************
 * TEST BREAK UP COUNT
 * Verifies that the breakUp() method returns exactly 2 fragments.
 ****************************************************************/
void TestGPS::test_breakUp_count() {
   // Setup
   GPS g;
   // Exercise
   auto pieces = g.breakUp();
   // Verify
   assertEquals((int)pieces.size(), 2);
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST BREAK UP FRAGMENT TYPE
 * Verifies that all pieces returned by breakUp() are of type Fragment.
 ****************************************************************/
void TestGPS::test_breakUp_fragmentType() {
   // Setup
   GPS g;
   auto pieces = g.breakUp();
   // Exercise & Verify
   for (auto b : pieces) {
      Fragment* f = dynamic_cast<Fragment*>(b);
      assertUnit(f != nullptr);
   }
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST BREAK UP OFFSET DISTANCE
 * Verifies that each piece returned by breakUp() is offset by SPAWN_OFFSET_PX pixels
 ****************************************************************/
void TestGPS::test_breakUp_offsetDistance() {
   // Setup
   GPS g;
   Position orig = g.getPosition();
   double zoom = orig.getZoom();
   double expected = 4.0 * zoom;
   auto pieces = g.breakUp();
   // Exercise & Verify
   for (auto b : pieces) {
      Position p2 = b->getPosition();
      double dx = p2.getMetersX() - orig.getMetersX();
      double dy = p2.getMetersY() - orig.getMetersY();
      double dist = std::hypot(dx, dy);
      assertUnit(std::fabs(dist - expected) < 1e-6);
   }
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST DRAW INVOKES DRAW GPS
 * Verifies that the draw() method of GPS invokes drawSatellite().
 ****************************************************************/
void TestGPS::test_draw_invokesDrawGPS() {
   // Setup
   SpyGPS g;
   // Exercise
   g.draw();
   // Verify
   assertUnit(g.drawn);
   // Teardown
}