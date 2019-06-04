#pragma once

#include <string>
#include <iostream>
#include <math.h>

#include "Atom.hpp"
#include "Cell.hpp"

using namespace std;

class CIF {
public:
  CIF();
  static bool Read(const string& FilePath, Cell& cell, vector<Atom>& Atoms);
  static bool SaveAsP1(const string& FilePath, Cell& cell, vector<Atom>& Atoms);

private:
  static void GetSections(const vector<string>& vsLines,
                          string& sHM, string& sIT, string& sCL,
                          string& sSY, string& sAT);
  static string DropError(const string& s);
  static void ReadCell(const string& strIn, Cell& cell);
  static void ReadSymm(const string& strIn, Cell& cell);
  static void ReadAtom(const string& strIn, vector<Atom>& Atoms);
};
