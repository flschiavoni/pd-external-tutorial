// PD external API
#include "m_pd.h"

static t_class *example12_class;

typedef struct _example12 {
    t_object x_obj;
    t_float x_f;          /* place to hold inlet's value if it's set by message */
} t_example12;


// Constructos of the class
void * example12_new(t_symbol *s, int argc, t_atom * argv) {
    t_example12 *x = (t_example12 *) pd_new(example12_class);
    outlet_new(&x->x_obj, &s_signal); // first signal outlet
    outlet_new(&x->x_obj, &s_signal); // second signal outlet
    outlet_new(&x->x_obj, &s_signal); // third signal outlet
    outlet_new(&x->x_obj, &s_signal); // fourth signal outlet
    return (void *) x;
}

// Destroy the class
void example12_destroy(t_example12 *x) {
   post("You say good bye and I say hello");
}

static t_int * example12_perform(t_int *w){
   t_float *out1 = (t_float *)(w[1]);
   t_float *out2 = (t_float *)(w[2]);
   t_float *out3 = (t_float *)(w[3]);
   t_float *out4 = (t_float *)(w[4]);
   int n = (int)(w[5]);
   t_example12 *x = (t_example12 *)(w[6]);
  return (w + 7); // proximo bloco
}

static void example12_dsp(t_example12 *x, t_signal **sp){
  dsp_add(example12_perform, 6, sp[0]->s_vec, sp[0]->s_n, x); //adiciona um metodo para tratar o dsp. Será executado a cada bloco de execução do PD.
  // Pelo que entendi:
  // 3 - qtd de argumentos
  // sp[0]->s_vec - vetor de saida
  // sp[0]->s_n - tamanho do vetor
  // x - referencia a minha classe
}


void example12_setup(void) {
    example12_class = class_new(gensym("example12"),
            (t_newmethod) example12_new, // Constructor
            (t_method) example12_destroy, // Destructor
            sizeof (t_example12),
	    CLASS_DEFAULT,
	    A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero

    class_addmethod(example12_class, (t_method) example12_dsp, gensym("dsp"), 0); // This method will add a signal inlet and associate a method to do this

}

