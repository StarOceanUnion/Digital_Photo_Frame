#ifndef _FONTS_MANAGER_H
#define _FONTS_MANAGER_H


typedef struct FontBitMap{
    int iXLeft;            //the top left corner of X point
    int iYTop;             //the top left corner of Y point
    int iXMax;             //bitmap's max of X axis
    int iYMax;             //bitmap's max of Y axis
    int iBpp;              //use 1bit,1bytes or 2bytes for bitmap's unit
    int iPitch;            //the offset betweeen two different rows (byte unit)

    /*
     * int iWidth;          //the standards of a bitmap, like 8x16  16x16.
     * int iRows;           //But FreeType bitmap's rows and width are convertible
     */

    int iCurOriginX;       //it means the current origin X axis(current means "current word" or "current font")
    int iCurOriginY;       //it means the current origin Y axis
    int iNextOriginX;      //it means the next origin X axis(next means "next word" or "next font")
    int iNextOriginY;      //it means the next origin Y axis
    unsigned char *pucBuffer;
}T_FontBitMap,* PT_FontBitMap;

typedef struct FontOpr{
    char *name;
    int (*FontInit)(char *pcFontFile, unsigned int dwFontSize);    //set a function to init the font's information
    int (*GetFontBitmap)(unsigned int dwCode, PT_FontBitMap ptFontBitMap);
    struct FontOpr *ptNext;
}T_FontOpr, *PT_FontOpr;




#endif //_FONTS_MANAGER_H
