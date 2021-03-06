/* Plugin structure generated by Schiavoni Pure Data external Generator */
#include "m_pd.h"

// ---------------------------------------------------
// Class definition
// ---------------------------------------------------
static t_class *multigain_class;

// ---------------------------------------------------
// Data structure definition
// ---------------------------------------------------
typedef struct _multigain {
   t_object x_obj;
   t_int count;
   t_float gain;
   t_inlet * x_inlet_gain_float;
   t_sample ** invec;
   t_sample ** outvec;
} t_multigain;

// ---------------------------------------------------
// Functions signature
// ---------------------------------------------------
void * multigain_new(t_floatarg count_arg);// Constructor
void multigain_destroy(t_multigain *x); //Destructor
static t_int * multigain_perform(t_int *w); //Perform function
static void multigain_dsp(t_multigain *x, t_signal **sp); //DSP function

// ---------------------------------------------------
// Perform
// ---------------------------------------------------
static t_int * multigain_perform(t_int *w){
   t_multigain *x = (t_multigain *)(w[1]);
   int n = (int)(w[2]), i = 0, j = 0;
   float gain = x->gain;
   for(; i < x->count ; i++)
      for(j = 0 ; j < n ; j++)
         x->outvec[i][j] = x->invec[i][j] * gain;
   return (w + 3); // proximo bloco
}

// ---------------------------------------------------
// DSP Function
// ---------------------------------------------------
static void multigain_dsp(t_multigain *x, t_signal **sp){
   if(x->count < 1) return;
   int i = 0;
   for(; i < x->count; i++){
      x->invec[i] = getbytes(sys_getblksize() * sizeof(t_sample));
      x->invec[i] = sp[i]->s_vec;
   }
   for(i = 0; i < x->count ; i++){
      x->outvec[i] = getbytes(sys_getblksize() * sizeof(t_sample));
      x->outvec[i] = sp[x->count + i]->s_vec;
   }
   dsp_add(multigain_perform, 2, x, sp[0]->s_n);
}

// ---------------------------------------------------
// Constructor of the class
// ---------------------------------------------------
void * multigain_new(t_floatarg count_arg){
   t_multigain *x = (t_multigain *) pd_new(multigain_class);
   x->count = (int)count_arg;
   short i;
   for (i = 0; i < x->count; i++) {
      inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // signal inlets
      outlet_new(&x->x_obj, &s_signal);
   }
   x->outvec = getbytes(sizeof(t_sample) * x->count);
   x->invec = getbytes(sizeof(t_sample) * x->count);
   x->x_inlet_gain_float = floatinlet_new(&x->x_obj, &x->gain);
   return (void *) x;
}

// ---------------------------------------------------
// Destroy the class
// ---------------------------------------------------
void multigain_destroy(t_multigain *x) {
   x->count = 0;
   inlet_free(x->x_inlet_gain_float);
}

// ---------------------------------------------------
// Setup
// ---------------------------------------------------
void multigain_tilde_setup(void) {
   multigain_class = class_new(gensym("multigain~"),
      (t_newmethod) multigain_new, // Constructor
      (t_method) multigain_destroy, // Destructor
      sizeof (t_multigain),
      CLASS_NOINLET,
      A_DEFFLOAT,
      0);//Must always ends with a zero

   class_addmethod(multigain_class, (t_method) multigain_dsp, gensym("dsp"), 0);
}
// EOF---------------------------------------------------
