// PD external API
#include "m_pd.h"

static t_class *example5_class;

typedef struct _example5 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
} t_example5;

// The BANG method, first inlet

void example5_bang(t_example5 *x) { // The method will always receive the class as argument
    post("BANGED!");
    post("My_float value: %f",x->my_float);
}

void example5_anything(t_example5 *x, t_symbol *s, int argc, t_atom *argv){

	post("ANYTHING!");
}

// Constructos of the class
void * example5_new(t_symbol * arg1, t_floatarg arg2) {
    t_example5 *x = (t_example5 *) pd_new(example5_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);

    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable

    return (void *) x;
}

void example5_setup(void) {
    example5_class = class_new(gensym("example5"),
            (t_newmethod) example5_new, // Constructor
            0, 
            sizeof (t_example5),
	    CLASS_DEFAULT,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0); // LAST argument is ALWAYS zero
    class_addbang(example5_class, example5_bang); // ADDs an ACTIVE inlet to receive bangs. This method must be linked to a local function.
    class_addanything(example5_class, example5_anything);

}

