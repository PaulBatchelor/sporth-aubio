#include <soundpipe.h>
#include <sporth.h>

static int sporth_aubio_onset(plumber_data *pd, sporth_stack *stack, void **ud)
{
    return PLUMBER_OK;
}

plumber_dyn_func sporth_return_ugen()
{
    return sporth_aubio_onset;
}
