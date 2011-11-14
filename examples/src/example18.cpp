// PD external API
#include "m_pd.h"

#ifndef EXAMPLE18_H
#define EXAMPLE18_H


namespace soundtouch{
	class RateTransposer : public FIFOProcessor{
		static t_class *example18_class;

typedef struct _example18 {
    t_object x_obj;
} t_example18;


// Constructos of the class
void * example18_new(void) {
    t_example18 *x = (t_example18 *) pd_new(example18_class);
    return (void *) x;
}

extern "C" void example18_setup(void) {
    example18_class = class_new(gensym("example18"),
            (t_newmethod) example18_new, // Constructor
            0,
            sizeof (t_example18),
	    CLASS_NOINLET,
            0);
};
}


#endif
