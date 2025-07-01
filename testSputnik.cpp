/***********************************************************************
 * Source File:
 *    Test Sputnik
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/
#include "testSputnik.h"
#include "fragment.h"
#include <cmath>

/******************************************************
* SPY SPUTNIK CLASS
* A subclass of Sputnik that overrides drawSatellite
*******************************************************/
class SpySputnik : public Sputnik {
public:
   SpySputnik() : drawn(false) {}
   void drawSatellite() const override {
      const_cast<SpySputnik*>(this)->drawn = true;
   }
   bool drawn;
};

void TestSputnik::run() {
   test_constructor_initialValues();
   test_breakUp_count();
   test_breakUp_fragmentType();
   test_breakUp_offsetDistance();
   test_draw_invokesDrawSputnik();
   report("Sputnik");
}

/******************************************************
* TEST CONSTRUCTOR INITIAL VALUES
* Verifies initial position and velocity
*******************************************************/
void TestSputnik::test_constructor_initialValues() {
   // Setup & Exercise
   Sputnik s;
   // Verify
   Position p = s.getPosition();
   Velocity v = s.getVelocity();
   assertEquals(p.getMetersX(), -36515095.13);
   assertEquals(p.getMetersY(), 21082000.0);
   assertEquals(v.getDx(), 2050.0);
   assertEquals(v.getDy(), 2684.68);
   // Teardown
}

/******************************************************
* TEST BREAK UP COUNT
* verifys that breakUp() returns 4 fragments
*******************************************************/
void TestSputnik::test_breakUp_count() {
   // Setup
   Sputnik s;
   // Exercise
   auto pieces = s.breakUp();
   // Verify
   assertEquals((int)pieces.size(), 4);
   // Teardown
   for (auto b : pieces) delete b;
}

/******************************************************
* TEST BREAK UP FRAGMENT TYPE
* verifies that all pieces are of type Fragment
*******************************************************/
void TestSputnik::test_breakUp_fragmentType() {
   // Setup
   Sputnik s;
   auto pieces = s.breakUp();
   // Exercise & Verify
   for (auto b : pieces) {
      Fragment* f = dynamic_cast<Fragment*>(b);
      assertUnit(f != nullptr);
   }
   // Teardown
   for (auto b : pieces) delete b;
}

/******************************************************
* TEST BREAK UP OFFSET DISTANCE
* verifies that each fragment is offset 4 px from the original position
*******************************************************/
void TestSputnik::test_breakUp_offsetDistance() {
   // Setup
   Sputnik s;
   Position orig = s.getPosition();
   double zoom = orig.getZoom();            // m/px
   double expectedOffset = 4.0 * zoom;      // meters

   auto pieces = s.breakUp();
   // Exercise & Verify
   for (auto b : pieces) {
      Position p2 = b->getPosition();
      double dx = p2.getMetersX() - orig.getMetersX();
      double dy = p2.getMetersY() - orig.getMetersY();
      double dist = hypot(dx, dy);
      // allow small floating error
      assertUnit(fabs(dist - expectedOffset) < 1e-6);
   }
   // Teardown
   for (auto b : pieces) delete b;
}

/******************************************************
* TEST DRAW INVOKES DRAW SPUTNIK
* verifies that draw() calls drawSatellite()
*******************************************************/
void TestSputnik::test_draw_invokesDrawSputnik() {
   // Setup
   SpySputnik s;
   // Exercise
   s.draw();
   // Verify
   assertUnit(s.drawn);
   // Teardown
}