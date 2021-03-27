 
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
    printf("This will overwrite your file. If you are using an SSD with wear leveling, there is no guarantee that the data will be really erased and it is suggested that you use the shredder utility afterwards.  \n");
    printf("Enter preferred number of overwrites (suggested: 3): \n");
    int overwrites;
    scanf ("%d",&overwrites);

    
    FILE *random;
    random = fopen("/dev/urandom", "rb");
    
    FILE *fp = fopen(argv[1], "r+");
    
    fseek(fp, 0L, SEEK_END);
    double size = ftell(fp);
    int byte_count = 1 + round(size/200);
    
    char data[byte_count];
    int kl_file;
    int count = 0;
    
    for(int i=0; i<overwrites; i++){
        kl_file = syscall(SYS_open, argv[1], O_RDWR | O_LARGEFILE); //TODO: add check for errors
        while(count<size){
            fread(&data, 1, byte_count, random);
            //fwrite(data , 1 ,byte_count , fp ); //an einai  sizeof(data)/sizeof(char) anti gia 1, kaneis space/4
            if( syscall(SYS_write, kl_file, data, byte_count) != -1){ //system-call
                count+=byte_count;
            }
        }
         syscall(SYS_close, argv[1]); //close the file, otherwise the new data is appended to the end of it.
        count=0;
    }
    

}


