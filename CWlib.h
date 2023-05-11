#ifndef basic
#define basic
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef CW_2NDSEM

#define CW_2NDSEM
typedef uint8_t BYTE; //unsigned char
typedef uint16_t WORD; //unsigned short
typedef uint32_t DWORD; //unsigned int
typedef short SHORT; /*Yeah, height and width can be negative. Usually bmp image data starts with bottom-left corner(and in this case H & W are positive),
 but if it starts with upper-left, then height (and width?) will be negative.*/

//this need to stop
#pragma pack(push, 1)

typedef uint32_t FXPT2DOT30;
typedef struct{
    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;
} CIEXYZ;
typedef struct{
    CIEXYZ ciexyzRed;
    CIEXYZ ciexyzGreen;
    CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;
//idk why microsoft made this so long. I'm not wise and knowledgeable enough to understand this.

typedef struct tagBITMAPFILEHEADER {
    WORD  Type;
    DWORD Size;
    WORD  Reserved1;
    WORD  Reserved2;
    DWORD OffBits;
}HEADERFILE;
typedef struct {
    DWORD        Size;
    DWORD        Width;
    DWORD        Height;
    WORD         Planes;
    WORD         BitCount;
    DWORD        Compression;
    DWORD        SizeImage;
    DWORD        XPelsPerMeter;
    DWORD        YPelsPerMeter;
    DWORD        ClrUsed;
    DWORD        ClrImportant;
    //v.3 ends here (and attributes we gonna use too)
    DWORD        bV5RedMask;
    DWORD        bV5GreenMask;
    DWORD        bV5BlueMask;
    DWORD        bV5AlphaMask;
    DWORD        bV5CSType;
    CIEXYZTRIPLE bV5Endpoints;
    DWORD        bV5GammaRed;
    DWORD        bV5GammaGreen;
    DWORD        bV5GammaBlue;
    //v.4 ends here
    DWORD        bV5Intent;
    DWORD        bV5ProfileData;
    DWORD        bV5ProfileSize;
    DWORD        bV5Reserved;
    //v.5 ends here
}HEADERINFO;

typedef struct{
    BYTE r;
    BYTE g;
    BYTE b;
}RGB;

typedef struct{
    HEADERFILE head;
    HEADERINFO inf;
    int version; //bmp version 0, 3, 4, 5
    RGB** arr;
    int padding_bytes; //padding bytes to be added to the end of the row
}BMP;
#pragma pack(pop)
#endif
