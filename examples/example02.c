// PD external API
#include "m_pd.h"

static t_class *example02_class;

typedef struct _example02 {
    t_object x_obj;
} t_example02;


// Constructor of the class
void * example02_new(t_symbol * arg1, t_floatarg arg2) {
    t_example02 *x = (t_example02 *) pd_new(example02_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);
    return (void *) x;
}

void example02_setup(void) {
    example02_class = class_new(gensym("example02"),
            (t_newmethod) example02_new, // Constructor
            0,
            sizeof (t_example02),
	    CLASS_NOINLET,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0);
}

