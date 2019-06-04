#include "FileReader.hpp"
#include <iostream>
#include <fstream>

vector<string> FileReader::ReadFile(const string& sFilePath) {
  ifstream ifs(sFilePath.c_str());
  vector<string> vs;
  string str;

  if( ifs.fail() ) {
    cout << "Failed to read " << sFilePath << endl;
  }

  while( getline(ifs, str) ) {
    vs.push_back(str);
  }

  return vs;
}
