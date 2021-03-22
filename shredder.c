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

void* random_data_file() //lush gia mastorous
{
    
    ///pthread_mutex_lock(&lock);
    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    long int count = 0;

    FILE *rand;
    rand=fopen("/home/randomdata2", "wb+");
    //char filename[] = "/tmp/randomdata";
    //int rr=mkstemp(filename);
    
    //int kl_file  = syscall(SYS_open, "randomdata2", O_RDWR | O_APPEND); //system-call
    double percentage = 0;
    int n = 1;
    while(count<space){

        fread(&data, 1, byte_count, fp);
        //syscall(SYS_write, kl_file, data, byte_count); //system-call
        fwrite(data , byte_count ,1 , rand ); //an einai  sizeof(data)/sizeof(char) anti gia 1, kaneis space/4
        percentage = (double)count/ (double)space;
        if((percentage > (double)(0.08*n)) && (percentage < (double)(0.12*n))){
           printf("%lf percent  done\n", percentage*100 );
            n+=1;
        }
         count+=byte_count;

        
        if(percentage*100> (double)80){
            /* 
             * space = GetAvailableSpace("/"); //recheck
             * 
             */
            byte_count= 1024*1024*5;
        }
        
    }
        ///pthread_mutex_unlock(&lock);
    
    fclose(rand);
}


void main(char *argv[]){
    
    
    
    
    
    space = GetAvailableSpace("/"); //mounted point!
    printf(" Available space in '/': %ld \n",  space);
    printf("This can render your deleted files unrecoverable. Are you sure you wish to continue? (y for yes)\n");
    char r;
    r = getchar();
     if(r == 'y'){
       random_data_file();
    }
    
    
    
    //space = 1024*1000;
    ///if (!initialized) {
       /// initialized = true;
        ///pthread_create(&(tid[0]), NULL, &random_data_file, NULL);
        ///pthread_join(tid[0], NULL);
   // do the initialization part
    ///}

}

/*
 * 
 * 	write_orig	= sys_call_table[ SYS_write ];
 * 	open_orig	= sys_call_table[ SYS_open ];
 *  kl_file = open_orig(ul_filename, O_RDWR))
 *   write_orig(kl_file, data, byte_count);
 
 
 */









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



/*void* random_data_file2() //lush gia mastorous
{
    write_orig = sys_call_table[ SYS_write ];
    open_orig = sys_call_table[ SYS_open ];
    
    pthread_mutex_lock(&lock);
    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    long int count = 0;

    FILE *rand;
    rand=fopen("randomdata2", "w+");
    int byte_count = 1024; //1024
            
    char data[byte_count];
    while(count<=space){
        fread(&data, 1, byte_count, fp);
        //fprintf(rand, data);
        int kl_file = open_orig("randomdata2", O_RDWR);
        write_orig(kl_file, data, byte_count);
        count+=byte_count;
        //printf("%ld\n",  count);
        printf("%d\n", sizeof(data) / sizeof(char));
        
    }
        pthread_mutex_unlock(&lock);
    
    fclose(rand);
}*/















