///
/// This file was generated using **holghol**
/// Version: 0.1.0
/// Find more on: https://gitlab.com/lpg2709/<repo>
///
/// # HOLGHOL
///
/// ## Contents
/// 1. About
/// 2. Features
/// 3. Usage
/// 4. Example
/// 5. API
/// 6. Credits
/// 7. Changelog
/// 6. License
///
/// ## About
/// TODO
///
/// ## Features
/// TODO
///
/// ## Usage
/// TODO
///
/// ## Example
/// TODO
///
/// ## API
///

#ifdef HOLGHOL_IMPLEMENTATION

#ifndef HOLGHOL_H
#define HOLGHOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                                   HELPER                                   *
 ******************************************************************************/
#define GHOL_ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#define GHOL_PINFO(fmt, ...) fprintf(stdout, "[INFO]: " fmt, __VA_ARGS__);
#define GHOL_PERROR(fmt, ...) fprintf(stderr, "[ERROR]: " fmt, __VA_ARGS__);
#define GHOL_VERSION_MAJOR 0
#define GHOL_VERSION_MINOR 1
#define GHOL_VERSION_MICRO 0

#define GHOL_STRINGIFY0(s) # s
#define GHOL_STRINGIFY(s) GHOL_STRINGIFY0(s)
#define GHOL_VERSION GHOL_STRINGIFY(GHOL_VERSION_MAJOR) "." GHOL_STRINGIFY(GHOL_VERSION_MINOR) "." GHOL_STRINGIFY(GHOL_VERSION_MICRO)

/******************************************************************************
 *                                    FILE                                    *
 ******************************************************************************/
const char* _gholFileOpen(const char *filepath, size_t *filesize);
bool _gholFileCreate(const char *filepath, const char *content, size_t content_size);
bool _gholFileAppend(const char *filepath, const char *content, size_t content_size);
bool _gholFileExist(const char *filepath);
void _gholFileAppendOrCreateStdout(const char *filepath, const char *content, size_t content_size);

/******************************************************************************
 *                                   UTILS                                    *
 ******************************************************************************/
const char* _gholRemoveIncludes(const char *string, size_t ssize, const char **files, size_t length);

/******************************************************************************
 *                                    CORE                                    *
 ******************************************************************************/
void gholPlainFile(const char *files[], size_t length, const char* outfile);
void gholLibFile(const char *files[], size_t length, const char *includes[], size_t len_includes, const char* outfile);
void gholCredits(const char* outfile);
void gholIfdefine(const char* prefix, const char *outfile);
void gholEndif(const char* prefix, const char *outfile);

#ifdef __cplusplus
}
#endif

#endif // HOLGHOL_H
                    

void gholPlainFile(const char *files[], size_t length, const char* outfile) {
	int i = 0;
	bool saveToFile = false;
	for(i = 0; i < length; i++) {
		if(!_gholFileExist(files[i])) {
			GHOL_PERROR("Plain text file not found: %s\n", files[i]);
			continue;
		}
		size_t file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		_gholFileAppendOrCreateStdout(outfile, file_content, file_size);
		free(file_content);
	}
}

void gholLibFile(const char *files[], size_t length, const char *includes[], size_t len_includes, const char* outfile) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(!_gholFileExist(files[i])) {
			GHOL_PERROR("Plain text file not found: %s\n", files[i]);
			continue;
		}
		size_t file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		const char * new_content = _gholRemoveIncludes(file_content, file_size, includes, len_includes);
		free(file_content);
		_gholFileAppendOrCreateStdout(outfile, new_content, file_size);
		free((void*)new_content);
	}
}

void gholCredits(const char* outfile) {
#define _GHOL_CREDIDS_STRING "///\n" \
	"/// This file was generated using **holghol**\n" \
	"/// Version: " GHOL_VERSION "\n" \
	"/// Find more on: https://gitlab.com/lpg2709/<repo>\n" \
	"///\n"
	size_t nbytes = snprintf(NULL, 0, "%s", _GHOL_CREDIDS_STRING) + 1;
	char* res = (char*) malloc(sizeof(char) * nbytes);
	snprintf(res, nbytes, "%s", _GHOL_CREDIDS_STRING);
	_gholFileAppendOrCreateStdout(outfile, res, nbytes);
#undef _GHOL_CREDIDS_STRING
}

void gholIfdefine(const char* prefix, const char *outfile) {
	const char* template = "\n#ifdef %s_IMPLEMENTATION\n\n";
	size_t nbytes = snprintf(NULL, 0, template, prefix) + 1;
	char* res = (char*) malloc(sizeof(char) * nbytes);
	snprintf(res, nbytes, template, prefix);
	_gholFileAppendOrCreateStdout(outfile, res, nbytes);
	free(res);
}

void gholEndif(const char* prefix, const char *outfile) {
	const char* template = "\n#endif // %s_IMPLEMENTATION\n\n";
	size_t nbytes = snprintf(NULL, 0, template, prefix) + 1;
	char* res = (char*) malloc(sizeof(char) * nbytes);
	snprintf(res, nbytes, template, prefix);
	_gholFileAppendOrCreateStdout(outfile, res, nbytes);
	free(res);
}
                    

const char* _gholFileOpen(const char *filepath, size_t *filesize) {
	FILE *f = fopen(filepath, "r");
	char *filecontent;

	if(f == NULL) {
		GHOL_PERROR("Fail to open the file '%s'\n", filepath);
		exit(EXIT_FAILURE);
	}

	fseek(f, 0L, SEEK_END);
	*filesize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	if(*filesize == 1) {
		GHOL_PERROR("No content on file '%s'\n", filepath);
		exit(EXIT_FAILURE);
	}

	filecontent = (char *) malloc(sizeof(char) * (*filesize));

	if(filecontent == NULL) {
		GHOL_PERROR("Fail to allocate memory for '%s' content!\n", filepath);
		exit(EXIT_FAILURE);
	}

	fread((void*) filecontent, sizeof(char), *filesize, f);

	fclose(f);

	return filecontent;
}

bool _gholFileCreate(const char *filepath, const char *content, size_t content_size) {
	FILE *f = fopen(filepath, "w");
	const char *filecontent;

	if(f == NULL) {
		GHOL_PERROR("Fail to open the file '%s' for write!\n", filepath);
		exit(EXIT_FAILURE);
	}

	int size = fwrite(content, sizeof(char), content_size - 1, f);
	fclose(f);

	if(size < 0) {
		return false;
	}

	return true;
}

bool _gholFileAppend(const char *filepath, const char *content, size_t content_size) {
	FILE *f = fopen(filepath, "a");
	const char *filecontent;

	if(f == NULL) {
		GHOL_PERROR("Fail to open the file '%s' for appending!\n", filepath);
		exit(EXIT_FAILURE);
	}

	int size = fwrite(content, sizeof(char), content_size - 1, f);
	fclose(f);

	if(size < 0) {
		return false;
	}

	return true;
}

bool _gholFileExist(const char *filepath) {
	FILE *file = fopen(filepath, "r");
	if (file != NULL) {
		fclose(file);
		return true;
	}
	return false;
}

void _gholFileAppendOrCreateStdout(const char *filepath, const char *content, size_t content_size) {
	if(filepath != NULL) {
		if(_gholFileExist(filepath)) {
			_gholFileAppend(filepath, content, content_size);
		} else {
			_gholFileCreate(filepath, content, content_size);
		}
	} else {
		fprintf(stdout, "%s", content);
	}
}
                    

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

#endif // HOLGHOL_IMPLEMENTATION

/// ## Changelog
///
/// [date] ([x.y.z]) - [description]
/// - [date]: date on which the change has been pushed
/// - [x.y.z]: Version string, represented in Semantic Versioning format
///   - [x]: Major version with API and library breaking changes
///   - [y]: Minor version with non-breaking API and library changes
///   - [z]: Patch version with no direct changes to the API
///
/// - 2023/11/08 (0.1.0) - ADD first implementation of the API
///
/// ## Credits
///
/// Developed by [Leonardo Padilha Guarezi <lpg2709>](https://gitlab.com/lpg2709).
///
/// ## Contributors
///
/// Contributors of this project:
///
/// [Full Name <nickname>](https://some.link/nick)
///
/// ## License
///
/// MIT License
///
/// Copyright (c) 2023 Leonardo Padilha Guarezi
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
