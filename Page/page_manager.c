#include <config.h>
#include <page_manager.h>
#include <string.h>

static PT_PageAction g_ptDispOprHead;

int RegisterPageAction(PT_PageAction ptPageAction)
{
  PT_PageAction ptTmp;

  if (!g_ptDispOprHead)
    {
      g_ptDispOprHead   = ptPageAction;
      ptPageAction->ptNext = NULL;
    }
  else
    {
      ptTmp = g_ptDispOprHead;
      while (ptTmp->ptNext)
        {
          ptTmp = ptTmp->ptNext;
        }
      ptTmp->ptNext	  = ptPageAction;
      ptPageAction->ptNext = NULL;
    }

  return 0;
}


void ShowPages(void)
{
  int i = 0;
  PT_PageAction ptTmp = g_ptDispOprHead;

  while (ptTmp)
    {
      printf("%02d %s\n", i++, ptTmp->name);
      ptTmp = ptTmp->ptNext;
    }
}

PT_PageAction Page(char *pcName)
{
  PT_PageAction ptTmp = g_ptDispOprHead;

  while (ptTmp)
    {
      if (strcmp(ptTmp->name, pcName) == 0)
        {
          return ptTmp;
        }
      ptTmp = ptTmp->ptNext;
    }
  return NULL;
}

int PagesInit(void)
{
  int iError;


  return iError;
}



