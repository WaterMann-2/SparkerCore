#include "sp_Utility.h"

vector<char> sp_Utility::ReadFile::readBinary(const string& fileName){

	std::ifstream file(fileName, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		DCout(SP_ERROR, "Failed to open file: " + fileName);

		if (file.bad()) DCout(SP_FATAL, "Badbit is set");
		if (file.fail()){
			string message = strerror(errno);
			DCout(SP_ERROR, message);
		}


		return vector<char>();
	}
	else {
		DCout(SP_INFO, "Opened file: " + fileName);
	}

	size_t fileSize = (size_t)file.tellg();
	vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}
