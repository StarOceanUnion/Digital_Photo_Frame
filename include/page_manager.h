#ifndef _PAGE_MANAGER_H
#define _PAGE_MANAGER_H

typedef struct PageAction{
    char *name;
    int (*Run)(void);
    int (*GetInputEvent)();
    int (*Prepare)();
    struct PageAction *ptNext;     //it is a link list
}T_PageAction, *PT_PageAction;
#endif    //_PAGE_MANAGER_H
