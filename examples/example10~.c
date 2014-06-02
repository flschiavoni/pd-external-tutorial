// PD external API
#include "m_pd.h"

static t_class *example10_class;

typedef struct _example10 {
    t_object x_obj;
    t_float x_f; /* inlet value when set by message */
} t_example10;

// Constructor of the class
void * example10_new(t_symbol *s, int argc, t_atom * argv) {
    t_example10 *x = (t_example10 *) pd_new(example10_class);
    post("%d parameters received",argc);
    return (void *) x;
}

// Destroy the class
void example10_destroy(t_example10 *x) {
   post("You say good bye and I say hello");
}

static t_int * example10_perform(t_int *w){
  t_float     *in = (t_float *) (w[1]);
  int          n  = (int) (w[2]);
  t_example10 *x  = (t_example10 *) (w[3]);
  // do something ...
  return (w + 4); // next block's address
}

static void example10_dsp(t_example10 *x, t_signal **sp){
  // adds a method for dsp
  dsp_add(example10_perform, 3, sp[0]->s_vec, sp[0]->s_n, x);
}

void example10_bang_method(t_example10 *x){
   (void) x;
   post("BANG!");
}

void example10_tilde_setup(void) {
  example10_class = class_new(gensym("example10~"),
    (t_newmethod) example10_new, // Constructor
    (t_method) example10_destroy, // Destructor
    sizeof (t_example10), CLASS_DEFAULT, A_GIMME, 0);
  // this declares the leftmost, "main" inlet
  // as taking signals.
   CLASS_MAINSIGNALIN(example10_class, t_example10, x_f);
   class_addmethod(example10_class, (t_method) example10_dsp, gensym("dsp"), 0);
   class_addbang(example10_class, example10_bang_method);
}

