#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    /*Init*/

    page("main")->Run();     //use page() func to use the run() func which was registered in main_page.c


    return 0;
}
