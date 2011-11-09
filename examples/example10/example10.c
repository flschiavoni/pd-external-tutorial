// PD external API
#include "m_pd.h"

static t_class *example10_class;

typedef struct _example10 {
    t_object x_obj;
    t_float x_f;          /* place to hold inlet's value if it's set by message */
} t_example10;


// Constructos of the class
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
   t_float *in = (t_float *)(w[1]);
   int n = (int)(w[2]);
   t_example10 *x = (t_example10 *)(w[3]);
  return (w + 4); // proximo bloco
}

static void example10_dsp(t_example10 *x, t_signal **sp){
  dsp_add(example10_perform, 3, sp[0]->s_vec, sp[0]->s_n, x); //adiciona um metodo para tratar o dsp. Será executado a cada bloco de execução do PD.
  // Pelo que entendi:
  // 3 - qtd de argumentos
  // sp[0]->s_vec - vetor de saida
  // sp[0]->s_n - tamanho do vetor
  // x - referencia a minha classe
}


void example10_setup(void) {
    example10_class = class_new(gensym("example10"),
            (t_newmethod) example10_new, // Constructor
            (t_method) example10_destroy, // Destructor
            sizeof (t_example10),
	    CLASS_DEFAULT,
	    A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero

  /* this is magic to declare that the leftmost, "main" inlet
     takes signals; other signal inlets are done differently...*/
     CLASS_MAINSIGNALIN(example10_class, t_example10, x_f);

    class_addmethod(example10_class, (t_method) example10_dsp, gensym("dsp"), 0); // This method will add a signal inlet and associate a method to do this

}

