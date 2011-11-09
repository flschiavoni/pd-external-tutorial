// PD external API
#include "m_pd.h"

static t_class *example7_class;

typedef struct _example7 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
    t_outlet *my_outlet; // Defines a outlet
} t_example7;

// The BANG method, first inlet

void example7_bang(t_example7 *x) { // The method will always receive the class as argument
    post("BANGED!");
    post("My_float value: %f",x->my_float);
    outlet_bang(x->my_outlet); // Bang my outlet
}

void example7_anything(t_example7 *x, t_symbol *s, int argc, t_atom *argv){

	post("ANYTHING!");
}

// Constructos of the class
void * example7_new(t_symbol * arg1, t_floatarg arg2) {
    t_example7 *x = (t_example7 *) pd_new(example7_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);

    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable

    x->my_outlet = outlet_new(&x->x_obj, gensym("bang"));

    return (void *) x;
}

// Destroy the class
void example7_destroy(t_example7 *x) {
   post("You say good bye and I say hello");
}

void example7_setup(void) {
    example7_class = class_new(gensym("example7"),
            (t_newmethod) example7_new, // Constructor
            (t_method) example7_destroy, // Destructor
            sizeof (t_example7),
	    CLASS_DEFAULT,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0); // LAST argument is ALWAYS zero
    class_addbang(example7_class, example7_bang); // ADDs an ACTIVE inlet to receive bangs. This method must be linked to a local function.
    class_addanything(example7_class, example7_anything);

}

