// PD external API
#include "m_pd.h"

static t_class *example6_class;

typedef struct _example6 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
    t_outlet *my_outlet; // Defines a outlet
} t_example6;

// The BANG method, first inlet

void example6_bang(t_example6 *x) { // The method will always receive the class as argument
    post("BANGED!");
    post("My_float value: %f",x->my_float);
    outlet_bang(x->my_outlet); // Bang my outlet
}

void example6_anything(t_example6 *x, t_symbol *s, int argc, t_atom *argv){

	post("ANYTHING!");
}

// Constructos of the class
void * example6_new(t_symbol * arg1, t_floatarg arg2) {
    t_example6 *x = (t_example6 *) pd_new(example6_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);

    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable

    x->my_outlet = outlet_new(&x->x_obj, gensym("bang"));

    return (void *) x;
}

void example6_setup(void) {
    example6_class = class_new(gensym("example6"),
            (t_newmethod) example6_new, // Constructor
            0, 
            sizeof (t_example6),
	    CLASS_DEFAULT,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0); // LAST argument is ALWAYS zero
    class_addbang(example6_class, example6_bang); // ADDs an ACTIVE inlet to receive bangs. This method must be linked to a local function.
    class_addanything(example6_class, example6_anything);

}

