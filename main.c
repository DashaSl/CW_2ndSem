#include "CWlib.h"
#include "read_write.h"
#include "func.h"


int main(){
    RGB clr = {0, 0, 255};
    RGB clr2 = {70, 140, 70};
    draw_simple_frame("ver3.bmp", 15, clr);
    return 0;
}
