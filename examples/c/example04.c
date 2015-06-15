// PD external API
#include "m_pd.h"

static t_class *example04_class;

static float counter = 0;
typedef struct _example04 {
    t_object x_obj;
    t_float my_float;// Creates a my_float variable into the structure
} t_example04;


// Constructor of the class
void * example04_new(){
    t_example04 *x = (t_example04 *) pd_new(example04_class);
    floatinlet_new(&x->x_obj, &x->my_float); //create a passive inlet which value will be stored into my_float variable
    counter++;
    post("%f", counter);
    return (void *) x;
}

void example04_destroy(t_example04 * x){
   (void) x;
   counter--;
   post("Goodbye Dave!");
}

void example04_setup(void) {
    example04_class = class_new(gensym("example04"),
            (t_newmethod) example04_new, // Constructor
            (t_method) example04_destroy,
            sizeof (t_example04),
            CLASS_NOINLET,
            0); // LAST argument is ALWAYS zero
}

