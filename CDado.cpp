#include "CDado.h"

CDado::CDado()
{
    srand(time(0));
}


int CDado::GetValorDado()
{
    return  (rand() % 6) + 1;
}
