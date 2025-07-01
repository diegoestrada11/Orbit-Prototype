/***********************************************************************
 * Source File:
 *    Test Hubble
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for TestHubble
 ************************************************************************/

#include "testHubble.h"
#include "fragment.h"
#include "position.h"
#include <cmath>

/*****************************************************************
 * SPY HUBBLE CLASS
 * A SpyHubble class that overrides drawSatellite() to set a flag
 ****************************************************************/
class SpyHubble : public Hubble {
public:
   SpyHubble() : drawn(false) {}
   void drawSatellite() const override {
      const_cast<SpyHubble*>(this)->drawn = true;
   }
   bool drawn;
};

void TestHubble::run() {
   test_constructor_initialValues();
   test_breakUp_count();
   test_breakUp_fragmentType();
   test_breakUp_offsetDistance();
   test_draw_invokesDrawHubble();
   report("Hubble");
}

/*****************************************************************
 * TEST CONSTRUCTOR INITIAL VALUES
 * verify initial position and velocity
 ****************************************************************/
void TestHubble::test_constructor_initialValues() {
   // Setup & Exercise
   Hubble h;
   // Verify
   Position p = h.getPosition();
   Velocity v = h.getVelocity();
   assertEquals(p.getMetersX(), 0.0);
   assertEquals(p.getMetersY(), -42164000.0);
   assertEquals(v.getDx(), 3100.0);
   assertEquals(v.getDy(), 0.0);
   // Teardown
}

/*****************************************************************
 * TEST BREAKUP COUNT
 * verify that breakUp() returns 9 fragments
 ****************************************************************/
void TestHubble::test_breakUp_count() {
   // Setup
   Hubble h;
   // Exercise
   auto pieces = h.breakUp();
   // Verify
   assertEquals((int)pieces.size(), 9);
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST BREAKUP FRAGMENT TYPE
 * verify that all pieces returned are Fragments
 ****************************************************************/
void TestHubble::test_breakUp_fragmentType() {
   // Setup
   Hubble h;
   auto pieces = h.breakUp();
   // Exercise & Verify
   for (auto b : pieces) {
      Fragment* f = dynamic_cast<Fragment*>(b);
      assertUnit(f != nullptr);
   }
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST BREAKUP OFFSET DISTANCE
 * verify that fragments are spawned at an offset distance
 ****************************************************************/
void TestHubble::test_breakUp_offsetDistance() {
   // Setup
   Hubble h;
   Position orig = h.getPosition();
   double zoom = orig.getZoom();
   double expected = 4.0 * zoom;  // SPAWN_OFFSET_PX
   auto pieces = h.breakUp();
   // Exercise & Verify
   for (auto b : pieces) {
      Position p2 = b->getPosition();
      double dx = p2.getMetersX() - orig.getMetersX();
      double dy = p2.getMetersY() - orig.getMetersY();
      double dist = hypot(dx, dy);
      assertUnit(fabs(dist - expected) < 1e-6);
   }
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST DRAW INVOKES DRAW HUBBLE
 * verify that draw() calls drawSatellite()
 ****************************************************************/
void TestHubble::test_draw_invokesDrawHubble() {
   // Setup
   SpyHubble h;
   // Exercise
   h.draw();
   // Verify
   assertUnit(h.drawn);
   // Teardown
}