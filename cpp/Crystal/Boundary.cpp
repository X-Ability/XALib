#include "Boundary.hpp"

using namespace std;

// NOTE: Atoms should be fractional
void Boundary::BackToUnitCell(const Cell& cell, vector<Atom>& Atoms) {
  for(unsigned int i = 0; i < Atoms.size(); ++i) {
    Atom a = Atoms[i];
    Vector3 v = a.GetPos();
    while(v.x <  0.0) v.x += 1.0;
    while(v.y <  0.0) v.y += 1.0;
    while(v.z <  0.0) v.z += 1.0;
    while(v.x >= 1.0) v.x -= 1.0;
    while(v.y >= 1.0) v.y -= 1.0;
    while(v.z >= 1.0) v.z -= 1.0;
    a.SetPos(v);
    Atoms[i] = a;
  }
}

