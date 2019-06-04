#include <iostream>
#include "SymOper.hpp"

using namespace String;

void SymOper::Set(string str) {
  vector<string> vs = Split(str,",");
  for(int i = 0; i < 3; i++) {
    SetEach(i, vs[i]);
  }
}

bool SymOper::SetEach(int idx, string str) {
  double c[3];
  size_t ixyz[3], iw, n;

  double wc0 = 1.0;
  double wc1 = 0.0;
  double wc2 = 0.0;

  ixyz[0] = str.find("x");
  ixyz[1] = str.find("y");
  ixyz[2] = str.find("z");
  iw      = str.find("/");

  for(int i=0; i<3; i++) {
    n = ixyz[i];
    if(n==string::npos)
      c[i]=0.0;
    else
      if(n==0)
        c[i]=1.0;
      else {
        string s = str.substr(n-1,1);
        if(s=="-")
          c[i]= -1.0;
	      else 
	        c[i]=  1.0;
      }
  }
  
  string sw0,sw1,sw2;
  if(iw == string::npos) {
    wc1 = 0.0;
    wc2 = 1.0;
  }
  else {
    if(iw == 0)
      return false;
    if(iw == str.length())
      return false;
    wc0 = 1.0;
    if(iw - 1 != 0)
      sw0 = str.substr(iw-2, 1);
    if(sw0 == "-")
      wc0 = -1.0;
    sw1 = str.substr(iw-1, 1);
    sw2 = str.substr(iw+1, 1);
    wc1 = StrToFloat(sw1);
    wc2 = StrToFloat(sw2);
  }

  for(int i = 0; i < 3; ++i) {
    m_mSym.a[idx][i] = c[i];
  }
  double w = wc0*wc1/wc2;
  if(idx == 0) m_vSym.x = w;
  if(idx == 1) m_vSym.y = w;
  if(idx == 2) m_vSym.z = w;

  return true;
}

Matrix33 SymOper::GetMatrix() {
  return m_mSym;
}

Vector3 SymOper::GetVector() {
  return m_vSym;
}

