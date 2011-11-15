// PD external API
#include "m_pd.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static t_class *example20_class;

typedef struct _example20 {
    t_object x_obj;
    pthread_t example20_thread;
} t_example20;


// Constructos of the class
void * example20_new(t_symbol *s, t_floatarg inlet_counter, t_floatarg outlet_counter) {
    t_example20 *x = (t_example20 *) pd_new(example20_class);
    return (void *) x;
}

// Destroy the class
void example20_destroy(t_example20 *x) {
   post("You say good bye and I say hello");
}

void * example20_thread_function(void * arg) {
    t_example20 *x = (t_example20 *) arg;
    while(1){
            //DO SOMETHING
	    printf("Threading running!\n");
	    sleep(1);
	}
    return 0;
}

static t_int * example20_perform(t_int *w){
   t_example20 *x = (t_example20 *)(w[1]);
   return (w + 2);
}

static void example20_dsp(t_example20 *x, t_signal **sp){
  pthread_create(&x->example20_thread, NULL, example20_thread_function, x);
  dsp_add(example20_perform, 1 , x);
}


void example20_setup(void) {
    example20_class = class_new(gensym("example20"),
            (t_newmethod) example20_new, // Constructor
            (t_method) example20_destroy, // Destructor
            sizeof (t_example20),
	    CLASS_NOINLET,
            0); // LAST argument is ALWAYS zero
    class_addmethod(example20_class, (t_method) example20_dsp, gensym("dsp"), 0);
}

