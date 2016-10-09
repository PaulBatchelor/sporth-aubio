#include <stdlib.h>
#include <soundpipe.h>
#include <sporth.h>
#include <aubio/aubio.h>

#define HOPSIZE 256

typedef struct {
    fvec_t *in;
    aubio_onset_t *on;
    int count;
    smpl_t is_onset;
    fvec_t *onset;
} sporth_aubio_d;

static void init_data(sporth_aubio_d *sad)
{
    sad->in = new_fvec(HOPSIZE); 
    sad->onset = new_fvec(1); 
    sad->count = 0;
    sad->on = new_aubio_onset("default", HOPSIZE, HOPSIZE, 44100);
}

static void free_data(sporth_aubio_d *sad)
{
    del_fvec(sad->in);
    del_fvec(sad->onset);
    del_aubio_onset(sad->on);
}

static void do_stuff(sporth_aubio_d *sad)
{
    aubio_onset_do(sad->on, sad->in, sad->onset);
    sad->is_onset = fvec_get_sample(sad->onset, 0);
    if(sad->is_onset) {
        fprintf(stderr, "onset!\n");
    }
}

static int sporth_aubio_onset(plumber_data *pd, sporth_stack *stack, void **ud)
{
    sporth_aubio_d *sad;
    switch(pd->mode) {
        case PLUMBER_CREATE:
            if(sporth_check_args(stack, "f") != PLUMBER_OK) {
                return PLUMBER_NOTOK;
            }
            sad = malloc(sizeof(sporth_aubio_d));
            init_data(sad);
            *ud = sad;
            sporth_stack_pop_float(stack);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_INIT:
            sporth_stack_pop_float(stack);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_COMPUTE:
            sad = *ud;
            if(sad->count == 0) {
                do_stuff(sad);
            }
            sad->in->data[sad->count] = sporth_stack_pop_float(stack);
            sporth_stack_push_float(stack, 0);
            sad->count = (sad->count + 1) % HOPSIZE;
            break;
        case PLUMBER_DESTROY:
            sad = *ud;
            free_data(sad);
            free(sad);
            break;
    }
    return PLUMBER_OK;
}

plumber_dyn_func sporth_return_ugen()
{
    return sporth_aubio_onset;
}
