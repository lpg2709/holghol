#include "holghol.h"

const char* _gholRemoveIncludes(const char *string, size_t ssize, const char **files, size_t length) {
    int i = 0;
    char *output = (char*) malloc(sizeof(char) * ssize);
    memset(output, 0, ssize);
	const char *include = "include \"";
	strncpy(output, string, ssize);

	if(length > 0) {
		int j = 0;
		char c = output[j];
		int start = -1;
		int end = -1;
		while(c != '\0') {
			switch(c) {
				case '#':
					{
                        start = j;
						int k = 0;
						char kc = include[k];
						c = output[++j];
						for(k = 0; kc != '\0'; ) {
							if(c != kc) {
								break;
							}
							c = output[++j];
							kc = include[++k];
						}

						if(kc == '\0') {
							for(i = 0; i < length; i++) {
								k = 0;
								kc = files[i][k];
								for(k = 0; kc != '\0'; ) {
									if(c != kc) {
										break;
									}
									c = output[++j];
									kc = files[i][++k];
								}
								if(kc == '\0') {
									end = ++j;
									int r = start;
									for(; r < end; r++) {
										output[r] = (char) ' ';
									}
									break;
								}
							}
						}
						break;
					}
				default:
					j++;
					break;
			}
			c = string[j];
		}
	}

	return output;
}

