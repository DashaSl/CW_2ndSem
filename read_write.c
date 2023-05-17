#include "CWlib.h"
#include "func.h"
#include <ctype.h>
#include <string.h>
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

int not_num_check(char* s){ //check if it's a non-zero positive integer
    if(!strlen(s)) return 0;
    if(s[0] == '0' && (strlen(s) > 1)) return 0;
    int i = 0;
    while(s[i] != '\0'){
        if(!isdigit(s[i])){
            return 1;
        }
        i++;
    }
    return 0;
};

void printhelp(){
    //printf("Well, help yourself...\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}
int check_cord(int x1, int y1, int x2, int y2){
    int ans = (x1 <= x2) && (y1 >= y2);
    return ans;
}

void printinf(char* s){
    BMP bmp = get_img(s);
    printf("version - %d\n", bmp.version);
    printf("\n");
    printf("Header info:\n%x - signature\n%u - filesize\n%hu - reserved1\n%hu - reserved2\n%u - pixel offset\n", bmp.head.Type, bmp.head.Size, bmp.head.Reserved1, bmp.head.Reserved2, bmp.head.OffBits);
    printf("\n");
    printf("Header file info:\n%u - height\n%u - width\n%u - header size\n%u - bits per pix\n%u - planes\n%x - compression\n", bmp.inf.Height, bmp.inf.Width, bmp.inf.Size, bmp.inf.BitCount, bmp.inf.Planes, bmp.inf.Compression);
    printf("%hu - image size\n%u - XPelsPerMeter\n%u - YPelsPerMeter\n%u - ClrUsed\n%hu - ClrImportant\n", bmp.inf.SizeImage, bmp.inf.XPelsPerMeter, bmp.inf.YPelsPerMeter, bmp.inf.ClrUsed, bmp.inf.ClrImportant);
    free_BMP(bmp);
}