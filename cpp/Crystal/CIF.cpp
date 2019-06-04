#include <sstream>
#include <iomanip>
#include <fstream>

#include "CIF.hpp"
#include "FileReader.hpp"

using namespace std;
using namespace String;

bool CIF::Read(const string& sFilePath, Cell& cell, vector<Atom>& Atoms) {
  string sHM, sIT, sCL, sSY, sAT;
  vector<string> vsLines = FileReader::ReadFile(sFilePath);
  if( vsLines.empty() ) return false;
  GetSections(vsLines, sHM, sIT, sCL, sSY, sAT);
  ReadCell(sCL, cell);
  ReadSymm(sSY, cell);
  ReadAtom(sAT, Atoms);
  return true;
}

void CIF::GetSections(const vector<string>& vsLines,
		      string& sHM, string& sIT, string& sCL,
		      string& sSY, string& sAT) {
  // flags
  bool bLoop = false;
  bool bLoop_symmetry  = false;
  bool bLoop_atom_site = false;

  // Read and decompose file
  for(unsigned int i = 0; i < vsLines.size(); ++i) {
    string sLine = vsLines[i];
    Trim(sLine);

    // Read loop_
    if(sLine.find("loop_") != string::npos) {
      bLoop = true;
      bLoop_symmetry  = false;
      bLoop_atom_site = false;
    }

    // Read Hermann-Mauguin symbol
    if(sLine.find("_symmetry_space_group_name_H-M") != string::npos) {
      sHM = sLine;
    }
    // Read International Table number
    if(sLine.find("_space_group_IT_number"     ) != string::npos || 
      sLine.find("_symmetry_Int_Tables_number") != string::npos) {
      sIT = sLine;
    }
    // Read _cell_length_ and _cell_angle
    if(sLine.find("_cell_length_a"    ) != string::npos ||
       sLine.find("_cell_length_b"    ) != string::npos ||
       sLine.find("_cell_length_c"    ) != string::npos ||
       sLine.find("_cell_angle_alpha" ) != string::npos ||
       sLine.find("_cell_angle_beta"  ) != string::npos ||
       sLine.find("_cell_angle_gamma" ) != string::npos ) {
      sCL = sCL + sLine + "\n";	
    }
    
    if(bLoop) {
      // Turned on symmetry flag
      if(sLine.find("_symmetry_equiv_"                  ) != string::npos ||
         sLine.find("_space_group_symop_operation_xyz"  ) != string::npos ) {
        bLoop_symmetry = true;
      }
      // ignore this section
      if(sLine.find("_atom_site_aniso") != string::npos) {
        continue;
      }
      // ignore this section
      if(sLine.find("_geom_angle_atom_site") != string::npos) {
        continue;
      }
      // Turned on atom_site flag
      if(sLine.find("_atom_site_") == 0) {
        bLoop_atom_site = true;
      }
      if(bLoop_symmetry) {
        sSY = sSY + sLine + "\n";
      }
      if(bLoop_atom_site) {
        sAT = sAT + sLine + "\n";
      }
    } // end of loop section
  }
}

void CIF::ReadCell(const string& strIn, Cell& cell) {
  double aa = 0.0;
  double bb = 0.0;
  double cc = 0.0;
  double al = 0.0;
  double be = 0.0;
  double ga = 0.0;

  vector<string> vs = Split(strIn, "\n");
  for (int i=0; i<(int)vs.size(); i++) {
    string sLine = vs[i];
    sLine = DropError(sLine);
    // split column
    vector<string> vsLine = Split(sLine, " ");
    string s = vsLine[1];
    double d = StrToFloat(s);
    if(sLine.find("_cell_length_a"   ) != string::npos) aa = d;
    if(sLine.find("_cell_length_b"   ) != string::npos) bb = d;
    if(sLine.find("_cell_length_c"   ) != string::npos) cc = d;
    if(sLine.find("_cell_angle_alpha") != string::npos) al = d;
    if(sLine.find("_cell_angle_beta" ) != string::npos) be = d;
    if(sLine.find("_cell_angle_gamma") != string::npos) ga = d;
  }
  cell.SetConstants(aa,bb,cc,al,be,ga);
}

void CIF::ReadSymm(const string& strIn, Cell& cell) {
  int iSymID  = 0;
  int iSymXYZ = 0;
  vector<string> vs = Split(strIn, "\n");
  for (int i=0; i<(int)vs.size(); i++) {
    string sLine = vs[i];
    // Read Loop definition of _symmetry_equiv_pos_
    if( sLine.find("_symmetry_equiv_pos_site_id") != string::npos) {
      if(iSymXYZ==0) iSymID=1;
      if(iSymXYZ==1) iSymID=2;
      continue;
    }
    if( sLine.find("_symmetry_equiv_pos_as_xyz"      ) != string::npos ||
        sLine.find("_space_group_symop_operation_xyz") != string::npos
     ) {
      if(iSymID==0) iSymXYZ=1;
      if(iSymID==1) iSymXYZ=2;
      continue;
    }
    string str = ToLowerCase(sLine);
    Trim(str,"\'");
    SymOper sym;
    sym.Set(str);
    cell.AddSymOper(sym);
  }
}

void CIF::ReadAtom(const string& strIn, vector<Atom>& Atoms) {
  // Read Loop definition of _atom_site_
  vector<string> vs_atom_site_def;
  vector<string> vs_atom_site;
  bool bDef = true;
  bool bSymbol = false;
  string stmp = "";

  vector<string> vs = Split(strIn, "\n");
  // get vs_atom_site_def and vs_atom_site
  for(unsigned int i = 0; i < vs.size(); ++i) {
    string sLine = vs[i];
    if(sLine.find("_atom_site_") != string::npos ) {
      vs_atom_site_def.push_back(sLine);
      if(sLine.find("_atom_site_type_symbol") != string::npos )
	bSymbol = true;
    }
    else {
      bDef = false;
    }
    if(!bDef) {
      stmp = stmp + sLine;
      vector<string> vsLine = Split(stmp," ");
      if(vsLine.size() == vs_atom_site_def.size()) {
        vs_atom_site.push_back(stmp);
        stmp="";
      }
    }
  }

  for(unsigned int i = 0; i < vs_atom_site.size(); ++i) {
    string sLine = vs_atom_site[i];
    vector<string> vsLine = Split(sLine, " ");
    string sL, sO, sX, sY, sZ;
    for(unsigned int j = 0; j < vsLine.size(); ++j) {
      string s     = vsLine[j];
      string s_def = vs_atom_site_def[j];
      if(s_def == "_atom_site_type_symbol" &&  bSymbol ) sL = s;
      if(s_def == "_atom_site_label"       && !bSymbol ) sL = s;
      if(s_def == "_atom_site_occupancy"               ) sO = s;
      if(s_def == "_atom_site_fract_x"                 ) sX = s;
      if(s_def == "_atom_site_fract_y"                 ) sY = s;
      if(s_def == "_atom_site_fract_z"                 ) sZ = s;
    }
    sL = DropError(sL);
    sX = DropError(sX);
    sY = DropError(sY);
    sZ = DropError(sZ);
    int n = Atom::AtomicNumber(sL);
    if( ToUpperCase(sL) == "D" ) n = 1;
    Vector3 v;
    v.x = StrToFloat(sX);
    v.y = StrToFloat(sY);
    v.z = StrToFloat(sZ);
    double occupancy = 1.0;
    if( sO != "" ) {
      occupancy = StrToFloat(sO);
    }
    Atom a(n, v.x, v.y, v.z, occupancy);
    Atoms.push_back(a);
  }
}

// drop g of a.bcdef(g)
string CIF::DropError(const string& s) {
  size_t st_Bra = s.find("(");
  if(st_Bra != string::npos) 
    return s.substr(0, st_Bra);
  else
    return s;
}

bool CIF::SaveAsP1(const string& sFilePath, Cell& cell, vector<Atom>& Atoms) {
  stringstream ss;
  Vector3 vLen = cell.GetLength();
  Vector3 vAng = cell.GetAngle();
  ss << "_cell_length_a       " << FloatToStr(vLen.x);
  ss << endl;
  ss << "_cell_length_b       " << FloatToStr(vLen.y);
  ss << endl;
  ss << "_cell_length_c       " << FloatToStr(vLen.z);
  ss << endl;
  ss << "_cell_angle_alpha    " << FloatToStr(vAng.x);
  ss << endl;
  ss << "_cell_angle_beta     " << FloatToStr(vAng.y);
  ss << endl;
  ss << "_cell_angle_gamma    " << FloatToStr(vAng.z);
  ss << endl;
  ss << endl;
  ss << "_symmetry_space_group_name_H-M   \'P 1\'";
  ss << endl;
  ss << "_symmetry_Int_Tables_number      1";
  ss << endl;
  ss << endl;
  ss << "loop_";
  ss << "_symmetry_equiv_pos_as_xyz   ";
  ss << endl;
  ss << "   \'x, y, z\'   ";
  ss << endl;
  ss << endl;
  ss << "loop_";
  ss << endl;
  ss << "_atom_site_label";
  ss << endl;
  ss << "_atom_site_fract_x";
  ss << endl;
  ss << "_atom_site_fract_y";
  ss << endl;
  ss << "_atom_site_fract_z";
  ss << endl;
  for(unsigned int i = 0; i < Atoms.size(); ++i) {
    Atom a = Atoms[i];
    Vector3 v = a.GetPos();
    ss << Atom::AtomicSymbol(a.GetNumber());
    ss << fixed << setw( 15 ) << setprecision( 6 ) << v.x;
    ss << fixed << setw( 15 ) << setprecision( 6 ) << v.y;
    ss << fixed << setw( 15 ) << setprecision( 6 ) << v.z;
    ss << endl;
  }

  ofstream ofs( sFilePath.c_str() );
  if( !ofs )
    return false;
  ofs << ss.str() << endl;
  ofs.close();

  return true;
}
