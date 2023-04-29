#include <config.h>
#include <page_manager.h>



static T_PageAction g_tBrowseAction = {
    .name           = "browse",
    .Run            = BrowseRun,
    .GetInputEvent  = BrowseGetInputEvent,
    .Prepare        = BrowsePrepare,
};




static void BrowseRun(void)
{
  /*1. Display the page */

  /*2. create prepare thread*/

  /*  3.call GetInputEvent function to get the events, and handle these*/
  while(1)
  {
    InputEvent = BrowseGetInputEvent();
    switch (InputEvent)
    {
      case "返回":
      {
        return 0;
      }
      case "缩小":
      {
        /* display reduced page*/
        break;
      }
      case "放大":
      {
        /* display enlarged page*/
        break;
      }
      case "上幅":
      {
        /*display  previous picture*/
      }
      case "下幅":
      {
        /*display next picture*/
      }
      case "连播":
      {
        Page("suto")->Run();
        break;
      }
      case "按住不放":
      {
        /*display moving picture*/
        break;
      }
    }
  }
}

int BrowseInit(void)
{
  return RegisterPageAction(&g_tBrowseAction);
}
