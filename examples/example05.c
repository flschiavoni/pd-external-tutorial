// PD external API
#include "m_pd.h"

static t_class *example05_class;

typedef struct _example05 {
    t_object x_obj;
} t_example05;

// The BANG method, first inlet

void example05_bang(t_example05 *x) { // The method will always receive the class as argument
   (void) x;
   post("BANGED!");
}

void example05_anything(t_example05 *x, t_symbol *s, int argc, t_atom *argv){
   (void)x;
   (void)s;
   (void)argc;
   (void)argv;
   post("ANYTHING!");
}

// Constructor of the class
void * example05_new() {
    t_example05 *x = (t_example05 *) pd_new(example05_class);
    return (void *) x;
}

void example05_setup(void) {
    example05_class = class_new(gensym("example05"),
            (t_newmethod) example05_new, // Constructor
            0, 
            sizeof (t_example05),
            CLASS_DEFAULT,
            0); // LAST argument is ALWAYS zero
    class_addbang(example05_class, example05_bang);
    class_addanything(example05_class, example05_anything);

}

