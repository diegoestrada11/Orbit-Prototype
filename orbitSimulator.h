/***********************************************************************
 * Header File:
 *    Orbit Simulator
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a body on the screen.
 ************************************************************************/

#pragma once
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "sputnik.h"

#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for ogstream, drawEarth

/**
 * OrbitSimulator
 *   Encapsulates a single Sputnik satellite orbiting Earth.
 */
class OrbitSimulator
{
public:
   /**
    * Constructor
    *   bounds: window bounds (zoom & pixel dimensions)
    */
   OrbitSimulator(const Position& bounds);

   /**
    * Handle user input (unused for now)
    */
   void input(const Interface* pUI);

   /**
    * Update physics and render scene
    */
   void display();

private:
   Position bounds;   // view bounds
   Sputnik  sputnik;  // our single satellite
};

