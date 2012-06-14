#pragma once
#ifndef MORTAR_H
#define MORTAR_H

#ifdef FEOS
#include <feos.h>
#else
#include <nds.h>
#endif
#include <stdlib.h>
#include "particle.h"
#include "atan.h"
#include "list.h"

class Mortar {
private:
  class pMortar : public Particle {
  private:
    s32 dx;
    s32 dy;
    s32 distance;
    list<Particle*> *pList;
    int upgrade;
    class pShrapnel : public Particle {
    private:
      s32 dx;
      s32 dy;
      s32 distance;
    public:
      pShrapnel(s32 x, s32 y, int upgrade)
      : Particle(x,y), distance(inttof32(5*upgrade)) {
        s32 direction = rand()%32768;
        dx = cosLerp(direction)/2;
        dy = sinLerp(direction)/2;
      }

      void move() {
        x += dx;
        y += dy;
        distance -= floattof32(0.5f);

        if(x < 0 || x > inttof32(256) || y < 0 || y > inttof32(192))
          valid = false;
        if(distance < 0)
          valid = false;
      }
      s32 getX()     { return f32toint(x); }
      s32 getY()     { return f32toint(y); }
      bool isValid() { return valid;       }
    };
  public:
    pMortar(s32 x, s32 y, s32 tx, s32 ty, int upgrade, list<Particle*> *pList)
      : Particle(x,y), pList(pList), upgrade(upgrade)
    {
      s32 direction = atan2Tonc(ty-y, tx-x);
      dx = cosLerp(direction)/2;
      dy = sinLerp(direction)/2;

      distance = sqrtf32(mulf32(ty-y, ty-y) + mulf32(tx-x, tx-x));

      if(x < 0 || x > inttof32(256) || y < 0 || y > inttof32(192))
        valid = false;
    }

    void move() {
      x += dx;
      y += dy;
      distance -= floattof32(0.5f);

      if(x < 0 || x > inttof32(256) || y < 0 || y > inttof32(192))
        valid = false;
      else if(distance < 0) {
        for(int i = 0; i < 10*upgrade; i++)
          pList->push_back(new pShrapnel(x, y, upgrade));
        valid = false;
      }
    }

    s32 getX()     { return f32toint(x); }
    s32 getY()     { return f32toint(y); }
    bool isValid() { return valid;       }
  };

  Mortar();
  ~Mortar();
public:
  static void shoot(s32 x, s32 y, s32 tx, s32 ty, int upgrade, list<Particle*> *pList) {
    static int cooldown = 60;
    if(cooldown <= 0) {
      pList->push_back(new pMortar(x, y, tx, ty, upgrade, pList));
      cooldown = 60;
    }
    else
      cooldown -= upgrade;
  }
};

#endif /* MORTAR_H */
