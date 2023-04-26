//
// Created by A on 2023/4/19.
//

#ifndef _FONTS_MANAGER_H
#define _FONTS_MANAGER_H

typedef struct FontOpr{
    char *name;
    int (*FontInit)(char *pcFont, unsigned int dwFontSize);    //set a function to init the font's information
    int (*GetFontBitmap)(unsigned int dwCode, PT_FontBitMap ptFontBitMap);
    struct FontOpr *ptNext;
}T_FontOpr, *PT_FontOpr;



#endif //_FONTS_MANAGER_H
