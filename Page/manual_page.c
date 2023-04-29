#include <config.h>
#include <page_manager.h>



static T_PageAction g_tManualAction = {
    .name           = "manual",
    .Run            = ManualPageRun,
    .GetInputEvent  = ManualGetInputEvent,
    .Prepare        = ManualPrepare,
};




static void ManualPageRun(void)
{
  /*1. Display the page */

  /*2. create prepare thread*/

  /*  3.call GetInputEvent function to get the events, and handle these*/
  while(1)
  {
    InputEvent = ManualGetInputEvent();
    switch (InputEvent)
    {
      case "向上":
      {
        /*judge this is top or not*/
        if(isTopLevel)
          return 0;
        else
        {
          /*display last one folder's page*/

        }
        break;
      }
      case "选择":
      {
        /*save current page*/
        StorePage();
        Page("auto")->Run();
        /*Restore previous page*/
        RestorePage();
        break;
      }
      case "上页":
      {
        /*display previous page*/;
      }
        break;
      case "下页":
      {
        /*display next page*/
      }
  }
}
}

int ManualInit(void)
{
  return RegisterPageAction(&g_tManualAction);
}
