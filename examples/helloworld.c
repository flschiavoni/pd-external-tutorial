/* Plugin structure generated by Schiavoni Pure Data external Generator */
#include "m_pd.h"

// ---------------------------------------------------
// Class definition
// ---------------------------------------------------
static t_class *helloworld_class;

// ---------------------------------------------------
// Data structure definition
// ---------------------------------------------------
typedef struct _helloworld {
   t_object x_obj;
} t_helloworld;

// ---------------------------------------------------
// Functions signature
// ---------------------------------------------------
void * helloworld_new(void);// Constructor
void helloworld_destroy(t_helloworld *x); //Destructor

// ---------------------------------------------------
// Constructor of the class
// ---------------------------------------------------
void * helloworld_new(void){
   t_helloworld *x = (t_helloworld *) pd_new(helloworld_class);
   return (void *) x;
}

// ---------------------------------------------------
// Destroy the class
// ---------------------------------------------------
void helloworld_destroy(t_helloworld *x) {
   (void) x;
   post("You say good bye and I say hello");
}

// ---------------------------------------------------
// Setup
// ---------------------------------------------------
void helloworld_setup(void) {
   helloworld_class = class_new(gensym("helloworld"),
      (t_newmethod) helloworld_new, // Constructor
      (t_method) helloworld_destroy, // Destructor
      sizeof (t_helloworld),
      CLASS_NOINLET,
      0);//Must always ends with a zero

}
// EOF---------------------------------------------------
