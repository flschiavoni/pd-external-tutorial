// PD external API
#include "m_pd.h"

static t_class *example19_class;

typedef struct _example19 {
    t_object x_obj;
    t_sample * outvec[64]; // 64 is a magic number!
    t_int inlet_counter;
} t_example19;


// Constructos of the class
void * example19_new(t_symbol *s, t_floatarg inlet_counter, t_floatarg outlet_counter) {
    t_example19 *x = (t_example19 *) pd_new(example19_class);

    post("inlet counter %f", inlet_counter);

    x->inlet_counter = inlet_counter;

    int i;
    for(i = 0 ; i < inlet_counter ; i++)
	inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);

    return (void *) x;
}

// Destroy the class
void example19_destroy(t_example19 *x) {
   post("You say good bye and I say hello");
}


static t_int * example19_perform(t_int *w){
   t_example19 *x = (t_example19 *)(w[1]);
   // Call DSP function or start DSP thread

  return (w + 2);
}

static void example19_dsp(t_example19 *x, t_signal **sp){
    short i;
    for (i = 0; i < x->inlet_counter; i++)
        x->outvec[i] = sp[i]->s_vec; // Put the inlets data into my structure
  dsp_add(example19_perform, 1 , x);
}


void example19_setup(void) {
    example19_class = class_new(gensym("example19"),
            (t_newmethod) example19_new, // Constructor
            (t_method) example19_destroy, // Destructor
            sizeof (t_example19),
	    CLASS_NOINLET,
	    A_DEFFLOAT, // # of inlets
            0); // LAST argument is ALWAYS zero

    class_addmethod(example19_class, (t_method) example19_dsp, gensym("dsp"), 0);
}

