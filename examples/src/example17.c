// PD external API
#include "m_pd.h"

static t_class *example17_class;

typedef struct _example17 {
   t_object x_obj;
   t_int outlet_counter;
   t_int inlet_counter;
} t_example17;

// Constructor of the class
void * example17_new(t_symbol *s, t_floatarg inlet_counter, t_floatarg outlet_counter) {
  t_example17 *x = (t_example17 *) pd_new(example17_class);
  int i;
  post("inlet counter: %f", inlet_counter);
  post("outlet counter: %f", outlet_counter);
  x->inlet_counter = inlet_counter;
  x->outlet_counter = outlet_counter;
  for(i = 0 ; i < inlet_counter ; i++)
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  for(i = 0 ; i < outlet_counter ; i++)
    outlet_new(&x->x_obj, &s_signal);
  return (void *) x;
}

// Destroy the class
void example17_destroy(t_example17 *x) {
   post("You say good bye and I say hello");
}


static t_int * example17_perform(t_int *w){
  t_example17 *x = (t_example17 *)(w[1]);
  int n = (int)(w[2]), i;
  for(i = 0 ; i < x->inlet_counter ; i++) {
    // DO something with the input
  }
  for(i = 0 ; i < x->outlet_counter ; i++) {
    // DO something with the output
  }
  return (w + (2 + x->inlet_counter + x->outlet_counter +1));
}

static void example17_dsp(t_example17 *x, t_signal **sp){
  int qtd = x->inlet_counter + x->outlet_counter + 2;
  dsp_add(example17_perform, qtd , x, sp[0]->s_n, sp[0]->s_vec);
}

void example17_setup(void) {
  example17_class = class_new(gensym("example17"),
    (t_newmethod) example17_new, // Constructor
    (t_method) example17_destroy, // Destructor
    sizeof (t_example17),
    CLASS_NOINLET,
    A_DEFFLOAT, // # of inlets
    A_DEFFLOAT, // # of outlets
    0); // LAST argument is ALWAYS zero
    class_addmethod(example17_class, (t_method) example17_dsp, gensym("dsp"), 0);
}

