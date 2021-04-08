#include <stdio.h> 
#include <sys/statvfs.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/syscall.h>
 #include <sys/types.h>



#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/random.h>
#include <errno.h>



#define O_RDWR           02 //linux
#define O_APPEND        02000 //linux
#define def_size    1024*1024*300
extern void *sys_call_table[];
int (*open_orig)(const char *filename, int flags);
ssize_t (*write_orig)(int fd, const void *buf, size_t count);

int statvfs(const char *path, struct statvfs *buf);

long int space = 1024*1024*230;
int byte_count = def_size; //to be modified afterwards 
char data[def_size];
//char* data; //best strategy for large numbers
int percentage = 0;


pthread_mutex_t lock;
pthread_t tid[1];

bool initialized;

long int GetAvailableSpace(const char* path)
{
  struct statvfs stat;

  if (statvfs(path, &stat) != 0) {
    // error happens, just quits here
    return -1;
  }

  // the available size is f_bsize * f_bavail
  return stat.f_bsize * stat.f_bfree;
} //AKOMA KALYTERA, PAIKSE ME DF

void showPlusFivePercent(){
    percentage+=5; 
    printf("%ld percent done\n",  percentage);
    return;
}

void* random_data_file(){ //lush gia mastorous

        FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    long int count = 0;

    FILE *rand;
    rand=fopen("TMPFILE924", "wb+");
    //rand = tmpfile();
    
    double percentage = 0;
    int n = 1;
    while(count<space){

        fread(&data, 1, byte_count, fp);
        if(fwrite(data , byte_count ,1 , rand ) !=-1 ){ //an einai  sizeof(data)/sizeof(char) anti gia 1, kaneis space/4
            count+=byte_count;
        }
        percentage = (double)count/ (double)space;
        //if((percentage > (double)(0.08*n)) && (percentage < (double)(0.12*n))){
           printf("%lf percent  done\n", percentage*100 );
           // n+=1;
       // }
         
        
        if(percentage*100> (double)80){
            /* 
             * space = GetAvailableSpace("/"); //recheck
             * 
             */
            byte_count= 1024*1024*5;
        }
        
    }
    
    fclose(rand);
}


void main(char *argv[]){
    char path[128];
    char r;

    printf("Press enter for default mount point ('/'). Otherwise, insert the mount point of the device (you may use the 'df' command to check it). Please be certain before doing do.  \n" );
    scanf( "%s" , &path );
    
    if(path == "\n"){
        path[0] = "/";
    }
    space = GetAvailableSpace(&path); //mounted point!
    
    printf(" Available space in bytes on %s : %ld \n", path,  space);
    printf("This can render your deleted files unrecoverable. Are you sure you wish to continue? (y for yes)\n");
    
    getchar(); //workaround for the \n remaining in the buffer after scanf. 
    r = getchar(); 
     if(r == 'y'){
       random_data_file();
    }


}










int random_data_file_simple() //lush gia mastorous
{
    int byte_count = 1024;
    char data[4096];
    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    fread(&data, 1, byte_count, fp);
    int n;

    FILE *rand;
    rand=fopen("randomdata.txt", "w");
    fprintf(rand, data);
    fclose(rand);
}

















