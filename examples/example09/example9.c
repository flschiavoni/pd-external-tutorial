// PD external API
#include "m_pd.h"

static t_class *example9_class;

typedef struct _example9 {
    t_object x_obj;
} t_example9;


// Constructos of the class
void * example9_new(t_symbol *s, int argc, t_atom * argv) {
    t_example9 *x = (t_example9 *) pd_new(example9_class);
    post("%d parameters received",argc);
    return (void *) x;
}

// Destroy the class
void example9_destroy(t_example9 *x) {
   post("You say good bye and I say hello");
}


void example9_setup(void) {
    example9_class = class_new(gensym("example9"),
            (t_newmethod) example9_new, // Constructor
            (t_method) example9_destroy, // Destructor
            sizeof (t_example9),
	    CLASS_NOINLET,
	    A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero
}

