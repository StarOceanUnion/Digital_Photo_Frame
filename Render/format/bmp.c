#include <pic_operation.h>
#include <stdlib.h>
#include <string.h>

static int isBMPFormat(unsigned char *aFileHead);
static int GetPixelDatasFrmBMP(unsigned char *aFileHead,PT_PixelDatas ptPixelDatas);
static int FreePixelDatasForBMP(PT_PixelDatas tPixelDatas);

struct T_PicFileParser g_tBMPParser = {
    .name           = "bmp",
    .isSupport      = isBMPFormat,
    .GetPixelDatas  = GetPixelDatasFrmBMP,
    .FreePixelDatas = FreePixelDatasForBMP,
};

typedef struct tagBITMAPFILEHEADER{     //BMP file header
    unsigned short bfType;
    unsigned long bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;
}BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER{     //BMP bitmap information header
    unsigned long  biSize;
    unsigned long  biWidth;
    unsigned long  biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long  biCompression;
    unsigned long  biSizeImage;
    unsigned long  biXPelsPerMeter;
    unsigned long  biYPelsPerMeter;
    unsigned long  biClrUsed;
    unsigned long  biClrImportant;
}BITMAPINFOHEADER;


static int isBMPFormat(unsigned char *aFileHead)
{
  if(aFileHead[0] != 0x42 || aFileHead[1] != 0x4d)
    return 0;
  else
    return 1;

}



static int GetPixelDatasFrmBMP(unsigned char *aFileHead,PT_PixelDatas ptPixelDatas)
{
  BITMAPFILEHEADER *ptBITMAPFILEHEADER;
  BITMAPINFOHEADER *ptBITMAPINFOHEADER;

  int iWidth;
  int iHeight;
  int iBpp;
  int x,y;

  unsigned char *pucSrc;
  unsigned char *pucDest;
  int iLineWidthAlign;
  int iLineWidthReal;


  ptBITMAPFILEHEADER = (BITMAPFILEHEADER *)aFileHead;
  ptBITMAPINFOHEADER = (BITMAPINFOHEADER*)(aFileHead + sizeof(BITMAPFILEHEADER));

  iWidth  = ptBITMAPINFOHEADER->biWidth;
  iHeight = ptBITMAPINFOHEADER->biHeight;
  iBpp    = ptBITMAPINFOHEADER->biBitCount;


  if(iBpp != 24)
  {
    return -1;
  }

  ptPixelDatas->iWidth        = iWidth;
  ptPixelDatas->iHeight       = iHeight;
  ptPixelDatas->iBpp          = iBpp;
  ptPixelDatas->aucPixelDatas = malloc (iWidth * iHeight * iBpp /8);
  if(ptPixelDatas->aucPixelDatas == NULL)
  {
    return -1;
  }

  iLineWidthReal = iWidth * iBpp / 8;
  iLineWidthAlign = (iLineWidthReal + 3) & ~0x3;      //Round to 4
  pucSrc = aFileHead + ptBITMAPFILEHEADER->bfOffBits;
  pucSrc = pucSrc + (iHeight - 1) * iLineWidthAlign;

  pucDest = ptPixelDatas->aucPixelDatas;
  for(y = 0;y < iHeight; y++)
  {
    memcpy(pucDest, pucSrc, iLineWidthReal);
    pucSrc  -= iLineWidthAlign;
    pucDest += iLineWidthReal;
  }
  return 0;
}



static int FreePixelDatasForBMP(PT_PixelDatas tPixelDatas)
{
  free(tPixelDatas->aucPixelDatas);
  return 0;
}


