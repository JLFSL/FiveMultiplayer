#include <unordered_map>
#include <iostream>
#include <stdint.h>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

#include"DataStores.h"

int main() {

	std::ofstream updateFile, missingFile;
	updateFile.open("output.txt");
	missingFile.open("missing.txt");

	for (int i = 0; i < currentHashMap.size(); i++) {
		bool found = false;

		for (int n = 0; n < newHashMap.size(); n++) {
			if (currentHashMap[i].current == newHashMap[n].original) {
				found = true;
				updateFile << int_to_hex(currentHashMap[i].original).c_str() << ", " << int_to_hex(newHashMap[n].current).c_str() << ",\n";
				break;
			}
		}

		if (!found) {
			missingFile << int_to_hex(currentHashMap[i].original).c_str() << ", " << int_to_hex(currentHashMap[i].current).c_str() << ",\n";
		}
	}

	updateFile.close();
	missingFile.close();

	int c;
	printf("Press ENTER to continue... ");
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));

	return 0;
}