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
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHUNKSIZE 100*2048*sizeof(char)

int sysinfo(struct sysinfo *info);
long ramchunks;
bool randomData = 0;
    

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
     * 
     * You may use watch -d free -m to see it in action!
     
    */
    
    //TODO: Change RLIMIT_AS limit. 
    //while(NULL != calloc(5, 2048*sizeof(char))){
        

    while((data = calloc(1, CHUNKSIZE)) != NULL){
        if(randomData!=0){
            fread(&data[0], 1, CHUNKSIZE, fp); //Overwrites RAM with random data. 200kb everytime. 
        }
    }
    return;
}

void doWhenClosing(){    struct sysinfo info;

     printf("Memory now: %lu \n", info.freeram);

}


int main(int argc, char *argv[]) {
    struct sysinfo info;
    atexit(doWhenClosing);
 printf("Memory now: %ld \n", info.freeram);

    /* 
        //Do on signal: 

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = doWhenClosing;
    sigaction(SIGTERM, &action, NULL); 

    */ 
    signal(SIGTERM, SIG_IGN); //Ignore signal


    if(getopt(argc,argv,"r") != -1){
        randomData = 1;
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






