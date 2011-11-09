// PD external API
#include "m_pd.h"

static t_class *example4_class;

typedef struct _example4 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
} t_example4;


// Constructos of the class
void * example4_new(t_symbol * arg1, t_floatarg arg2) {
    t_example4 *x = (t_example4 *) pd_new(example4_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);

    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable

    return (void *) x;
}

void example4_setup(void) {
    example4_class = class_new(gensym("example4"),
            (t_newmethod) example4_new, // Constructor
            0,
            sizeof (t_example4),
	    CLASS_NOINLET,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0); // LAST argument is ALWAYS zero
}

