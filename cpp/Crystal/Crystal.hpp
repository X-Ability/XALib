#pragma once

#include <string>
#include <iostream>
#include <math.h>

#include "Atom.hpp"
#include "Cell.hpp"
#include "Boundary.hpp"

using namespace std;

class Crystal {
public:
  Crystal();
  static vector<Atom> SymmetryOperation(const Cell& cell, const vector<Atom>& vAsymAtoms);
  static vector<Atom> Dedupe(const Cell& cell, const vector<Atom>& Atoms, int nAsym);

private:
  static vector<Atom> DedupeAtomsSelf(const Cell& cell, const vector<Atom>& Atoms);
  static vector<Atom> DedupeAtomsBy  (const Cell& cell, const vector<Atom>& Atoms0,
				      const vector<Atom>& Atoms1);
};
