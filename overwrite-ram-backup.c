#define _GNU_SOURCE
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

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





void memfetch(){
    //char *cmd = "/proc/meminfo";
    //FILE *cmdfile = popen(cmd, "r");
}



int main(void) {
    struct sysinfo info;

    long localRamValue;
    
    if(sysinfo(&info) > -1){
        localRamValue = info.freeram;
    } else{
        return 0;
    }
    ramchunks = (localRamValue/2048) ; //2048 chunks, each equal to availableram/2048 bytes
    
    char* data = (char *) calloc( ramchunks, 2048*sizeof(char));//sets all bits to zero!
    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    char your_buffer[2048];
    int buffer_size = 2048;
    
    //fwrite(&data,2048*sizeof(char),ramchunks, fp); //3os
    //read(&fp, &data, sizeof data); //4os
    //arc4random_buf(&data, sizeof data); //5os -lbsd
    int fd = open("/dev/urandom", 02);
    FILE *rand=fopen("randomdatadd2", "wb+");
    char name[10] = {'c','o','d','e','\n'};      
    for(int i=0; i<ramchunks; i++){
        //read(fd, data[i], 2048);
         //fread(&data[i], 1, ramchunks, fp); //2os
         //memcpy(&data[i], fp, 2048); //1os
        
        fread(&data[i], 1, 2048, fp);//6os - doulevei!
        
        //fwrite(&data[i] , 2048 ,1 , rand ) ; //TEKMHRIWSH
        //fwrite(name , 10 ,1 , rand ) ; //TEKMHRIWSH
    }
    sysinfo(&info);
    long ramnow = info.freeram;
    printf("ramnow %ld \n", ramnow );

} 






