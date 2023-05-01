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


static int ConvertOneline(int iWidth, int iSrcBpp, int iDstBpp, unsigned char  *pudSrcDatas, unsigned char *pudDstDatas)
{
  unsigned int dwRed;
  unsigned int dwGreen;
  unsigned int dwBlue;
  unsigned int dwColor;

  unsigned short *pwDstDatas16bpp = (unsigned short *)pudDstDatas;
  unsigned int   *pwDstDatas32bpp = (unsigned int *)pudDstDatas;

  int i;
  int pos = 0;

  if (iSrcBpp != 24)
  {
    return -1;
  }

  if (iDstBpp == 24)
  {
    memcpy(pudDstDatas, pudSrcDatas, iWidth * 3);
  }
  else
  {
    for (i = 0; i < iWidth; i++)
    {
      dwBlue  = pudSrcDatas[pos++];
      dwGreen = pudSrcDatas[pos++];
      dwRed   = pudSrcDatas[pos++];
      if (iDstBpp == 32)
      {
        /*888*/
        dwColor = (dwRed << 16) | (dwGreen << 8) | dwBlue;
        *pwDstDatas32bpp = dwColor;
        pwDstDatas32bpp++;
      }
      else if (iDstBpp == 16)
      {
        /* 565 */
        dwRed   = dwRed >> 3;
        dwGreen = dwGreen >> 2;
        dwBlue  = dwBlue >> 3;
        dwColor = (dwRed << 11) | (dwGreen << 5) | (dwBlue);
        *pwDstDatas16bpp = dwColor;
        pwDstDatas16bpp++;
      }
    }
  }
  return 0;
}



/* ptPixelDatas->iBpp is the input parameters
 * it determines that the datas geted from BMP need be switched to this format*/
static int GetPixelDatasFrmBMP(unsigned char *aFileHead,PT_PixelDatas ptPixelDatas)
{
  BITMAPFILEHEADER *ptBITMAPFILEHEADER;
  BITMAPINFOHEADER *ptBITMAPINFOHEADER;

  int iWidth;
  int iHeight;
  int iBMPBpp;
  int x,y;

  unsigned char *pucSrc;
  unsigned char *pucDest;
  int iLineWidthAlign;
  int iLineWidthReal;


  ptBITMAPFILEHEADER = (BITMAPFILEHEADER *)aFileHead;
  ptBITMAPINFOHEADER = (BITMAPINFOHEADER*)(aFileHead + sizeof(BITMAPFILEHEADER));

  iWidth  = ptBITMAPINFOHEADER->biWidth;
  iHeight = ptBITMAPINFOHEADER->biHeight;
  iBMPBpp    = ptBITMAPINFOHEADER->biBitCount;


  if(iBMPBpp != 24)
  {
    return -1;
  }

  ptPixelDatas->iWidth        = iWidth;
  ptPixelDatas->iHeight       = iHeight;
  ptPixelDatas->aucPixelDatas = malloc (iWidth * iHeight * ptPixelDatas->iBpp / 8);
  ptPixelDatas->iLineBytes    = iWidth * ptPixelDatas->iBpp / 8;
  if(ptPixelDatas->aucPixelDatas == NULL)
  {
    return -1;
  }

  iLineWidthReal = iWidth * iBMPBpp / 8;
  iLineWidthAlign = (iLineWidthReal + 3) & ~0x3;      //Round to 4
  pucSrc = aFileHead + ptBITMAPFILEHEADER->bfOffBits;
  pucSrc = pucSrc + (iHeight - 1) * iLineWidthAlign;

  pucDest = ptPixelDatas->aucPixelDatas;
  for(y = 0;y < iHeight; y++)
  {
    //memcpy(pucDest, pucSrc, iLineWidthReal);
    ConvertOneline(iWidth, iBMPBpp, ptPixelDatas->iBpp, pucSrc, pucDest);
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


