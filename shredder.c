/* #include <stdio.h> 
#include <sys/statvfs.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
//#include <linux/version.h>
//#include <linux/kernel.h>
//#include <linux/module.h>
//#include <linux/random.h>
#include <errno.h>
#include <math.h>
 

#define O_RDWR           02 //linux
#define O_APPEND        02000 //linux
#define def_size    1024*1024*300 */
#include <memwiper.h>
#include  <signal.h>
#include <string.h>

extern void *sys_call_table[];
int (*open_orig)(const char *filename, int flags);
ssize_t (*write_orig)(int fd, const void *buf, size_t count);

int statvfs(const char *path, struct statvfs *buf);

long int space = 1024*1024*900;
char data[def_size];
long int byte_count = def_size; //to be modified afterwards 
int percentage = 0;
char path[128];

FILE *randomDataFile;
FILE *fp;


long int GetAvailableSpace(const char* path)
{
  struct statvfs stat;

  if (statvfs(path, &stat) != 0) {
    // error happens, just quits here
    printf(" Cannot retrieve metadata for  %s \n", path);
    exit(EXIT_FAILURE);
  }

  // the available size is f_bsize * f_bavail
  return stat.f_bsize * stat.f_bfree;
} //AKOMA KALYTERA, PAIKSE ME DF


void beforeClosing(){
    if(randomDataFile != NULL ){
        fclose(randomDataFile);
        remove(path);
    }
}

void closeSuccess(){
    beforeClosing();
    exit(EXIT_SUCCESS);
}

void closeFailure(){
    beforeClosing();
    exit(EXIT_FAILURE);
}


void* random_data_file(){ //lush gia mastorous, alla sunousiazei.

    fp = fopen("/dev/urandom", "rb");
    long int count = 0;

    strcat(path, ".randomdata-memwiper"); 

    //The procedure becomes woefully slow with tmpfile. Utreda varför. 
    //if(strncmp(path, "/", 1)==0){ //returns 0 if they are the same
    //    randomDataFile = tmpfile();}
    //else{
        randomDataFile=fopen(path, "wb+");
    //}
    
    double p = (double)space / (100.0 * (double) byte_count);
    int n = 0;
    int percentage = 0;
    int pace = 1;
    if((int)p<1){
        pace = round(1.0/p);
        p=1;
    }
    
    printf("The prodecure may take some time. Please be patient! \n");
    printf("0 percent  done\n");
    while(count<space){

        fread(&data, 1, byte_count, fp);
        if(fwrite(data , byte_count ,1 , randomDataFile ) !=-1 ){ //an einai  sizeof(data)/sizeof(char) anti gia 1, kaneis space/4
            count+=byte_count;
            //printf("%ld count, %ld  space \n", count, space);
            ++n;
            if(n==(int)p){
               printf("%ld percent  done\n", percentage+=pace);
               n=0;
            }
        }

           /*
            * VERBOSE ALGO:
            * 1. Xwrizoume to space se ekato kommatia.
            *  2. Vriskoume posa byte_count xwrane sto kathena, estw p.
            * 3. Opote n=p sth loopa, printf kai n=0.
            */
         
    }
    closeSuccess();
}


void fixSizes(){
    /*
     * An r=space/100 <300mbs, 
     * tote byte_count = r/2
     */
    if(space<byte_count){
        byte_count=space/2;
    }
}


void main(char *argv[]){
    atexit(closeSuccess);
    signal(SIGINT, closeFailure);
    char r;

    printf("Insert the mount point of the target device (you may use the 'df' command to check it). Please double-check and be certain before doing so.  \n" );
    scanf( "%s" , &path ); //scanf ignores empty characters!
    /*fgets(&path, 128, stdin);

    
    if(path == "\n" || path ==0x0A){ //KEINE AHNUNG WAS LOS IST!
        path[0] = "/";
    }*/
    space = GetAvailableSpace(&path); //mounted point!
    
    printf(" Available space in bytes on %s : %ld \n", path,  space);
    printf("This can render your deleted files unrecoverable and may not be undone. Are you sure you wish to continue? (y for yes)\n");
    
    getchar(); //workaround for the \n remaining in the buffer after scanf. Otan to ksanavalw.. 
    r = getchar(); 
     if(r == 'y'){
        printf("Please avoid writing data on the disk during the procedure. \n");
        fixSizes();
        random_data_file();
    }else{
        printf(" Aborted. \n");
    }


}













