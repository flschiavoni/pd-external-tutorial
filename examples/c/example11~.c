// PD external API
#include "m_pd.h"

static t_class *example11_class;

typedef struct _example11 {
    t_object x_obj;
    t_float x_f;          /* place to hold inlet's value if it's set by message */
} t_example11;


// Constructor of the class
void * example11_new(t_symbol *s, int argc, t_atom * argv) {
    t_example11 *x = (t_example11 *) pd_new(example11_class);
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // second signal inlet
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // third signal inlet
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // fourth signal inlet
    return (void *) x;
}

// Destroy the class
void example11_destroy(t_example11 *x) {
   post("You say good bye and I say hello");
}

static t_int * example11_perform(t_int *w){
  t_float *in1 = (t_float *)(w[1]);
  t_float *in2 = (t_float *)(w[2]);
  t_float *in3 = (t_float *)(w[3]);
  t_float *in4 = (t_float *)(w[4]);
  int n = (int)(w[5]);
  t_example11 *x = (t_example11 *)(w[6]);
  return (w + 7); // proximo bloco
}

static void example11_dsp(t_example11 *x, t_signal **sp){
  dsp_add(example11_perform, 6, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n, x);
}

void example11_tilde_setup(void) {
    example11_class = class_new(gensym("example11~"),
            (t_newmethod) example11_new, // Constructor
            (t_method) example11_destroy, // Destructor
            sizeof (t_example11),
	    CLASS_DEFAULT,
	    A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero

  /* this is magic to declare that the leftmost, "main" inlet
     takes signals; other signal inlets are done differently...*/
    CLASS_MAINSIGNALIN(example11_class, t_example11, x_f);
    class_addmethod(example11_class, (t_method) example11_dsp, gensym("dsp"), 0); // This method will add a signal inlet and associate a method to do this

}

