// PD external API
#include "m_pd.h"

static t_class *example16_class;


typedef struct _example16 {
    t_object x_obj;
} t_example16;

int count = 0;

void * example16_new(void) {
    t_example16 *x = (t_example16 *) pd_new(example16_class);
    post("Counter value: %d",count);
    count++;
    return (void *) x;
}

void example16_setup(void) {
    example16_class = class_new(gensym("example16"),
            (t_newmethod) example16_new, // Constructor
            0,
            sizeof (t_example16),
	    CLASS_NOINLET,
            0);
}

