#include "CWlib.h"
void free_BMP(BMP bmp){
    for(int i = 0; i < abs(bmp.inf.Height); i++){
        free((bmp.arr)[i]);
    }
    free(bmp.arr);
}


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


    int height = abs(headinf.Height);
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

void put_img(char* file_name, BMP bmp) {
    FILE *fp = fopen(file_name, "wb");
    if (fp == NULL) {
        fprintf(stderr, "couldn't open file");
        exit(1);
    }
    fwrite(&(bmp.head), 1, sizeof(HEADERFILE), fp);
    fwrite(&(bmp.inf), 1, bmp.inf.Size, fp);
    int height = abs(bmp.inf.Height);
    int width = bmp.inf.Width;
    BYTE *padding = calloc(bmp.padding_bytes, sizeof(BYTE));

    for (int i = 0; i < height; i++) {
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

void copy_paste(char* source, char* paste_here, int xs1, int ys1, int xs2, int ys2, int xp, int yp){
    BMP sour = get_img(source);
    BMP paste = get_img(paste_here);
    int width = xs2 - xs1;
    int height = ys1 - ys2;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            change_clr((paste.arr)[yp - i]+xp+j, (sour.arr)[ys1-i][xs1+j]);
        }
    }
    put_img(paste_here, paste);
    free_BMP(sour);
    free_BMP(paste);
};

int cmp_rgb(RGB rgb1, RGB rgb2){
    if(rgb1.r == rgb2.r && rgb1.g == rgb2.g && rgb1.b == rgb2.b){
        return 1;
    }
    return 0;
}

void change_color(char* file_name, RGB to_be_changed, RGB base){
    BMP bmp = get_img(file_name);
    for(int i = 0; i < abs(bmp.inf.Height); i++){
        for(int j = 0; j < abs(bmp.inf.Width); j++){
            if(cmp_rgb((bmp.arr)[i][j], to_be_changed)){
                change_clr((bmp.arr)[i]+j, base);
            }
        }
    }
    put_img(file_name, bmp);
    free_BMP(bmp);
}


int main(){
    copy_paste("ver3.bmp", "ver5.bmp", 100, 100, 150, 0, 300, 300);
    BMP bmp = get_img("ver3.bmp");
    put_img("ver3new.bmp", bmp);
    RGB rgb = (bmp.arr)[20][20];
    free_BMP(bmp);
    RGB new = {255, 0, 255};
    change_color("ver3.bmp", rgb, new);
    return 0;
}
