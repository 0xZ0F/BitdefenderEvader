#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int main(void)
{
	static const char filename[] = "ExcludeMgr.xml";
	FILE *file = fopen(filename, "r");
	char *Exclusions[11];
	Exclusions[10] = 0;
	int eIndexCounter = -1;

	if (file != NULL) {
		char line[128]; // Max line size
		while (fgets(line, sizeof line, file) != NULL) // Read line
		{
			if (strstr(line, "ExcludeItem") != NULL && eIndexCounter != 9) {
				eIndexCounter++;
				Exclusions[eIndexCounter] = line;
			}
		}
		fclose(file);
	}
	else {
		perror(filename);
	}

	for (int i = 0; i < sizeof(Exclusions) / sizeof(Exclusions[i]); i++) {
		printf(Exclusions[i]);
	}

	getchar();
	return 0;
}