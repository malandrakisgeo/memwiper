#define _GNU_SOURCE
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHUNKSIZE 10*2048*sizeof(char)

int sysinfo(struct sysinfo *info);
long ramchunks;
    
//struct sysinfo {
               //long uptime;             /* Seconds since boot */
               //unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
               //unsigned long totalram;  /* Total usable main memory size */
               //unsigned long freeram;   /* Available memory size */
               //unsigned long sharedram; /* Amount of shared memory */
               //unsigned long bufferram; /* Memory used by buffers */
               //unsigned long totalswap; /* Total swap space size */
               //unsigned long freeswap;  /* swap space still available */
              // unsigned short procs;    /* Number of current processes */
              // unsigned long totalhigh; /* Total high memory size */
              // unsigned long freehigh;  /* Available high memory size */
            //   unsigned int mem_unit;   /* Memory unit size in bytes */
            //   char _f[20-2*sizeof(long)-sizeof(int)]; /* Padding to 64 bytes */
//};





void memwiper(){
    //char *cmd = "/proc/meminfo";
    //FILE *cmdfile = popen(cmd, "r");
    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    
    char* data = (char *) calloc( 1, CHUNKSIZE);//sets all bits to zero! . Can be up to 64kbs
    
    /*
     * The program is expected to crush as soon as calloc returns NULL due to lack of available space.
     * Though highly unlikely (check the manuals of calloc about that), it is probable that that calloc will return NULL
     * despite the existence of available space in ram. Hence the while(1) in the calling loop:
     * this program will run until RAM is exhausted, thereby crushing the system. 
     
    */
    
    //TODO: Change RLIMIT_AS limit. 
    //while(NULL != calloc(5, 2048*sizeof(char))){
    while((data = calloc(1, CHUNKSIZE)) != NULL){
          fread(&data[0], 1, 2048, fp); //Overwrites RAM with random data. 2kbs everytime. 
    }
    return;
}



int main(void) {
    struct sysinfo info;

    long localRamValue;
    
    if(sysinfo(&info) > -1){
        localRamValue = info.freeram;
    } else{
        return 0;
    }
    
    struct rlimit old_lim, lim, new_lim;

    if( getrlimit(RLIMIT_DATA, &old_lim) == 0)
        printf("Old limits -> soft limit= %ld \t"
           " hard limit= %ld \n", old_lim.rlim_cur, 
                                 old_lim.rlim_max);
    
    while(1){ //Check the comments in memwiper for the rationale. 
        memwiper(); 
    }
    

} 






