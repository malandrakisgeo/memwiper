#include <stdio.h> 
#include <sys/statvfs.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <math.h>
#include <linux/version.h>
#include <linux/random.h>
#include <math.h>
#include <sys/statvfs.h>

 
 
#define O_RDWR           02 //linux
#define O_APPEND        02000 //linux
#define O_LARGEFILE 0 //linux
#define RANDOM_DATA_GENERATOR "/dev/urandom" //linux

#define def_size    1024*1024*300 
#define CHUNKSIZE 100*2048*sizeof(char)

