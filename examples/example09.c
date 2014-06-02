// PD external API
#include "m_pd.h"

static t_class *example09_class;

typedef struct _example09 {
    t_object x_obj;
} t_example09;


// Constructor of the class
void * example09_new(t_symbol *s, int argc, t_atom * argv) {
    t_example09 *x = (t_example09 *) pd_new(example09_class);
    post("External name: %s", s->s_name);
    post("%d parameters received",argc);
    (void) argv;
    if(argc < 1){
       post("Please, gimme some parameters!");
       return NULL;
    }
    if(argv[0].a_type != A_FLOAT){
      post("Please, gimme a float!");
      return NULL;
    }
    return (void *) x;
}

// Destroy the class
void example09_destroy(t_example09 *x) {
   (void) x;
   post("You say good bye and I say hello");
}


void example09_setup(void) {
    example09_class = class_new(gensym("example09"),
            (t_newmethod) example09_new, // Constructor
            (t_method) example09_destroy, // Destructor
            sizeof (t_example09),
            CLASS_NOINLET,
            A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero
}

