#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    if(argc != 3){
        printf(
                "Usage:\n"
                "\t./fread <filename> <amount_of_strings>"
        );
        return -1;
    }
    int N;

    if(!sscanf(argv[2], "%d", &N)){
        printf("Wrong strings amount input\n");
        return -1;
    }
    int ncopy = N;
    int Nstr = 0;
    if(!N) {
        Nstr = 1;
        N = 1;
    }
    FILE* file = fopen(argv[1], "r");
    if(!file){
        printf("Error, can't open the file!\n");
        return -1;
    }


    char buffer[512];
    int buffptr = 0;
    memset(buffer, 0, 512);


    char inp = fgetc(file);


    while(inp != EOF && N){

        buffer[buffptr++] = inp;
        if(inp == '\n'){
            if(!Nstr)N--;
            printf("%s", buffer);
            memset(buffer, 0, 512);
            buffptr = 0;
            if(N == 0){
                printf("Press any key to continue...");
                getchar();
                N = ncopy;
            }
        }
        inp = fgetc(file);
    }
    printf("Program finished!\n");
}