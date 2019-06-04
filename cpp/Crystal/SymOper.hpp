#pragma once
#include <vector>
#include <string>
#include "Vector3.hpp"
#include "String.hpp"

using namespace std;

class SymOper {
public:
private:
  Matrix33 m_mSym;
  Vector3  m_vSym;
public:
  SymOper() {};
  void Set(string str);
  Matrix33 GetMatrix();
  Vector3  GetVector();
private:
  bool SetEach(int idx, string str);
};
