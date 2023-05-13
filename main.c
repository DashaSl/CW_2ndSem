#include "CWlib.h"
#include "read_write.h"
#include "func.h"


int main(){

    RGB clr2 = {163, 33, 152};
    RGB clr = {125, 14, 53};
    int* data = malloc(sizeof(int)*4);
    data[0] = 50;
    data[1] = 100;
    data[2] = 100;
    draw_hexagon("ver3.bmp", data, 0, 1, clr2, 1, clr);
    printf("sucsess!\n");
    free(data);
    return 0;
}
