#include "Atom.hpp"

Atom::Atom()
  : m_number(-1), m_position(0.0, 0.0, 0.0), m_occupancy(1.0)
{
}

Atom::Atom(int n, double x, double y, double z, double occupancy)
  : m_number(n), m_position(x, y, z), m_occupancy(occupancy)
{
}

void Atom::SetPos(Vector3 v) {
  m_position = v;
}

Vector3 Atom::GetPos() const {
  return m_position;
}

void Atom::SetNumber(int n_) {
  m_number = n_;
}

int Atom::GetNumber() const {
  return m_number;
}

void Atom::SetOccupancy(double d) {
  m_occupancy = d;
}

double Atom::GetOccupancy() const {
  return m_occupancy;
}


int Atom::AtomicNumber(string s) {
  transform(s.begin(), s.end(), s.begin(), ::toupper);
  if(s == "H" ) return  1;
  if(s == "HE") return  2;
  if(s == "LI") return  3;
  if(s == "BE") return  4;
  if(s == "B" ) return  5;
  if(s == "C" ) return  6;
  if(s == "N" ) return  7;
  if(s == "O" ) return  8;
  if(s == "F" ) return  9;
  if(s == "NE") return 10;
  if(s == "NA") return 11;
  if(s == "MG") return 12;
  if(s == "AL") return 13;
  if(s == "SI") return 14;
  if(s == "P" ) return 15;
  if(s == "S" ) return 16;
  if(s == "CL") return 17;
  if(s == "AR") return 18;
  if(s == "K" ) return 19;
  if(s == "CA") return 20;
  if(s == "SC") return 21;
  if(s == "TI") return 22;
  if(s == "V" ) return 23;
  if(s == "CR") return 24;
  if(s == "MN") return 25;
  if(s == "FE") return 26;
  if(s == "CO") return 27;
  if(s == "NI") return 28;
  if(s == "CU") return 29;
  if(s == "ZN") return 30;
  if(s == "GA") return 31;
  if(s == "GE") return 32;
  if(s == "AS") return 33;
  if(s == "SE") return 34;
  if(s == "BR") return 35;
  if(s == "KR") return 36;
  if(s == "RB") return 37;
  if(s == "SR") return 38;
  if(s == "Y" ) return 39;
  if(s == "ZR") return 40;
  if(s == "NB") return 41;
  if(s == "MO") return 42;
  if(s == "TC") return 43;
  if(s == "RU") return 44;
  if(s == "RH") return 45;
  if(s == "PD") return 46;
  if(s == "AG") return 47;
  if(s == "CD") return 48;
  if(s == "IN") return 49;
  if(s == "SN") return 50;
  if(s == "SB") return 51;
  if(s == "TE") return 52;
  if(s == "I" ) return 53;
  if(s == "XE") return 54;
  if(s == "CS") return 55;
  if(s == "BA") return 56;
  if(s == "LA") return 57;
  if(s == "CE") return 58;
  if(s == "PR") return 59;
  if(s == "ND") return 50;
  if(s == "PM") return 61;
  if(s == "SM") return 62;
  if(s == "EU") return 63;
  if(s == "CD") return 64;
  if(s == "TB") return 65;
  if(s == "DY") return 66;
  if(s == "HO") return 67;
  if(s == "ER") return 68;
  if(s == "TM") return 69;
  if(s == "YB") return 70;
  if(s == "LU") return 71;
  if(s == "HF") return 72;
  if(s == "TA") return 73;
  if(s == "W" ) return 74;
  if(s == "RE") return 75;
  if(s == "OS") return 76;
  if(s == "IR") return 77;
  if(s == "PT") return 78;
  if(s == "AU") return 79;
  if(s == "HG") return 80;
  if(s == "TL") return 81;
  if(s == "PB") return 82;
  if(s == "BI") return 83;
  if(s == "PO") return 84;
  if(s == "AT") return 85;
  if(s == "RN") return 86;
  if(s == "FR") return 87;
  if(s == "RA") return 88;
  if(s == "AC") return 89;
  if(s == "TH") return 90;
  if(s == "PA") return 91;
  if(s == "U" ) return 92;
  if(s == "NP") return 93;
  if(s == "PU") return 94;
  if(s == "AM") return 95;
  if(s == "CM") return 96;
  if(s == "BK") return 97;
  if(s == "CF") return 98;
  if(s == "ES") return 99;
  if(s == "FM") return 100;
  if(s == "MD") return 101;
  if(s == "NO") return 102;
  if(s == "LR") return 103;

  if(s == "RF") return 104;
  if(s == "DB") return 105;
  if(s == "SG") return 106;
  if(s == "BH") return 107;
  if(s == "HS") return 108;
  if(s == "MT") return 109;
  if(s == "DS") return 110;
  if(s == "RG") return 111;
  if(s == "CN") return 112;
  return 0;
}

string Atom::AtomicSymbol(int i) {
  switch(i) {
  case   1: return "H";
  case   2: return "He";
  case   3: return "Li";
  case   4: return "Be";
  case   5: return "B";
  case   6: return "C";
  case   7: return "N";
  case   8: return "O";
  case   9: return "F";
  case  10: return "Ne";
  case  11: return "Na";
  case  12: return "Mg";
  case  13: return "Al";
  case  14: return "Si";
  case  15: return "P";
  case  16: return "S";
  case  17: return "Cl";
  case  18: return "Ar";
  case  19: return "K";
  case  20: return "Ca";
  case  21: return "Sc";
  case  22: return "Ti";
  case  23: return "V";
  case  24: return "Cr";
  case  25: return "Mn";
  case  26: return "Fe";
  case  27: return "Co";
  case  28: return "Ni";
  case  29: return "Cu";
  case  30: return "Zn";
  case  31: return "Ga";
  case  32: return "Ge";
  case  33: return "As";
  case  34: return "Se";
  case  35: return "Br";
  case  36: return "Kr";
  case  37: return "Rb";
  case  38: return "Sr";
  case  39: return "Y";
  case  40: return "Zr";
  case  41: return "Nb";
  case  42: return "Mo";
  case  43: return "Tc";
  case  44: return "Ru";
  case  45: return "Rh";
  case  46: return "Pd";
  case  47: return "Ag";
  case  48: return "Cd";
  case  49: return "In";
  case  50: return "Sn";
  case  51: return "Sb";
  case  52: return "Te";
  case  53: return "I";
  case  54: return "Xe";
  case  55: return "Cs";
  case  56: return "Ba";
  case  57: return "La";
  case  58: return "Ce";
  case  59: return "Pr";
  case  60: return "Nd";
  case  61: return "Pm";
  case  62: return "Sm";
  case  63: return "Eu";
  case  64: return "Gd";
  case  65: return "Tb";
  case  66: return "Dy";
  case  67: return "Ho";
  case  68: return "Er";
  case  69: return "Tm";
  case  70: return "Yb";
  case  71: return "Lu";
  case  72: return "Hf";
  case  73: return "Ta";
  case  74: return "W";
  case  75: return "Re";
  case  76: return "Os";
  case  77: return "Ir";
  case  78: return "Pt";
  case  79: return "Au";
  case  80: return "Hg";
  case  81: return "Tl";
  case  82: return "Pb";
  case  83: return "Bi";
  case  84: return "Po";
  case  85: return "At";
  case  86: return "Rn";
  case  87: return "Fr";
  case  88: return "Ra";
  case  89: return "Ac";
  case  90: return "Th";
  case  91: return "Pa";
  case  92: return "U";
  case  93: return "Np";
  case  94: return "Pu";
  case  95: return "Am";
  case  96: return "Cm";
  case  97: return "Bk";
  case  98: return "Cf";
  case  99: return "Es";
  case 100: return "Fm";
  case 101: return "Md";
  case 102: return "No";
  case 103: return "Lr";

  case 104: return "Rf";
  case 105: return "Db";
  case 106: return "Sg";
  case 107: return "Bh";
  case 108: return "Hs";
  case 109: return "Mt";
  case 110: return "Ds";
  case 111: return "Rg";
  case 112: return "Cn";

  default:   return "Dummy";
  }
}
