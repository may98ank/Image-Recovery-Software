#include<stdio.h>
#include <stdint.h>
typedef uint8_t  BYTE;


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Usage: ./recover.c infile\n");
        return 1;
    }
    
    char* mem = argv[1]; 
    FILE *input = fopen(mem,"r");
    
    if(input == NULL)
    {
        fprintf(stderr,"could not open %s.",mem);
        fclose(input);
        return 2;
    }
    int i = 0;
    while(i < 50)
    {
        BYTE bl[512];
        char filename[12];
        fread( bl, 1, 512, input);
        if(bl[0] == 0xff && bl[1] == 0xd8 && bl[2] == 0xff && (bl[3] & 0xf0) == 0xe0)
        {
            sprintf( filename, "%03i.jpg", i);
            i++;
            FILE* output = fopen( filename, "w");
            while(1){
                fwrite( bl, 1, 512, output);
                
                int a = fread( bl, 1, 512, input);
                 
                 if(bl[0] == 0xff && bl[1] == 0xd8 && bl[2] == 0xff && (bl[3] & 0xf0) == 0xe0)
                 {
                     fclose(output);
                     fseek(input,-1*512,SEEK_CUR);
                     break;
                 }
                if(a < 512){
                    fclose(output);
                    fclose(input);
                    return 0;
                }
            }
            
        }
    }
}
    