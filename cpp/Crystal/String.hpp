#pragma once

#include <string>
#include <vector>

using namespace std;

namespace String
{
  bool Trim(string& str, const string& key = " \t\r\n");
  vector<string> Split( const string& str, const string& delimiter );
  string ToUpperCase(const string& str);
  string ToLowerCase(const string& str);
  double StrToFloat(const string& s);
  int StrToInt(const string& s);
  string IntToStr(int i);
  string FloatToStr(double f);
};


