#pragma once

#include <string>
#include <vector>

using namespace std;

class FileReader {
public:
  static vector<string> ReadFile(const string& sFilePath);
};

