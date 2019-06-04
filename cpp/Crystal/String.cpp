#include <sstream>
#include <algorithm>
#include "String.hpp"

namespace String {
  int StrToInt(const string& s) {
    int ret;
    stringstream ss;
    ss << s;
    ss >> ret;
    return ret;
  }

  double StrToFloat(const string& s) {
    double ret;
    stringstream ss;
    ss << s;
    ss >> ret;
    return ret;
  }

  string IntToStr(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
  }

  string FloatToStr(double f) {
    stringstream ss;
    ss << f;
    return ss.str();
  }

  bool Trim(string& str, const string& key) {
    int b = (int)str.find_first_not_of(key.c_str());
    int e = (int)str.find_last_not_of(key.c_str());
    if(b == -1) {
      str = "";
      return false;
    }
    str = string(str, b, e - b + 1);
    return true;
  }

  vector<string> Split( const string& str, const string& delimiter ) {
    vector<string> vstr;
    vstr.clear();
    string::size_type start = 0;
    string::size_type pos( str.find( delimiter ) );
    while( pos != string::npos ) {
      if( pos == start ) {
	++start;
      }
      else {
	vstr.push_back( str.substr(start, pos-start) );
	start = pos + delimiter.length();
      }
      pos = str.find( delimiter, start );
    }
    if( str.length() > start ) {
      vstr.push_back( str.substr(start, str.length()-start) );
    }

    return vstr;
  }

  string ToUpperCase(const string& str) {
    string s = str;
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
  }

  string ToLowerCase(const string& str) {
    string s = str;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
  }
}

