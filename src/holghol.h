#ifndef HOLGHOL_H
#define HOLGHOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                                   HELPER                                   *
 ******************************************************************************/
#define GHOL_ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#define GHOL_PINFO(fmt, ...) fprintf(stdout, "[INFO]: " fmt, __VA_ARGS__);
#define GHOL_PERROR(fmt, ...) fprintf(stderr, "[ERROR]: " fmt, __VA_ARGS__);

/******************************************************************************
 *                                    FILE                                    *
 ******************************************************************************/
const char* _gholFileOpen(const char *filepath, long *filesize);
bool _gholFileCreate(const char *filepath, const char *content);
bool _gholFileAppend(const char *filepath, const char *content);
bool _gholFileExist(const char *filepath);

/******************************************************************************
 *                                   UTILS                                    *
 ******************************************************************************/
void _gholRemoveIncludes(const char **files);

/******************************************************************************
 *                                    CORE                                    *
 ******************************************************************************/
void gholPlainFile(const char *files[], size_t lenght);
void gholLibFile(const char *files[], size_t lenght);

#ifdef __cplusplus
}
#endif

#endif // HOLGHOL_H
