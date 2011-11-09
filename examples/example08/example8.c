// PD external API
#include "m_pd.h"

static t_class *example8_class;

typedef struct _example8 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
    t_outlet *my_outlet; // Defines a outlet
} t_example8;


// Constructos of the class
void * example8_new(void) {
    t_example8 *x = (t_example8 *) pd_new(example8_class);

    // creating inlets to the messages "alfa" and "beta"
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("alfa"));
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("beta"));

    x->my_outlet = outlet_new(&x->x_obj, gensym("bang"));

    return (void *) x;
}

// Destroy the class
void example8_destroy(t_example8 *x) {
   post("You say good bye and I say hello");
}



void example8_start(t_example8 *x){
    post("START / BANG");
}

void example8_stop(t_example8 *x){
    post("STOP");
}

void example8_open(t_example8 *x, t_symbol *s){
    post("open %s",s->s_name);
}


void example8_alfa(t_example8 *x, t_floatarg f){
	post("ALFA VALUE %f",f);
}

void example8_beta(t_example8 *x, t_floatarg f){
	post("BETA VALUE %f",f);
}

void example8_setup(void) {
    example8_class = class_new(gensym("example8"),
            (t_newmethod) example8_new, // Constructor
            (t_method) example8_destroy, // Destructor
            sizeof (t_example8),
	    CLASS_DEFAULT,
            0); // LAST argument is ALWAYS zero

    // All these messages will be received by the first left inlet
    class_addmethod(example8_class, (t_method) example8_start, gensym("start"), 0); // two messages, the same function
    class_addmethod(example8_class, (t_method) example8_start, gensym("bang"),  0); // may be "start" or "bang" messages
    class_addmethod(example8_class, (t_method) example8_stop,  gensym("stop"),  0);
    class_addmethod(example8_class, (t_method) example8_open,  gensym("open"),  A_DEFSYMBOL,0);

    // These messages will be associated with inlets 2 and 3
    class_addmethod(example8_class, (t_method) example8_alfa,  gensym("alfa"), A_DEFFLOAT,0); 
    class_addmethod(example8_class, (t_method) example8_beta,  gensym("beta"), A_DEFFLOAT,0); 

}

