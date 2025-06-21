/***********************************************************************
 * Header File:
 *    Test Body : Test the Body class
 * Author:
 *    Natalia Navarrete Diego Estrada
 * Summary:
 *    All the unit tests for Body
 ************************************************************************/

#pragma once

#include "body.h"
#include "unitTest.h"

 /*******************************
  * TEST Body
  * A friend class for Body which contains the Body unit tests
  ********************************/
class TestBody : public UnitTest
{
public:
   void run()
   {
      // Constructor
      construct_default();

      // Setters
      setPosition();
      setVelocity();
      setActiveFlag();

      // Methods
      updateMovement();
      updateInactive();

      report("Body");
   }

private:
   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   none
    * output:  position=(0,0), velocity=(0,0), active=true
    *********************************************/
   void construct_default();

   /*********************************************
    * name:    SET POSITION
    * input:   pos=(100,200)
    * output:  getPosition()==(100,200)
    *********************************************/
   void setPosition();

   /*********************************************
    * name:    SET VELOCITY
    * input:   vel=(5,-3)
    * output:  getVelocity()==(5,-3)
    *********************************************/
   void setVelocity();

   /*********************************************
    * name:    SET ACTIVE FLAG
    * input:   active=false
    * output:  isActive()==false
    *********************************************/
   void setActiveFlag();

   /*********************************************
    * name:    UPDATE MOVEMENT
    * input:   velocity=(2,3), dt=1.0
    * output:  position updated to (2,3)
    *********************************************/
   void updateMovement();

   /*********************************************
    * name:    UPDATE INACTIVE
    * input:   active=false
    * output:  position unchanged
    *********************************************/
   void updateInactive();
};


class BodyConcrete : public Body
{
public:
   void draw() const override
   {
      // no-op
   }
};
