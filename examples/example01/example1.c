// PD external API
#include "m_pd.h"

static t_class *example1_class;

typedef struct _example1 {
    t_object x_obj;
} t_example1;


// Constructos of the class
void * example1_new(void) {
    t_example1 *x = (t_example1 *) pd_new(example1_class);
    return (void *) x;
}

void example1_setup(void) {
    example1_class = class_new(gensym("example1"),
            (t_newmethod) example1_new, // Constructor
            0,
            sizeof (t_example1),
	    CLASS_NOINLET,
            0);
}

