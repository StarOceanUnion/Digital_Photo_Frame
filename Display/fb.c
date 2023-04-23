#include "../include/disp_manager.h"
#include <linux/fb.h>
#include <string.h>
#include "../include/config.h"

static int FBDeviceInit (void);
static int FBShowPixel (int iPenX, int iPenY, unsigned int dwColor);
static int FBCleanScreen (unsigned int dwBackColor);
static int g_fb;
static struct fb_var_screeninfo g_tFBVar;   //current var
static struct fb_fix_screeninfo g_tFBFix;   //current fix


/*make set and register a struct*/

static T_DispOpr g_tFBOpr = {
        .name           = "fb",
        .DeviceInit     = FBDeviceInit,
        .ShowPixel      = FBShowPixel,
        .CleanScreen    = FBCleanScreen,
};


static int FBDeviceInit (void)
{
    int ret;

    g_fb = open(FB_DEVICE_NAME, O_RDWR);
    if (g_fb < 0)
    {
        DBG_PRINTF("can't open %s\n", FB_DEVICE_NAME);
    }

    ret = ioctl(g_fb, FBIOGET_VSCREENINFO, &g_tFBVar);
    if (ret < 0)
    {
        DBG_PRINTF("can't get fb's var\n");
        return -1;
    }

    ret = ioctl(g_fb, FBIOGET_FSCREENINFO, &g_tFBFix);
    if (ret < 0)
    {
        DBG_PRINTF("can't get fb's fix\n");
        return -1;
    }

    g_tFBOpr.iXres = ;
    g_tFBOpr.iYres = ;
    g_tFBOpr.iBpp = ;
    g_tFBOpr.iLine


}
static int FBShowPixel (int iPenX, int iPenY, unsigned int dwColor)
{

}
static int FBCleanScreen (unsigned int dwBackColor)
{

}


int FBInit(void)
{
        RegisterDispOpr(&g_tFBOpr);   //register the fb's struct
}