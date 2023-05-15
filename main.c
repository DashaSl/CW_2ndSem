#include "CWlib.h"
#include "read_write.h"
#include "func.h"


int main(){
    RGB clr = {0, 0, 255};
    RGB clr2 = {100, 30, 200};
    int* data = malloc(sizeof(int)*4);
    data[0] = 30;
    data[1] = 70;
    data[2] = 70;
    //draw_hexagon("blank.bmp", data, 1, 1, clr, 0, clr);
    BMP bmp = get_img("blank.bmp");
    fill_v2(bmp, clr2, clr, 70, 70);
    put_img("new.bmp", bmp);
    return 0;
}
