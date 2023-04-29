#include <disp_manager.h>
#include <linux/fb.h>
#include <string.h>
#include <config.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>

static int FBDeviceInit (void);
static int FBShowPixel (int iPenX, int iPenY, unsigned int dwColor);
static int FBCleanScreen (unsigned int dwBackColor);
static int g_iFBFd;
static struct fb_var_screeninfo g_tVar;   //current var
static struct fb_fix_screeninfo g_tFix;   //current fix
static int g_iScreenSize;
static unsigned char* g_pucFbMem;
static int g_iLineWidth;
static int g_iPixelWidth;


/*make set and register a struct*/

static T_DispOpr g_tFBDispOpr = {
        .name           = "fb",
        .DeviceInit     = FBDeviceInit,
        .ShowPixel      = FBShowPixel,
        .CleanScreen    = FBCleanScreen,
};


static int FBDeviceInit (void)
{
    int ret;

    g_iFBFd = open(FB_DEVICE_NAME, O_RDWR);
    if (g_iFBFd < 0)
    {
        DBG_PRINTF("can't open %s\n", FB_DEVICE_NAME);
    }

    ret = ioctl(g_iFBFd, FBIOGET_VSCREENINFO, &g_tVar);
    if (ret < 0)
    {
        DBG_PRINTF("can't get fb's var\n");
        return -1;
    }

    ret = ioctl(g_iFBFd, FBIOGET_FSCREENINFO, &g_tFix);
    if (ret < 0)
    {
        DBG_PRINTF("can't get fb's fix\n");
        return -1;
    }

    //screensize
    g_iScreenSize   = g_tVar.xres * g_tVar.yres * g_tVar.bits_per_pixel / 8;
    //use mmap to transport data
    g_pucFbMem = (unsigned char *)mmap(NULL, g_iScreenSize, PROT_READ | PROT_WRITE, MAP_SHARED, g_iFBFd, 0);
    if(g_pucFbMem < 0)
    {
        DBG_PRINTF("can't mmap\n");
        return -1;
    }
    g_tFBDispOpr.iXres  = g_tVar.xres;
    g_tFBDispOpr.iYres  = g_tVar.yres;
    g_tFBDispOpr.iBpp   = g_tVar.bits_per_pixel;
    g_iLineWidth        = g_tVar.xres * g_tVar.bits_per_pixel / 8;
    g_iPixelWidth       = g_tVar.bits_per_pixel / 8;

    return 0;
}

/* dwColor = 0xRRGGBB */
static int FBShowPixel (int iPenX, int iPenY, unsigned int dwColor)
{
    unsigned char *pucPen8 = g_pucFbMem + iPenY * g_iLineWidth + iPenX * g_iPixelWidth;
    unsigned short *pwPen16;
    unsigned int *pdwPen32;
    int red;
    int green;
    int blue;

    pwPen16     = (unsigned short *)pucPen8;
    pdwPen32    = (unsigned int *)pucPen8;

    switch (g_tFBDispOpr.iBpp)
    {
        case 8:
        {
            *pucPen8 = dwColor;
            break;
        }
        case 16:
        {
            red         = (dwColor >> (16+3)) & 0x1f;    //(dwColor >> 16) & 0xff
            green       = (dwColor >> (8+2)) & 0x3f;
            blue        = (dwColor >> 3) & 0x1f;
            *pwPen16    = dwColor;
            break;
        }
        case 32:
        {
            *pdwPen32 = dwColor;
            break;
        }
        default:
        {
            DBG_PRINTF("can't support %dbpp\n", g_tVar.bits_per_pixel);
            return -1;
            break;
        }
    }
    return 0;
}
static int FBCleanScreen (unsigned int dwBackColor)
{
    int red;
    int green;
    int blue;


    unsigned char *pucPen8 = g_pucFbMem;    //the first address of frambuffer
    unsigned short *pwPen16;
    unsigned int *pdwPen32;
    pwPen16     = (unsigned short *)pucPen8;
    pdwPen32    = (unsigned int *)pucPen8;

    int i;
    switch (g_tFBDispOpr.iBpp)
    {
        case 8:
        {
            memset(pucPen8, dwBackColor, g_iScreenSize);
            break;
        }
        case 16:
        {
            red         = (dwBackColor >> (16+3)) & 0x1f;    //(dwColor >> 16) & 0xff
            green       = (dwBackColor >> (8+2)) & 0x3f;
            blue        = (dwBackColor >> 3) & 0x1f;

            for(i = 0; i < g_iScreenSize; i++)
            {
                *pwPen16    = dwBackColor;
                pwPen16++;
                i += 4;                   //short type ,it adds 2 bytes writing once
            }

            break;
        }
        case 32:
        {
            for(i = 0; i < g_iScreenSize; i++)
            {
                *pdwPen32 = dwBackColor;
                pdwPen32++;
                i += 2;                   //short type ,it adds 2 bytes writing once
            }
            break;
        }
        default:
        {
            DBG_PRINTF("can't support %dbpp\n", g_tVar.bits_per_pixel);
            return -1;
            break;
        }
    }
    return 0;
}


int FBInit(void)
{
       return  RegisterDispOpr(&g_tFBDispOpr);   //register the fb's struct
}