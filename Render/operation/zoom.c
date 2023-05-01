/*this file can scale(zoom) the picture
 * it means we can let the picture larger or smaller*/

#include <stdlib.h>
#include <string.h>
#include <pic_operation.h>
#include <config.h>

int PicZoom(PT_PixelDatas ptOriginPic, PT_PixelDatas ptZoomPic)
{
  unsigned long dwDstWidth = ptZoomPic->iWidth;
  unsigned long* pdwSrcXTable;
  unsigned long x;
  unsigned long y;
  unsigned long dwSrcY;
  unsigned char *pucDest;
  unsigned char *pucSrc;
  unsigned long dwPixelBytes = ptOriginPic->iBpp/8;

  if (ptOriginPic->iBpp != ptZoomPic->iBpp)
  {
    return -1;
  }

  pdwSrcXTable = malloc(sizeof(unsigned long) * dwDstWidth);
  if (NULL == pdwSrcXTable)
  {
    DBG_PRINTF("malloc error!\n");
    return -1;
  }

  for (x = 0; x < dwDstWidth; x++)//generate pdwSrcXTable
  {
    pdwSrcXTable[x]=(x*ptOriginPic->iWidth/ptZoomPic->iWidth);
  }

  for (y = 0; y < ptZoomPic->iHeight; y++)
  {
    dwSrcY = (y * ptOriginPic->iHeight / ptZoomPic->iHeight);

    pucDest = ptZoomPic->aucPixelDatas + y*ptZoomPic->iLineBytes;
    pucSrc  = ptOriginPic->aucPixelDatas + dwSrcY*ptOriginPic->iLineBytes;

    for (x = 0; x <dwDstWidth; x++)
    {
      /* original coordinate: pdwSrcXTable[x]，dwSrcY
       * zoomed coordinate: x, y
       */
      memcpy(pucDest+x*dwPixelBytes, pucSrc+pdwSrcXTable[x]*dwPixelBytes, dwPixelBytes);
    }
  }

  free(pdwSrcXTable);
  return 0;
}

