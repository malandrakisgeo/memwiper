#include <stdio.h> 
#include <sys/statvfs.h>
#include <stdlib.h>
#include <stdbool.h>


int statvfs(const char *path, struct statvfs *buf);

long int space = 10

24*1000;
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

int random_data_file() //lush gia mastorous
{

    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    long int count = 0;

    FILE *rand;
    rand=fopen("randomdata2.txt", "w+");

    while(count<=space){
            int byte_count = 1024; //1024
            
        char data[1024];
        fread(&data, 1, byte_count, fp);
        fprintf(rand, data);
        count+=byte_count;
        printf("%ld\n",  count);
    }
    
    
    fclose(rand);
}


void main(char *argv[]){
    long m = GetAvailableSpace("/"); //mounted point!
    printf("%ld\n",  m);
    //space = 1024*1000;
    if (!initialized) {
        initialized = true;
        random_data_file();
   // do the initialization part
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


















