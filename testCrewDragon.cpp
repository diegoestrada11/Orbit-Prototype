/***********************************************************************
 * Source File:
 *    TEST CrewDragon
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for CrewDragon
 ************************************************************************/

#include "testCrewDragon.h"
#include "fragment.h"
#include "position.h"
#include <cmath>

/*****************************************************************
 * SPY CREW DRAGON CLASS
 * A subclass of CrewDragon that overrides drawSatellite to set a flag.
 ****************************************************************/
class SpyCrewDragon : public CrewDragon {
public:
   SpyCrewDragon() : drawn(false) {}
   void drawSatellite() const override {
      const_cast<SpyCrewDragon*>(this)->drawn = true;
   }
   bool drawn;
};

void TestCrewDragon::run() {
   test_constructor_initialValues();
   test_breakUp_count();
   test_breakUp_fragmentType();
   test_breakUp_offsetDistance();
   test_draw_invokesDrawCrewDragon();
   report("CrewDragon");
}

/*****************************************************************
 * TEST CONSTRUCTOR INITIAL VALUES
 * Verifies that the CrewDragon constructor initializes position and velocity.
 ****************************************************************/
void TestCrewDragon::test_constructor_initialValues() {
   // Setup & Exercise
   CrewDragon d;
   // Verify
   Position p = d.getPosition();
   Velocity v = d.getVelocity();
   assertEquals(p.getMetersX(), 0.0);
   assertEquals(p.getMetersY(), 8000000.0);
   assertEquals(v.getDx(), -7900.0);
   assertEquals(v.getDy(), 0.0);
   // Teardown
}

/*****************************************************************
 * TEST BREAK UP COUNT
 * Verifies that CrewDragon.breakUp() returns 8 fragments.
 ****************************************************************/
void TestCrewDragon::test_breakUp_count() {
   // Setup
   CrewDragon d;
   // Exercise
   auto pieces = d.breakUp();
   // Verify
   assertEquals((int)pieces.size(), 8);
   // Teardown
   for (auto b : pieces) delete b;
}

/*****************************************************************
 * TEST BREAK UP FRAGMENT TYPE
 * Verifies that all pieces returned by breakUp() are of type Fragment.
 ****************************************************************/
void TestCrewDragon::test_breakUp_fragmentType() {
   // Setup
   CrewDragon d;
   auto pieces = d.breakUp();
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
 * Verifies that each fragment is spawned at an offset distance of 4 pixels
 ****************************************************************/
void TestCrewDragon::test_breakUp_offsetDistance() {
   // Setup
   CrewDragon d;
   Position orig = d.getPosition();
   double zoom = orig.getZoom();
   double expected = 4.0 * zoom; // SPAWN_OFFSET_PX
   auto pieces = d.breakUp();
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
 * TEST DRAW INVOKES DRAW CREW DRAGON
 * Verifies that calling draw() on CrewDragon invokes drawSatellite().
 ****************************************************************/
void TestCrewDragon::test_draw_invokesDrawCrewDragon() {
   // Setup
   SpyCrewDragon d;
   // Exercise
   d.draw();
   // Verify
   assertUnit(d.drawn);
   // Teardown
}