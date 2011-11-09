// PD external API
#include "m_pd.h"

static t_class *example01_class;

typedef struct _example01 {
    t_object x_obj;
} t_example01;


// Constructos of the class
void * example01_new(void) {
    t_example01 *x = (t_example01 *) pd_new(example01_class);
    return (void *) x;
}

void example01_setup(void) {
    example01_class = class_new(gensym("example01"),
            (t_newmethod) example01_new, // Constructor
            0,
            sizeof (t_example01),
	    CLASS_NOINLET,
            0);
}

