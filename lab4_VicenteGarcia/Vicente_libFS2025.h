#ifndef VICENTE_LIBFS2025_H
#define VICENTE_LIBFS2025_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_FILES 100
#define MAX_FILENAME 50
#define MAX_FILE_SIZE 1024
#define LINE_SIZE 512

// File system structures
typedef struct {
    char filename[MAX_FILENAME];
    int size;
    int is_open;
} FileEntry;

// Function prototypes
int fileCreate(const char *filename);
int fileOpen(const char *filename);
int fileWrite(int file_index, const char *data);
int fileRead(int file_index);
int fileClose(int file_index);
int fileDelete(const char *filename);

#endif // LIBFS2025_H