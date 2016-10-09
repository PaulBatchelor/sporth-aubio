#include <soundpipe.h>
#include <sporth.h>
#include <aubio/aubio.h>

static int sporth_aubio_onset(plumber_data *pd, sporth_stack *stack, void **ud)
{
    switch(pd->mode) {
        case PLUMBER_CREATE:
            if(sporth_check_args(stack, "f") != PLUMBER_OK) {
                return PLUMBER_NOTOK;
            }
            sporth_stack_pop_float(stack);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_INIT:
            sporth_stack_pop_float(stack);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_COMPUTE:
            sporth_stack_pop_float(stack);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_DESTROY:
            break;
    }
    return PLUMBER_OK;
}

plumber_dyn_func sporth_return_ugen()
{
    return sporth_aubio_onset;
}
