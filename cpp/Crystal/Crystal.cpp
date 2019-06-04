#include "Crystal.hpp"

using namespace String;

vector<Atom> Crystal::SymmetryOperation(const Cell& cell, const vector<Atom>& Asyms) {
  vector<Atom> Symms;
  int nSym = cell.GetSymCount();
  int nAsm = (int)Asyms.size();
  Symms.resize(nAsm*nSym);
  for(int i=0; i < nSym; ++i) {
    SymOper sym = cell.GetSymOper(i);
    Matrix33 m = sym.GetMatrix();
    Vector3  v = sym.GetVector();
    for(int j = 0; j < nAsm; ++j) {
      Atom a = Asyms[j];
      Vector3 vP = a.GetPos();
      vP = m * vP;
      vP = vP + v;
      a.SetPos(vP);
      Symms[i * nAsm + j] = a;
    }
  }
  return Symms;
}

vector<Atom> Crystal::Dedupe(const Cell& cell, const vector<Atom>& Atoms, int nAsym) {
  vector<Atom> Atoms0, Atoms1, Atoms2;
  for(int i = 0; i < nAsym; ++i) {
    Atoms0.push_back(Atoms[i]);
  }
  for(int i = nAsym; i < (int)Atoms.size(); ++i) {
    Atoms1.push_back(Atoms[i]);
  }
  Atoms1 = DedupeAtomsSelf(cell, Atoms1);
  Atoms1 = DedupeAtomsBy  (cell, Atoms0, Atoms1);

  Atoms2.resize(nAsym + (int)Atoms1.size());
  for(int i = 0; i < nAsym; ++i) {
    Atoms2[i] = Atoms0[i];
  }
  for(int i = 0; i < (int)Atoms1.size(); ++i) {
    Atoms2[nAsym+i] = Atoms1[i];
  }
  return Atoms2;
}

// Dedupe overlaped atoms in Atoms
vector<Atom> Crystal::DedupeAtomsSelf(const Cell& cell, const vector<Atom>& Atoms) {
  Matrix33 mat = cell.GetMatF2R();
  vector<Atom> Deduped;
  vector<bool> bOverlap;
  int nAtom = Atoms.size();
  bOverlap.resize(nAtom);
  for(int i = 0; i < nAtom; ++i) {
    bOverlap[i] = false;
  }
  for(int i = 0; i < nAtom; ++i) {
    if( bOverlap[i] ) continue;
    Atom ai = Atoms[i];
    Vector3 vi = ai.GetPos();
    vi = mat * vi;
    for(int j = i + 1; j < nAtom; ++j) {
      if( bOverlap[j] ) continue;
      Atom aj = Atoms[j];
      Vector3 vj = aj.GetPos();
      vj = mat * vj;
      Vector3 v = vi - vj;
      double d = v * v;
      if(d < 0.1) {
        bOverlap[j] = true;
      }
    }
  }
  for(int i = 0; i < nAtom; ++i) {
    Atom a = Atoms[i];
    if( !bOverlap[i] )
      Deduped.push_back(a);
  }
  return Deduped;
}

// Remove atoms in Atoms1 that overlap with atoms in Atom0
vector<Atom> Crystal::DedupeAtomsBy(const Cell& cell,
				    const vector<Atom>& Atoms0,
				    const vector<Atom>& Atoms1) {
  Matrix33 mat = cell.GetMatF2R();
  vector<Atom> Deduped;
  vector<bool> bOverlap;
  int nAtom0 = Atoms0.size();
  int nAtom1 = Atoms1.size();
  bOverlap.resize(nAtom1);
  for(int i = 0; i < nAtom1; ++i) {
    bOverlap[i] = false;
  }
  for(int i = 0; i < nAtom0; ++i) {
    Atom ai = Atoms0[i];
    Vector3 vi = ai.GetPos();
    vi = mat* vi;
    for(int j = 0; j < nAtom1; ++j) {
      if( bOverlap[j] ) continue;
      Atom aj = Atoms1[j];
      Vector3 vj = aj.GetPos();
      vj = mat * vj;
      Vector3 v = vi - vj;
      double d = v * v;
      if(d < 0.1) {
        bOverlap[j] = true;
      }
    }
  }
  for(int i = 0; i < nAtom1; ++i) {
    Atom a = Atoms1[i];
    if( !bOverlap[i] ) Deduped.push_back(a);
  }
  return Deduped;
}

