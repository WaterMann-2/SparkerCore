#pragma once

#include "sp_Debug.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using std::vector;
using std::string;
using std::filesystem::path;
using std::filesystem::absolute;
using std::stringstream;

namespace sp_Utility {

	class ReadFile {
	public:
		static vector<char> readBinary(const string& fileName);
	};
}