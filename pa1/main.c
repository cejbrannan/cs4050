#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Data{
    int index;
    double distance;
}Data;


int calculate(int inp[], int curr[], int row, Data* datas){
    int sum = 0;
    for(int i = 0; i < 12; i++){
        //printf("%d: %d %d", i, inp[i], curr[i]);
        int diff = inp[i] - curr[i];
        int sqr = diff * diff;
        sum += sqr;
        //printf("%d\n", sum);
    }
    
    double total = sqrt(sum);
    //printf("%d %f", row, total);
    datas[row-1].distance = total;
    datas[row-1].index = row;
    return 0;
}


int compare(const void * x, const void * y){
    Data *a = (Data *)x;
    Data *b = (Data *)y;
    if(a->distance > b->distance){
        return 1;
    }else if(a->distance < b->distance){
        return -1;
    }else{
        return 0;
    }

}

int main(int argc, char **argv)
{
    //clock_t start = clock();
    //printf(clock());
    //double cpu_time_used;
    //start = clock();
    clock_t t;
    t = clock();
    //struct timeval stop, start;
    //gettimeofday(&start, NULL);

    if(argc < 1){
        printf("Error no arguments");
        exit(-1);
    }
    int size;
    char fname[8];
    strcpy(fname, argv[1]);
    size = atoi(fname) * 1000;
    //printf("%d", size);
    Data* datas = malloc(sizeof(Data) * size);
    int inp[12];
    for(int i = 0; i < 12; i++){
        inp[i] = atoi(argv[i+2]);
    }
   
    FILE* fp = fopen(fname, "r");
    if(!fp){
        printf("Can't open\n");
        return 0;
    }else{
        char buffer[1024];
        int row = 0;
        int column = 0;
        while(fgets(buffer, 1024, fp)){
            column = 0;
            int arr[12];

            char* value = strtok(buffer, ",");
            while(value){
                if(column == 0){
                    //printf("a: ");
                    for(int i = 0; i < 12; i++){
                        arr[i] = 0;
                    }
                }
                //printf("%s ", value);
                arr[column] = atoi(value);
                value = strtok(NULL, ",");
                column++;
            }
            row++;
            calculate(inp, arr, row, datas);
            //printf("\n");
        }
        fclose(fp);
    }
   
    qsort(datas, size, sizeof(Data), compare);
    for(int i = 0; i < 25; i++){
        printf("%d %f\n", datas[i].index, datas[i].distance);

    }
    free(datas);
    t = clock() - t;
    double totaltime = (((double)t)/CLOCKS_PER_SEC);
    //printf("%d", totaltime);
    //gettimeofday(&stop, NULL);
    printf("took %f us\n", totaltime); 
    return 0;
}
