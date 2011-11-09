// PD external API
#include "m_pd.h"

static t_class *example07_class;

typedef struct _example07 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
    t_outlet *my_outlet; // Defines a outlet
} t_example07;

// The BANG method, first inlet

void example07_bang(t_example07 *x) { // The method will always receive the class as argument
    post("BANGED!");
    post("My_float value: %f",x->my_float);
    outlet_bang(x->my_outlet); // Bang my outlet
}

void example07_anything(t_example07 *x, t_symbol *s, int argc, t_atom *argv){

	post("ANYTHING!");
}

// Constructos of the class
void * example07_new(t_symbol * arg1, t_floatarg arg2) {
    t_example07 *x = (t_example07 *) pd_new(example07_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);

    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable

    x->my_outlet = outlet_new(&x->x_obj, gensym("bang"));

    return (void *) x;
}

// Destroy the class
void example07_destroy(t_example07 *x) {
   post("You say good bye and I say hello");
}

void example07_setup(void) {
    example07_class = class_new(gensym("example07"),
            (t_newmethod) example07_new, // Constructor
            (t_method) example07_destroy, // Destructor
            sizeof (t_example07),
	    CLASS_DEFAULT,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0); // LAST argument is ALWAYS zero
    class_addbang(example07_class, example07_bang); // ADDs an ACTIVE inlet to receive bangs. This method must be linked to a local function.
    class_addanything(example07_class, example07_anything);

}

