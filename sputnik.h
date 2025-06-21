/***********************************************************************
 * Header File:
 *    Sputnik
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a sputnik satellite on the screen.
 ************************************************************************/

#include "satellite.h"
#include <string>
#pragma once

/****************************************************************************
* SPUTNIK
****************************************************************************/
class Sputnik : public Satellite
{
public:
   Sputnik();

   string getName() const;
   void draw() const override;

private:
   string name;
};