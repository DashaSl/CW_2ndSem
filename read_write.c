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
    printf("You have 5 options:\n1)draw Hexagon, 2)copy a part of an image and paste it on another image 3)draw a frame 4)change chosen color on other color 5)show bmp file info\n");
    printf("\n");
    printf("1)to draw hexagon, choose option -H/--hexagon\nchoose mode 1 (--mode/-m 1) if you want to draw it using a point and radius; mode 0 if you want to draw using upper left and lower down coordinates\n");
    printf("if you've chosen mode 1 chose radius (-r/--radius 20) and start point (-s/--start 30 30); if mode 0 chose start point and end point(-e/--end 50 10)\n");
    printf("chose thickness of lines using -w/--width (-w 30)\n");
    printf("chose line color -g/--rgb1 (-g 23 167 80)\n");
    printf("chose to fill(1) or not to fill(0) hexagon (-z/--fill_flag 0)\n");
    printf("select a color, if you've chosen fill_flag 1 (-b/--rgb2 33 33 33)\n");
    printf("chose your file using -f/--file_name (-f name_of_the_file)\n");
    printf("example: ./CW2 --hexagon --start 0 110 --end 110 0 -w 7 --rgb1 20 20 20 --rgb2 200 100 50 -z 1 --file_name Amogus.bmp\n");
    printf("\n");
    printf("2)to copy & paste, chose option -C/--copy\n");
    printf("chose source file (-f/--file_name) and the file, where you going to paste to, (-o/--out_file)\n");
    printf("chose upper left coordinates (-s/--start) and lower right (-e/--end) of the part of source image to be copied\n");
    printf("chose a point on the output file, where the upper left corner of the copied piece will be (-p/--point)\n");
    printf("example: ./CW2 -C --start 10 200 --end 150 40 -p 30 230 --file_name file1.bmp --out_file file2.bmp\n");
    printf("\n");
    printf("3)to draw a frame, chose -F/--frame\n");
    printf("select the type of frame using -m/--mode. 0 - simple frame, 1 - Koch line frame, 2 - Minkowski line frame\n");
    printf("If you selected mode 0 chose width of the frame (-w/--width) and color (-g/--rgb1) only.\n");
    printf("If you selected mode 1 or 2 chose width (-w/--width) of the frame,\n");
    printf("color of lines of the frame (-g/--rgb1)\n");
    printf("chose to fill(1) or not to fill(0) frame\n");
    printf("select a color, if you've chosen fill_flag 1 (-b/--rgb2)\n");
    printf("chose file -f/--file_name\n");
    printf("example: ./CW2 -F --width 50 -z 1 --rgb1 55 55 55 --rgb2 1 1 1 -f file.bmp\n");
    printf("\n");
    printf("4)to change color of all pixels of the chosen color to the other color, choose option -G/--changeclr\n");
    printf("chose your file -f/--file_name\n");
    printf("chose color-to-be-changed -g/--rgb1 and finish color -b/--rgb2\n");
    printf("chose your file -f/--file_name");
    printf("example: ./CW2 -G --rgb1 45 45 45 --rgb2 88 88 88 -f myfile.bmp\n");
    printf("\n");
    printf("5)to see bmp file info chose -i/--info and write your file name\n");
    printf("example: ./CW2 -i myfile.bmp\n");
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