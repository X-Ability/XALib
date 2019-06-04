#pragma once

#include "Atom.hpp"
#include "Cell.hpp"

class Boundary {
public:
  static void BackToUnitCell(const Cell& cell, vector<Atom>& Atoms);
};
