// PD external API
#include "m_pd.h"

static t_class *myobj1_class;
static t_class *myobj2_class;

typedef struct _myobj1 {
    t_object x_obj;
} t_myobj1;

typedef struct _myobj2 {
    t_object x_obj;
} t_myobj2;


// Constructor of the class
void * myobj1_new(t_symbol * arg1, t_floatarg arg2) {
    t_myobj1 *x = (t_myobj1 *) pd_new(myobj1_class);
    post("My OBJ 1");
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);
    return (void *) x;
}

// Constructor of the class
void * myobj2_new(t_symbol * arg1, t_floatarg arg2) {
    t_myobj2 *x = (t_myobj2 *) pd_new(myobj2_class);
    post("My OBJ 2");
    post("First arg: %s", arg1->s_name);
    post("Second arg: %f", arg2);
    return (void *) x;
}

void example03_setup(void) {
    post("Initializing my library");

    myobj1_class = class_new(gensym("myobj1"),
            (t_newmethod) myobj1_new, // Constructor
            0,
            sizeof (t_myobj1),
	    CLASS_NOINLET,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0);
    class_sethelpsymbol(myobj1_class, gensym("myobj1-help"));

    myobj2_class = class_new(gensym("myobj2"),
            (t_newmethod) myobj2_new, // Constructor
            0,
            sizeof (t_myobj2),
	    CLASS_NOINLET,
            A_DEFFLOAT, // First Constructor parameter
            A_DEFSYMBOL, // Second Consctructo parameter
            0);
    class_sethelpsymbol(myobj2_class, gensym("myobj2-help"));

}

