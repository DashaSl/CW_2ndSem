#include "CWlib.h"
#include "func.h"

void free_BMP(BMP bmp){
    for(int i = 0; i < abs(bmp.inf.Height); i++){
        free((bmp.arr)[i]);
    }
    free(bmp.arr);
}

BMP get_img(char* file_name){
    FILE* fp = fopen(file_name, "rb"); //r - read, b - binary
    if(fp == NULL){
        printf("couldn't open %s file in get_img. Does it actually exist?\n", file_name);
        exit(1);
    }
    HEADERFILE header;
    HEADERINFO headinf;
    BMP ans;

    fread(&header, 1, sizeof(HEADERFILE), fp);
    DWORD headSize; //to find out which version

    fread(&headSize, 1, sizeof(DWORD), fp);
    headinf.Size = headSize;
    fread(&(headinf.Width), 1, headinf.Size - sizeof(DWORD), fp);

    ans.head = header;
    ans.inf = headinf;

    ans.version = 0;

    if(headSize == 40){
        ans.version = 3;
    }else if(headSize == 108){
        ans.version = 4;
    }else if(headSize == 124){
        ans.version = 5;
    }


    int height = abs(headinf.Height);
    int width = headinf.Width;

    int padding = (width*sizeof(RGB))%4; // padding to be added
    BYTE trash[4]; //put your extra padding here

    RGB** arr = malloc(sizeof(RGB*)*height);
    if(arr == NULL){
        printf("couldn't do malloc in function get_img.\n");
        exit(1);
    }

    for(int i = 0; i < height; i++){
        arr[i] = malloc(sizeof(RGB) * width);
        if(arr[i] == NULL){
            printf("couldn't do malloc in function get_img.\n");
            exit(1);
        }
        fread(arr[i], sizeof(RGB), width, fp);
        fread(trash, 1, padding, fp);
    }
    ans.arr = arr;
    fclose(fp);

    ans.padding_bytes = padding;

    return ans;
}

void put_img(char* file_name, BMP bmp) {
    FILE *fp = fopen(file_name, "wb");
    if(fp == NULL){
        printf("couldn't open %s file in put_img.\n", file_name);
        exit(1);
    }
    fwrite(&(bmp.head), 1, sizeof(HEADERFILE), fp);
    fwrite(&(bmp.inf), 1, bmp.inf.Size, fp);
    int height = abs(bmp.inf.Height);
    int width = bmp.inf.Width;
    BYTE *padding = calloc(bmp.padding_bytes, sizeof(BYTE));
    if(padding == NULL){
        printf("couldn't do calloc in function put_img.\n");
        exit(1);
    }
    for (int i = 0; i < height; i++) {
        fwrite((bmp.arr)[i], sizeof(RGB), width, fp);
        fwrite(padding, sizeof(BYTE), bmp.padding_bytes, fp);
    }
    fclose(fp);

}
