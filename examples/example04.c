// PD external API
#include "m_pd.h"

static t_class *example04_class;

typedef struct _example04 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
} t_example04;


// Constructor of the class
void * example04_new(t_symbol * arg1, t_floatarg arg2) {
    t_example04 *x = (t_example04 *) pd_new(example04_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);

    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable

    return (void *) x;
}

void example04_setup(void) {
    example04_class = class_new(gensym("example04"),
            (t_newmethod) example04_new, // Constructor
            0,
            sizeof (t_example04),
	    CLASS_NOINLET,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0); // LAST argument is ALWAYS zero
}

