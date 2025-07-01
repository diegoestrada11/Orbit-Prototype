/***********************************************************************
 * Source File:
 *    Test Starlink
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "testStarlink.h"
#include "fragment.h"
#include "position.h"
#include <cmath>

/*****************************************************************
 * SPY STARLINK CLASS
 ****************************************************************/
class SpyStarlink : public Starlink {
public:
   SpyStarlink() : drawn(false) {}
   void drawSatellite() const override {
      const_cast<SpyStarlink*>(this)->drawn = true;
   }
   bool drawn;
};

void TestStarlink::run() {
   test_constructor_initialValues();
   test_breakUp_count();
   test_breakUp_fragmentType();
   test_breakUp_offsetDistance();
   test_draw_invokesDrawStarlink();
   report("Starlink");
}

/*****************************************************************
 * TEST CONSTRUCTOR INITIAL VALUES
 * verify default constructor sets position and velocity correctly
 *****************************************************************/
void TestStarlink::test_constructor_initialValues() {
   // Setup
   Starlink s;
   // Exercise
   Position p = s.getPosition();
   Velocity v = s.getVelocity();
   double r = s.getRadius();
   // Verify
   assertEquals(p.getMetersX(), 0.0);
   assertEquals(p.getMetersY(), -13020000.0);
   assertEquals(v.getDx(), 5800.0);
   assertEquals(v.getDy(), 0.0);
   double expectedRadius = 6.0 * p.getZoom();
   assertEquals(r, expectedRadius);
   // Teardown
}

/*****************************************************************
 * TEST BREAKUP COUNT
 * verify breakUp() returns 6 fragments
 *****************************************************************/
void TestStarlink::test_breakUp_count()
{
   // Setup
   Starlink s;
   // Exercise
   auto pieces = s.breakUp();
   // Verify
   assertEquals((int)pieces.size(), 6);
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST BREAKUP FRAGMENT TYPE
 * verify all returned bodies are Fragments
 *****************************************************************/
void TestStarlink::test_breakUp_fragmentType()
{
   // Setup
   Starlink s;
   auto pieces = s.breakUp();
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
 * verify spawn offset by 4 px in meters
 ****************************************************************/
void TestStarlink::test_breakUp_offsetDistance() {
   // Setup
   Starlink s;
   Position orig = s.getPosition();
   double zoom = orig.getZoom();
   double expected = 4.0 * zoom;  // SPAWN_OFFSET_PX = 4
   auto pieces = s.breakUp();
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
 * TEST DRAW INVOKES DRAW STARLINK
 * verify draw() should call drawSatellite()
 ****************************************************************/
void TestStarlink::test_draw_invokesDrawStarlink() {
   // Setup
   SpyStarlink s;
   // Exercise
   s.draw();
   // Verify
   assertUnit(s.drawn);
   // Teardown
}