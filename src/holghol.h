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

