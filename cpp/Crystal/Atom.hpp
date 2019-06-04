#pragma once


#include <string>
#include <algorithm>
#include <vector>

#include "Vector3.hpp"

using namespace std;

class Atom {
  private:
    int     m_number;
    Vector3 m_position;
    double  m_occupancy;

  public:
    void SetPos(Vector3 v);
    Vector3 GetPos() const;
    void SetNumber(int n);
    int GetNumber() const;
    void SetOccupancy(double d);
    double GetOccupancy() const;

  public:
    Atom();
    Atom(int n, double x, double y, double z, double occupancy = 1.0);

    static int AtomicNumber(string s);
    static string AtomicSymbol(int i);
};

