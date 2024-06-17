#pragma once
#include <vector>
#include "Vector3.hpp"
#include "SymOper.hpp"

using namespace std;

class Cell {
private:
  // Translation vectors
  Vector3 m_vA0, m_vA1, m_vA2, m_vA3;

  // Matrix
  Matrix33 m_matR2F;           // Real to Fractional
  Matrix33 m_matF2R;           // Fractional to Real

  // Symmetry
  vector<SymOper> m_SymOpers;  // Symmetry Operations
  
public:
  Cell();
  void SetConstants(double aa, double bb, double cc, double al, double be, double ga);
  void SetConstants(Vector3 vLen, Vector3 vAng);
  void SetTranslationVectors(Vector3 vA1, Vector3 vA2, Vector3 vA3);
  void GetTranslationVectors(Vector3& vA1, Vector3& vA2, Vector3& vA3) const;
  Matrix33 GetTranslationMatrix() const { return Matrix33(m_vA1, m_vA2, m_vA3); };
  void GetOriginAndTV(Vector3& vA0, Vector3& vA1, Vector3& vA2, Vector3& vA3);
  void SetOriginAndTV(Vector3& vA0, Vector3& vA1, Vector3& vA2, Vector3& vA3);
  void GetReciprocalVectors(Vector3& vB1, Vector3& vB2, Vector3& vB3) const;
  double GetVolume();
  Matrix33 GetMatR2F() const;
  Matrix33 GetMatF2R() const;
  Vector3 GetPosF2R(const Vector3& v) const;
  Vector3 GetPosR2F(const Vector3& v) const;
  Vector3 GetLength() const;
  Vector3 GetAngle() const;
  int GetSymCount() const;
  SymOper GetSymOper(int index) const;
  void AddSymOper(SymOper sym);
  void Print() const;

private:
  void GenerateMatrix();
};


