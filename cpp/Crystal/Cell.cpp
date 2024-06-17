#include <iostream>
#include "Cell.hpp"

Cell::Cell() : m_vA0(0.0, 0.0, 0.0) {
};

void Cell::SetConstants(double aa, double bb, double cc, double al, double be, double ga) {
  double sin_ga, cos_ga;
  double sin_be, cos_be;
  double cos_al;
  Vector3 vA, vB, vC;
  al = M_PI * al / 180.0;
  be = M_PI * be / 180.0;
  ga = M_PI * ga / 180.0;
  // sin and cos
  sin_ga = sin(ga);
  cos_ga = cos(ga);
  sin_be = sin(be);
  cos_be = cos(be);
  cos_al = cos(al);
  // A axis vector
  m_vA1.x  = aa;
  m_vA1.y  = 0;
  m_vA1.z  = 0;
  // B axis vector
  m_vA2.x  = bb * cos_ga;
  m_vA2.y  = bb * sin_ga;
  m_vA2.z  = 0;
  // C axis vector
  m_vA3.x  = cc * (cos_be);
  m_vA3.y  = cc * (cos_al-cos_be*cos_ga) / sin_ga;
  m_vA3.z  = sqrt(cc*cc*sin_be*sin_be - vC.y*vC.y);
  GenerateMatrix();
}

void Cell::SetConstants(Vector3 vLen, Vector3 vAng) {
  SetConstants(vLen.x, vLen.y, vLen.z, vAng.x, vAng.y, vAng.z);
}

void Cell::SetTranslationVectors(Vector3 vA1, Vector3 vA2, Vector3 vA3) {
  m_vA1 = vA1;
  m_vA2 = vA2;
  m_vA3 = vA3;
  GenerateMatrix();
}

void Cell::GetOriginAndTV(Vector3& vA0, Vector3& vA1, Vector3& vA2, Vector3& vA3) {
  vA0 = m_vA0;
  vA1 = m_vA1;
  vA2 = m_vA2;
  vA3 = m_vA3;
}

void Cell::SetOriginAndTV(Vector3& vA0, Vector3& vA1, Vector3& vA2, Vector3& vA3) {
  m_vA0 = vA0;
  SetTranslationVectors(vA1, vA2, vA3);
}

void Cell::GetTranslationVectors(Vector3& vA1, Vector3& vA2, Vector3& vA3) const {
  vA1 = m_vA1;
  vA2 = m_vA2;
  vA3 = m_vA3;
}

void Cell::GetReciprocalVectors(Vector3& vB1, Vector3& vB2, Vector3& vB3) const {
  Vector3 vA1 = m_vA1;
  Vector3 vA2 = m_vA2;
  Vector3 vA3 = m_vA3;
  double vol = vA1*(vA2^vA3);
  double cst = 2.0 * M_PI / vol;
  vB1 = vA2^vA3*cst;
  vB2 = vA3^vA1*cst;
  vB3 = vA1^vA2*cst;
}

void Cell::GenerateMatrix() {
  m_matF2R.a[0][0] = m_vA1.x; m_matF2R.a[0][1] = m_vA2.x; m_matF2R.a[0][2] = m_vA3.x;
  m_matF2R.a[1][0] = m_vA1.y; m_matF2R.a[1][1] = m_vA2.y; m_matF2R.a[1][2] = m_vA3.y;
  m_matF2R.a[2][0] = m_vA1.z; m_matF2R.a[2][1] = m_vA2.z; m_matF2R.a[2][2] = m_vA3.z;
  m_matR2F = m_matF2R;
  m_matR2F.Inverse();
}

Matrix33 Cell::GetMatR2F() const{
  return m_matR2F;
}

Matrix33 Cell::GetMatF2R() const{
  return m_matF2R;
}

Vector3 Cell::GetPosR2F(const Vector3& v) const{
  return m_matR2F * v;
}

Vector3 Cell::GetPosF2R(const Vector3& v) const{
  return m_matF2R * v;
}

Vector3 Cell::GetLength() const {
  double aa = sqrt(m_vA1*m_vA1);
  double bb = sqrt(m_vA2*m_vA2);
  double cc = sqrt(m_vA3*m_vA3);
  Vector3 v(aa,bb,cc);
  return v;
}

Vector3 Cell::GetAngle() const {
  Vector3 vLen = GetLength();
  double al = acos( (m_vA2 * m_vA3) / (vLen.y * vLen.z) ) * 180.0 / M_PI;
  double be = acos( (m_vA3 * m_vA1) / (vLen.z * vLen.x) ) * 180.0 / M_PI;
  double ga = acos( (m_vA1 * m_vA2) / (vLen.x * vLen.y) ) * 180.0 / M_PI;
  Vector3 v(al,be,ga);
  return v;
}


int Cell::GetSymCount() const {
  return (int)m_SymOpers.size();
}

double Cell::GetVolume() {
  return (m_vA1^m_vA2)*m_vA3;
}

SymOper Cell::GetSymOper(int index) const {
  return m_SymOpers[index];
}

void Cell::AddSymOper(SymOper sym) {
  m_SymOpers.push_back(sym);
}

void Cell::Print() const {
  cout << "a1 " << m_vA1.x << " " << m_vA1.y << " " << m_vA1.z << endl;
  cout << "a2 " << m_vA2.x << " " << m_vA2.y << " " << m_vA2.z << endl;
  cout << "a3 " << m_vA3.x << " " << m_vA3.y << " " << m_vA3.z << endl;

  Vector3 v = GetLength();
  Vector3 u = GetAngle();
  cout << "abc   " << v.x << " " << v.y << " " << v.z << endl;
  cout << "angle " << u.x << " " << u.y << " " << u.z << endl;
}
