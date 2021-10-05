#include <memwiper.h>

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
    int byte_count = 1 + round(size/200); //Not error-safe. A mechanic's , but not an engineer's way. TODO: something about that
    
    char data[byte_count];
    int kl_file;
    int count = 0;
    
    for(int i=0; i<overwrites; i++){
        kl_file = syscall(SYS_open, argv[1], O_RDWR | O_LARGEFILE); //TODO: add error check
        while(count<size){
            fread(&data, 1, byte_count, random);
            //fwrite(data , 1 ,byte_count , fp ); //an einai  sizeof(data)/sizeof(char) anti gia 1, kaneis space/4
            if( syscall(SYS_write, kl_file, data, byte_count) != -1){ //system-call
                count+=byte_count;
            }
        }
         syscall(SYS_close, argv[1]); //close the file, otherwise the new data is appended to its' end.
        count=0;
    }
    

}


