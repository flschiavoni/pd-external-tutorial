// PD external API
#include "m_pd.h"

static t_class *example05_class;

typedef struct _example05 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
} t_example05;

// The BANG method, first inlet

void example05_bang(t_example05 *x) { // The method will always receive the class as argument
    post("BANGED!");
    post("My_float value: %f",x->my_float);
}

void example05_anything(t_example05 *x, t_symbol *s, int argc, t_atom *argv){

	post("ANYTHING!");
}

// Constructos of the class
void * example05_new(t_symbol * arg1, t_floatarg arg2) {
    t_example05 *x = (t_example05 *) pd_new(example05_class);
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);

    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable

    return (void *) x;
}

void example05_setup(void) {
    example05_class = class_new(gensym("example05"),
            (t_newmethod) example05_new, // Constructor
            0, 
            sizeof (t_example05),
	    CLASS_DEFAULT,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0); // LAST argument is ALWAYS zero
    class_addbang(example05_class, example05_bang); // ADDs an ACTIVE inlet to receive bangs. This method must be linked to a local function.
    class_addanything(example05_class, example05_anything);

}

