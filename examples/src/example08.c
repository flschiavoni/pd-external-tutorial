// PD external API
#include "m_pd.h"

static t_class *example08_class;

typedef struct _example08 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
    t_outlet *my_outlet; // Defines a outlet
} t_example08;


// Constructos of the class
void * example08_new(void) {
    t_example08 *x = (t_example08 *) pd_new(example08_class);

    // creating inlets to the messages "alfa" and "beta"
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("alfa"));
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("beta"));

    x->my_outlet = outlet_new(&x->x_obj, gensym("bang"));

    return (void *) x;
}

// Destroy the class
void example08_destroy(t_example08 *x) {
   post("You say good bye and I say hello");
}



void example08_start(t_example08 *x){
    post("START / BANG");
}

void example08_stop(t_example08 *x){
    post("STOP");
}

void example08_open(t_example08 *x, t_symbol *s){
    post("open %s",s->s_name);
}


void example08_alfa(t_example08 *x, t_floatarg f){
	post("ALFA VALUE %f",f);
}

void example08_beta(t_example08 *x, t_floatarg f){
	post("BETA VALUE %f",f);
}

void example08_setup(void) {
    example08_class = class_new(gensym("example08"),
            (t_newmethod) example08_new, // Constructor
            (t_method) example08_destroy, // Destructor
            sizeof (t_example08),
	    CLASS_DEFAULT,
            0); // LAST argument is ALWAYS zero

    // All these messages will be received by the first left inlet
    class_addmethod(example08_class, (t_method) example08_start, gensym("start"), 0); // two messages, the same function
    class_addmethod(example08_class, (t_method) example08_start, gensym("bang"),  0); // may be "start" or "bang" messages
    class_addmethod(example08_class, (t_method) example08_stop,  gensym("stop"),  0);
    class_addmethod(example08_class, (t_method) example08_open,  gensym("open"),  A_DEFSYMBOL,0);

    // These messages will be associated with inlets 2 and 3
    class_addmethod(example08_class, (t_method) example08_alfa,  gensym("alfa"), A_DEFFLOAT,0); 
    class_addmethod(example08_class, (t_method) example08_beta,  gensym("beta"), A_DEFFLOAT,0); 

}

