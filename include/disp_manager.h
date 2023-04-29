#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H

typedef struct DispOpr{
    char *name;                     //the name of device
    int iXres;                      //it means the horizontal resolution of the LCD
    int iYres;                      //it means the vertical resolution of the LCD
    int iBpp;                       //the bits per pixel,it sometimes sets 8bits,16bits or 32bits
    int iLineWidth;                 //the number of bytes that take up one line of data
    unsigned char *pucDisoMem;      //frambuffer's address
    int (*DeviceInit) (void);
    int (*ShowPixel) (int iPenX, int iPenY, unsigned int dwColor);
    int (*CleanScreen) (unsigned int dwBackColor);
    struct DispOpr *ptNext;         //it is a link list
}T_DispOpr, *PT_DispOpr;

int RegisterDispOpr(PT_DispOpr ptDispOpr);
void ShowDispOpr(void);
int DisplayInit(void);
int FBInit(void);

#endif //_DISP_MANAGER_H
