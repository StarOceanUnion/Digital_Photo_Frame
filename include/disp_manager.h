#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H

typedef struct DispOpr{
    char *name;
    int iXres;
    int iYres;
    int iBpp;
    int iLineWidth;               //the number of bytes that take up one line of data
    unsigned char *pucDisoMem;    //frambuffer's address
    int (*DeviceInit) (void);
    int (*ShowPixel) (int iPenX, int iPenY, unsigned int dwColor);
    int (*CleanScreen) (unsigned int dwBackColor);
    struct DispOpr *ptNext;         //it is a link list
}T_DispOpr, *PT_DispOpr;

#endif //_DISP_MANAGER_H
