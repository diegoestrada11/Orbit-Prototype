/***********************************************************************
 * Source File:
 *    TEST Earth
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for Test Earth
 ************************************************************************/

#include "testEarth.h"
#include <cassert>
#include <cmath>

/*********************************************************************
 * SPY EARTH CLASS
 **********************************************************************/
class SpyEarth : public Earth
{
public:
   bool drawCalled = false;

   // Override draw to set a flag instead of calling the UI
   void draw() const override {
      // const_cast to modify the flag in a const method
      const_cast<SpyEarth*>(this)->drawCalled = true;
   }
};

void TestEarth::run()
{
   test_constructor_initialValues();
   test_update_rotation();
   test_breakUp_empty();
   test_draw_invokesDraw();
   report("Earth");
}

/**********************************************************************
 * TEST CONSTRUCTOR INITIAL VALUES
 * verify that the default constructor sets position to (0,0) and
 * velocity to (0,0), and radius to the real Earth radius in meters.
 **********************************************************************/
void TestEarth::test_constructor_initialValues() {
   // SETUP
   Earth e;

   // EXERCISE
   Position pos = e.getPosition();
   Velocity vel = e.getVelocity();
   double radius = e.getRadius();

   // VERIFY
   assertEquals(pos.getMetersX(), 0.0);
   assertEquals(pos.getMetersY(), 0.0);
   assertEquals(vel.getDx(), 0.0);
   assertEquals(vel.getDy(), 0.0);
   assertEquals(radius, 6378000.0);  // 6,378 km in meters

   // TEARDOWN
}

/**********************************************************************
 * TEST UPDATE ROTATION
 * verify that update() rotates Earth by the fixed per-frame increment.
 **********************************************************************/
void TestEarth::test_update_rotation() {
   // SETUP
   Earth e;
   double before = e.getAngle().toRadians();

   // EXERCISE
   e.update(0.0);  // dt is unused for Earth, but we call it anyway

   // VERIFY
   double rawInc = -2.0 * M_PI / 1800.0; // raw increment (negative)
   // normalize exactly as our Angle class would:
   double normInc = Angle(rawInc).toRadians();

   double after = e.getAngle().toRadians();
   // Now before + normInc equals the stored after value
   assertEquals(after, before + normInc);

   // TEARDOWN
}

/**********************************************************************
 * TEST BREAKUP EMPTY
 * verify that breakUp() returns an empty list for Earth.
 **********************************************************************/
void TestEarth::test_breakUp_empty() {
   // SETUP
   Earth e;

   // EXERCISE
   auto pieces = e.breakUp();

   // VERIFY
   assertEquals((int)pieces.size(), 0);

   // TEARDOWN
}

/**********************************************************************
 * TEST DRAW INVOKES DRAW
 * verify that draw() on our SpyEarth actually gets invoked. 
 **********************************************************************/
void TestEarth::test_draw_invokesDraw() {
   // SETUP
   SpyEarth se;
   assertUnit(!se.drawCalled);

   // EXERCISE
   se.draw();

   // VERIFY
   assertUnit(se.drawCalled);

   // TEARDOWN
}