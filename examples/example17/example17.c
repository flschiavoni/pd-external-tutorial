// PD external API
#include "m_pd.h"

static t_class *example17_class;

typedef struct _example17 {
    t_object x_obj;
    t_int outlet_counter;
    t_int inlet_counter;
} t_example17;


// Constructos of the class
void * example17_new(t_symbol *s, t_intarg inlet_counter, t_intarg outlet_counter) {
    t_example17 *x = (t_example17 *) pd_new(example17_class);

    post("inlet counter %d",inlet_counter);
    post("outlet counter %d",outlet_counter);

    return (void *) x;
}

// Destroy the class
void example17_destroy(t_example17 *x) {
   post("You say good bye and I say hello");
}

/*
static t_int * example17_perform(t_int *w){
   t_float *in1 = (t_float *)(w[1]);
   t_float *in2 = (t_float *)(w[2]);
   t_float *in3 = (t_float *)(w[3]);
   t_float *in4 = (t_float *)(w[4]);
   t_float *out1 = (t_float *)(w[5]);
   t_float *out2 = (t_float *)(w[6]);
   t_float *out3 = (t_float *)(w[7]);
   t_float *out4 = (t_float *)(w[8]);
   int n = (int)(w[9]);
   t_example17 *x = (t_example17 *)(w[10]);
  return (w + 11); // proximo bloco
}
*/
static void example17_dsp(t_example17 *x, t_signal **sp){
  //dsp_add(example17_perform, 10, sp[0]->s_vec, sp[0]->s_n, x); //adiciona um metodo para tratar o dsp. Será executado a cada bloco de execução do PD.
  // Pelo que entendi:
  // 3 - qtd de argumentos
  // sp[0]->s_vec - vetor de saida
  // sp[0]->s_n - tamanho do vetor
  // x - referencia a minha classe
}


void example17_setup(void) {
    example17_class = class_new(gensym("example17"),
            (t_newmethod) example17_new, // Constructor
            (t_method) example17_destroy, // Destructor
            sizeof (t_example17),
	    CLASS_NOINLET,
	    A_FLOAT, // # of inlets
	    A_FLOAT, // # of outlets
            0); // LAST argument is ALWAYS zero

    class_addmethod(example17_class, (t_method) example17_dsp, gensym("dsp"), 0);

}

