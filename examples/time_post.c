/* Plugin structure generated by Schiavoni Pure Data external Generator */
#include "m_pd.h"

// ---------------------------------------------------
// Class definition
// ---------------------------------------------------
static t_class *time_post_class;

// ---------------------------------------------------
// Data structure definition
// ---------------------------------------------------
typedef struct _time_post {
   t_object x_obj;
   t_float time;
   t_clock  *x_clock;
   double last_time;
} t_time_post;

// ---------------------------------------------------
// Functions signature
// ---------------------------------------------------
void * time_post_new(t_floatarg time_arg);// Constructor
void time_post_destroy(t_time_post *x); //Destructor
void time_post_doit(t_time_post * x);


// ---------------------------------------------------
// Clock do it function
// ---------------------------------------------------
void time_post_doit(t_time_post * x){
   double now = clock_getlogicaltime();
   post("logical time: %f, last_time: %f (%f)", now, x->last_time, now - x->last_time);
   x->last_time = now;
   clock_delay(x->x_clock, x->time);
}

// ---------------------------------------------------
// Constructor of the class
// ---------------------------------------------------
void * time_post_new(t_floatarg time_arg){
   t_time_post *x = (t_time_post *) pd_new(time_post_class);
   x->time = time_arg;

   x->x_clock = clock_new(x, (t_method)time_post_doit);
   x->last_time = clock_getlogicaltime();
   clock_delay(x->x_clock, x->time);
   return (void *) x;
}

// ---------------------------------------------------
// Destroy the class
// ---------------------------------------------------
void time_post_destroy(t_time_post *x) {
   clock_unset(x->x_clock);
   clock_free(x->x_clock);
}

// ---------------------------------------------------
// Setup
// ---------------------------------------------------
void time_post_setup(void) {
   time_post_class = class_new(gensym("time_post"),
      (t_newmethod) time_post_new, // Constructor
      (t_method) time_post_destroy, // Destructor
      sizeof (t_time_post),
      CLASS_NOINLET,
      A_DEFFLOAT,
      0);//Must always ends with a zero

}
// EOF---------------------------------------------------
