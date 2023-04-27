
#include "../include/encoding_manager.h"


static int isUtf8Coding(unsigned char *pucBufHead);
static  int Utf8GetCodeFrmBuf (unsigned char *pucBufStart, unsigned char *pucBufEnd, unsigned int *pdwCode);

static T_EncodingOpr g_tUtf8EncodingOpr = {
    .name = "utf-8",
    .iHeadLen = 3,
    .isSupport = isUtf8Coding,
    .GetCodeFrmBuf = Utf8GetCodeFrmBuf;
};




static int isUtf8Coding(unsigned char *pucBufHead)
{
  return 0;
}



static  int Utf8GetCodeFrmBuf (unsigned char *pucBufStart, unsigned char *pucBufEnd, unsigned int *pdwCode)
{
  return 0;
}


int Utf8EncodingInit(void)
{
  AddFontOprForEncoding(&g_tUtf8EncodingOpr,GetFontOpr("freetype"));
  AddFontOprForEncoding(&g_tUtf8EncodingOpr,GetFontOpr("ascii"));
  return RegisterEncodingOpr(&g_tUtf8EncodingOpr);
}