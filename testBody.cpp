/***********************************************************************
 * Source File:
 *    TEST BODY
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/


#include "TestBody.h"
#include "unitTest.h"
#include "body.h"
#include "position.h"
#include "velocity.h"
#include <cmath>


void TestBody::construct_default()
{
   BodyConcrete b;
   assertUnit(b.getPosition().getMetersX() == 0.0);
   assertUnit(b.getPosition().getMetersY() == 0.0);
   assertUnit(b.getVelocity().getDx() == 0.0);
   assertUnit(b.getVelocity().getDy() == 0.0);
   assertUnit(b.isActive());
}

void TestBody::setPosition()
{
   BodyConcrete b;
   Position p(100.0, 200.0);
   b.setPosition(p);
   assertUnit(b.getPosition().getMetersX() == 100.0);
   assertUnit(b.getPosition().getMetersY() == 200.0);
}

void TestBody::setVelocity()
{
   BodyConcrete b;
   Velocity v;
   v.setDx(5.0);
   v.setDy(-3.0);
   b.setVelocity(v);
   assertUnit(b.getVelocity().getDx() == 5.0);
   assertUnit(b.getVelocity().getDy() == -3.0);
}

void TestBody::setActiveFlag()
{
   BodyConcrete b;
   b.setActive(false);
   assertUnit(!b.isActive());
}

void TestBody::updateMovement()
{
   BodyConcrete b;
   Velocity v;
   v.setDx(2.0);
   v.setDy(3.0);
   b.setVelocity(v);
   b.update(1.0);
   assertUnit(b.getPosition().getMetersX() == 2.0);
   assertUnit(b.getPosition().getMetersY() == 3.0);
}

void TestBody::updateInactive()
{
   BodyConcrete b;
   b.setActive(false);
   Position orig = b.getPosition();
   b.update(1.0);
   assertUnit(b.getPosition().getMetersX() == orig.getMetersX());
   assertUnit(b.getPosition().getMetersY() == orig.getMetersY());
}
