// PD external API
#include "m_pd.h"

static t_class *example13_class;

typedef struct _example13 {
    t_object x_obj;
    t_float x_f;          /* place to hold inlet's value if it's set by message */
} t_example13;


// Constructos of the class
void * example13_new(t_symbol *s, int argc, t_atom * argv) {
    t_example13 *x = (t_example13 *) pd_new(example13_class);

    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // second signal inlet
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // third signal inlet
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // fourth signal inlet

    outlet_new(&x->x_obj, &s_signal); // first signal outlet
    outlet_new(&x->x_obj, &s_signal); // second signal outlet
    outlet_new(&x->x_obj, &s_signal); // third signal outlet
    outlet_new(&x->x_obj, &s_signal); // fourth signal outlet
    return (void *) x;
}

// Destroy the class
void example13_destroy(t_example13 *x) {
   post("You say good bye and I say hello");
}

static t_int * example13_perform(t_int *w){
   t_float *in1 = (t_float *)(w[1]);
   t_float *in2 = (t_float *)(w[2]);
   t_float *in3 = (t_float *)(w[3]);
   t_float *in4 = (t_float *)(w[4]);
   t_float *out1 = (t_float *)(w[5]);
   t_float *out2 = (t_float *)(w[6]);
   t_float *out3 = (t_float *)(w[7]);
   t_float *out4 = (t_float *)(w[8]);
   int n = (int)(w[9]);
   t_example13 *x = (t_example13 *)(w[10]);
  return (w + 11); // proximo bloco
}

static void example13_dsp(t_example13 *x, t_signal **sp){
  dsp_add(example13_perform, 10, sp[0]->s_vec, sp[0]->s_n, x); //adiciona um metodo para tratar o dsp. Será executado a cada bloco de execução do PD.
  // Pelo que entendi:
  // 3 - qtd de argumentos
  // sp[0]->s_vec - vetor de saida
  // sp[0]->s_n - tamanho do vetor
  // x - referencia a minha classe
}


void example13_setup(void) {
    example13_class = class_new(gensym("example13"),
            (t_newmethod) example13_new, // Constructor
            (t_method) example13_destroy, // Destructor
            sizeof (t_example13),
	    CLASS_DEFAULT,
	    A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero

    CLASS_MAINSIGNALIN(example13_class, t_example13, x_f);
    class_addmethod(example13_class, (t_method) example13_dsp, gensym("dsp"), 0); // This method will add a signal inlet and associate a method to do this

}

