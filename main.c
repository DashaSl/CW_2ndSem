#include "CWlib.h"

BMP get_img(char* file_name){
    FILE* fp = fopen(file_name, "rb"); //r - read, b - binary

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


    int height = headinf.Height;
    int width = headinf.Width;

    int padding = (width*sizeof(RGB))%4; // padding to be added
    BYTE trash[4]; //put your extra padding here

    RGB** arr = malloc(sizeof(RGB*)*height);

    for(int i = 0; i < height; i++){
        arr[i] = malloc(sizeof(RGB) * width);
        fread(arr[i], sizeof(RGB), width, fp);
        fread(trash, 1, padding, fp);
    }
    ans.arr = arr;
    fclose(fp);

    ans.padding_bytes = padding;
    
    return ans;
}

void put_img(char* file_name, BMP bmp){
    FILE* fp = fopen(file_name, "wb");
    fwrite(&(bmp.head), 1, sizeof(HEADERFILE), fp);
    fwrite(&(bmp.inf), 1, bmp.inf.Size, fp);
    int height = bmp.inf.Height;
    int width = bmp.inf.Width;
    BYTE* padding = calloc(bmp.padding_bytes, sizeof(BYTE));
    for(int i = 0; i < height; i++){
        fwrite((bmp.arr)[i], sizeof(RGB), width, fp);
        fwrite(padding, sizeof(BYTE), bmp.padding_bytes, fp);
    }
    fclose(fp);
}

void change_clr(RGB* source, RGB clr){
    source->r = clr.r;
    source->g = clr.g;
    source->b = clr.b;
}

int main(){
    BMP bmp = get_img("version5_sample.bmp");
    put_img("new2.bmp", bmp);
    printf( "%d\n", bmp.version);
    return 0;
}
