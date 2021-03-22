 
#include <stdio.h> 
#include <sys/statvfs.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/syscall.h>
 #include <sys/types.h>
#include <math.h>


#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/random.h>
#include <errno.h>
#include <math.h>

#define O_RDWR           02 //linux
#define O_APPEND        02000 //linux
#define O_LARGEFILE 0 //linux

void main(int argc, char **argv){
    FILE *random;
    random = fopen("/dev/urandom", "rb");
    
    FILE *fp = fopen(argv[1], "r+");
    
    fseek(fp, 0L, SEEK_END);
    double size = ftell(fp);
    int byte_count = 1 + round(size/200);
    char data[byte_count];
    int kl_file  = syscall(SYS_open, argv[1], O_RDWR | O_LARGEFILE); 
    int count = 0;
    while(count<size){

        fread(&data, 1, byte_count, random);
        syscall(SYS_write, kl_file, data, byte_count); //system-call
        //fwrite(data , 1 ,byte_count , fp ); //an einai  sizeof(data)/sizeof(char) anti gia 1, kaneis space/4
        count+=byte_count;
        
    }
    
    

}


