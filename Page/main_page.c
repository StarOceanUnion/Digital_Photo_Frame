#include <config.h>
#include <page_manager.h>



static T_PageAction g_tMainPageAction = {
    .name           = "main",
    .Run            = BrowseRun,
    .GetInputEvent  = MainPageGetInputEvent,
    .Prepare        = MainPagePrepare,
};




static void MainPageRun(void)
{
  /*1. Display the page */

  /*2. create prepare thread*/

  /*  3.call GetInputEvent function to get the events, and handle these*/
  while(1)
  {
    InputEvent = MainPageGetInputEvent();
    switch (InputEvent)
    {
      case "浏览模式":
      {
        /*save current page*/
        StorePage();
        Page ("browse")->Run();
        /*Restore previous page*/
        RestorePage();
        break;
      }
      case "连播模式":
      {
        /*save current page*/
        StorePage();
        Page("auto")->Run();
        /*Restore previous page*/
        RestorePage();
        break;
      }
      case "设置模式":
      {
        /*save current page*/
        StorePage();
        Page("setting")->Run();
        /*Restore previous page*/
        RestorePage();
        break;
      }
    }
  }
}

int MainPageGetInputEvent()
{
  /* get original LCD data
   * it calls input_manager.c's function to let current thread sleep or not
   * when it gets LCD's data, it will wake up this thread
   */
  GetInputEvent();
  /*handle data*/
}

int MainPageInit(void)
{
  return RegisterPageAction(&g_tMainPageAction);
}