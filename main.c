#include "CWlib.h"
#include "read_write.h"
#include "func.h"


int main(){
    RGB clr = {0, 0, 0};
    RGB clr2 = {230, 150, 200};
    draw_Koch_frame("ver3.bmp", 50, 1, clr, clr2);
    return 0;
}
