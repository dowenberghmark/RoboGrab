#include "brick.h"
int main()
{
brick_init();
tacho_stop(OUTB|OUTC);
brick_uninit();
return 0;
}
