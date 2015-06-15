// PD external API
#include "m_pd.h"

static t_class *example06_class;

typedef struct _example06 {
  t_object x_obj;
  t_float my_float;
  t_outlet *my_outlet; // defines an outlet
} t_example06;

// The BANG method, first inlet
void example06_bang(t_example06 *x) {
  post("BANGED!");
  post("my_float value: %f",x->my_float);
  outlet_bang(x->my_outlet); // Bang my outlet
}

void example06_anything(t_example06 *x, t_symbol *s, int argc, t_atom *argv){
   (void)x;
   (void)s;
   (void)argc;
   (void)argv;
   post("ANYTHING!");
}

// Constructor of the class
void * example06_new(t_symbol * arg1, t_floatarg arg2) {
  t_example06 *x = (t_example06 *) pd_new(example06_class);
  post("First arg: %s", arg1->s_name);
  post("Second arg: %f", arg2);
  // passive inlet
  floatinlet_new(&x->x_obj, &x->my_float); 
  // bang outlet
  x->my_outlet = outlet_new(&x->x_obj, gensym("bang"));
  return (void *) x;
}

void example06_setup(void) {
  example06_class = class_new(gensym("example06"),
    (t_newmethod) example06_new, // Constructor
    0, sizeof (t_example06), CLASS_DEFAULT,
    A_DEFFLOAT,  // 1st constructor parameter
    A_DEFSYMBOL, // 2nd constructor parameter
    0); // LAST argument is ALWAYS zero

  class_addbang(example06_class, example06_bang); // 
  class_addanything(example06_class, example06_anything);
}

