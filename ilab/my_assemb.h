#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
const int Label_name_size = 20;
const int labels_size = 16;
const int max_pointer = 8;
typedef struct mark {int pointer; char* name;} mark_t;
int assemb(mark_t* labels, const char* bufin, char* bufout, int stat);