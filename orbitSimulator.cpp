 /***********************************************************************
 * Source File:
 *    ORBIT SIMULATOR
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/
#include "orbitSimulator.h"

static constexpr double FPS = 30.0;
static constexpr double TIME_DILATION = 24 * 60;
static constexpr double DT = TIME_DILATION / FPS;

OrbitSimulator::OrbitSimulator(const Position& bounds)
   : viewBounds(bounds)
{
   // Create the core satellites
   bodies.push_back(new Sputnik());
   bodies.push_back(new GPS());
   bodies.push_back(new Hubble());
   bodies.push_back(new Starlink());
   bodies.push_back(new CrewDragon());

   // Create the user?controlled ship
   bodies.push_back(new Ship());

   // Create the earth
   bodies.push_back(new Earth());

}

OrbitSimulator::~OrbitSimulator()
{
   for (auto b : bodies)
      delete b;
}

void OrbitSimulator::input(const Interface* ui)
{
   Ship* ship = nullptr;
   for (auto b : bodies) {
      if ((ship = dynamic_cast<Ship*>(b))) break;
   }
   if (!ship) return;

   // Rotation
   if (ui->isLeft())  ship->rotateLeft();
   if (ui->isRight()) ship->rotateRight();

   // Thrust: toggle based on key state
   if (ui->isDown())  ship->startThrust();
   else               ship->stopThrust();

   // Fire projectile on space press
   if (ui->isSpace()) {
      Projectile* p = ship->fireProjectile();
      bodies.push_back(p);
   }
}

void OrbitSimulator::display()
{
   // Advance physics for everyone
   advanceAll(DT);

   // Handle any collisions & spawn debris
   handleCollisions();

   // Remove expired bodies (fragments, projectiles, destroyed sats)
   removeExpired();

   // Draw Earth + all bodies
   ogstream gout(Position(0, 0));
   //gout.drawEarth(Position(0, 0), 0.0);
   for (auto b : bodies)
      b->draw();
}

void OrbitSimulator::advanceAll(double dt)
{
   for (auto b : bodies)
      b->update(dt);
}

void OrbitSimulator::handleCollisions()
{
   vector<Body*> newBodies;
   const size_t n = bodies.size();

   for (size_t i = 0; i < n; ++i)
   {
      for (size_t j = i + 1; j < n; ++j)
      {
         Body* A = bodies[i];
         Body* B = bodies[j];
         if (!A->isExpired() && !B->isExpired() && A->intersects(*B))
         {
            A->onCollision(B);
            B->onCollision(A);

            // collect any breakups
            auto piecesA = A->breakUp();
            auto piecesB = B->breakUp();
            newBodies.insert(newBodies.end(), piecesA.begin(), piecesA.end());
            newBodies.insert(newBodies.end(), piecesB.begin(), piecesB.end());
         }
      }
   }

   // append new fragments/parts/projectiles
   for (auto p : newBodies)
      bodies.push_back(p);
}

void OrbitSimulator::removeExpired()
{
   auto it = bodies.begin();
   while (it != bodies.end())
   {
      if ((*it)->isExpired())
      {
         delete* it;
         it = bodies.erase(it);
      }
      else
         ++it;
   }
}

