#ifndef HOLGHOL_H
#define HOLGHOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                                   HELPER                                   *
 ******************************************************************************/
#define GHOL_ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

/******************************************************************************
 *                                    FILE                                    *
 ******************************************************************************/
const char* gholOpenFile(const char *filepath, long *filesize);
bool gholExistFile(const char *filepath);
bool gholCreateFile(const char *filepath, const char *content);

#ifdef __cplusplus
}
#endif

#endif // HOLGHOL_H
