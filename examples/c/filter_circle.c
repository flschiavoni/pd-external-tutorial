/* Plugin structure generated by Schiavoni Pure Data external Generator */
#include "m_pd.h"
#include "g_canvas.h"

// ---------------------------------------------------
// Class definition
// ---------------------------------------------------
static t_class *filter_circle_class;
t_widgetbehavior filter_circle_widgetbehavior; // This represents the external GUI

// ---------------------------------------------------
// Data structure definition
// ---------------------------------------------------
typedef struct _filter_circle {
   t_object x_obj;
   t_float pole_radius;
   t_float pole_angle;
   t_float zero_radius;
   t_float zero_angle;
   t_outlet * x_outlet_coefficiente_list;
} t_filter_circle;

// ---------------------------------------------------
// Functions signature
// ---------------------------------------------------
void * filter_circle_new(t_floatarg zero_radius_arg, t_floatarg zero_angle_arg, t_floatarg pole_radius_arg, t_floatarg pole_angle_arg);// Constructor
void filter_circle_destroy(t_filter_circle *x); //Destructor
void filter_circle_zeros(t_filter_circle *x, t_floatarg f0, t_floatarg f1); // Message function
void filter_circle_poles(t_filter_circle *x, t_floatarg f0, t_floatarg f1); // Message function
void filter_circle_bang_method(t_filter_circle *x);// Active inlet function
//GUI stuff
static void filter_circle_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2);
static void filter_circle_vis(t_gobj *z, t_glist *glist, int vis);
static void filter_circle_displace(t_gobj *z, t_glist *glist,int dx, int dy);
static void filter_circle_activate(t_gobj *x, struct _glist *glist, int state);
static void filter_circle_select(t_gobj *z, t_glist *glist, int state);
static int filter_circle_click(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit);
static void filter_circle_delete(t_gobj *z, t_glist *glist);
static void filter_circle_save(t_gobj *c, t_binbuf *b);
static void filter_circle_properties(t_gobj *c, t_glist *list);

// ---------------------------------------------------
// Constructor of the class
// ---------------------------------------------------
void * filter_circle_new(
      t_floatarg pole_radius_arg,
      t_floatarg pole_angle_arg,
      t_floatarg zero_radius_arg,
      t_floatarg zero_angle_arg
      ){
   t_filter_circle *x = (t_filter_circle *) pd_new(filter_circle_class);

   x->zero_radius = zero_radius_arg;
   x->zero_angle = zero_angle_arg;
   x->pole_radius = pole_radius_arg;
   x->pole_angle = pole_angle_arg;

   char buf[256];
   sprintf(buf,"filter_circle%lx", (long unsigned int)x);
   pd_bind(&x->x_obj.ob_pd, gensym(buf));

   x->x_outlet_coefficiente_list = outlet_new(&x->x_obj, gensym("list"));
   return (void *) x;
}

// ---------------------------------------------------
// Destroy the class
// ---------------------------------------------------
void filter_circle_destroy(t_filter_circle *x) {
   (void) x;
   char buf[256];
   sprintf(buf,"filter_circle%lx", (long unsigned int)x);
   pd_unbind(&x->x_obj.ob_pd, gensym(buf));
   outlet_free(x->x_outlet_coefficiente_list);
}

// ---------------------------------------------------
// filter_circle_zeros
// ---------------------------------------------------
void filter_circle_zeros(t_filter_circle *x, t_floatarg f0, t_floatarg f1){
   x->zero_radius = f0;
   x->zero_angle = f1;
}

// ---------------------------------------------------
// filter_circle_poles
// ---------------------------------------------------
void filter_circle_poles(t_filter_circle *x, t_floatarg f0, t_floatarg f1){
   x->pole_radius = f0;
   x->pole_angle = f1;
}

// ---------------------------------------------------
// filter_circle_bang
// ---------------------------------------------------
void filter_circle_bang_method(t_filter_circle *x){
   t_atom coefficients[6];
   //Falta calcular os coeficientes
   SETFLOAT(coefficients+0, 0);
   SETFLOAT(coefficients+1, 0);
   SETFLOAT(coefficients+2, 0);
   SETFLOAT(coefficients+3, 0);
   SETFLOAT(coefficients+4, 0);
   SETFLOAT(coefficients+5, 0);
   outlet_list(x->x_outlet_coefficiente_list, gensym("list"), 6, coefficients);
}

//GUI stuff ---------------------------------------
// ---------------------------------------------------
// The external GUI rectangle definition
// ---------------------------------------------------
static void filter_circle_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2){
   // This function is always called. 
   // Better do not put a post here...
   // post("GETRECT");
   (void) glist;
   t_filter_circle *x = (t_filter_circle *)z;
   *xp1 = x->x_obj.te_xpix;
   *yp1 = x->x_obj.te_ypix;
   *xp2 = x->x_obj.te_xpix + 355;
   *yp2 = x->x_obj.te_ypix + 220;
}

// ---------------------------------------------------
// Create TCL procedures
// ---------------------------------------------------
static void filter_circle_create_procs(t_filter_circle *x, t_canvas *canvas){

   sys_vgui("proc update_labels%lx {} {\
            set pole_radius [.x%lx.c.s1%lx get ] \n \
            set pole_angle  [.x%lx.c.s2%lx get ] \n \
            set zero_radius [.x%lx.c.s3%lx get ] \n \
            set zero_angle  [.x%lx.c.s4%lx get ] \n \
            set P0rad [concat P0([decimal [expr $pole_radius / 90]], $pole_angle)] \n \
            set P1rad [concat P0([decimal [expr $pole_radius / 90]], [expr 360 - $pole_angle])] \n \
            set Z0rad [concat P0([decimal [expr $zero_radius / 90]], $zero_angle)] \n \
            set Z1rad [concat P0([decimal [expr $zero_radius / 90]], [expr 360 - $zero_angle])] \n \
            .x%lx.c.l1%lx configure -text [ concat $P0rad $P1rad $Z0rad $Z1rad] \n \
            \
            set pole_x1 [decimal [expr cos($pole_angle / 180 * [pi]) * $pole_radius / 90]] \n \
            set pole_y1 [decimal [expr sin($pole_angle / 180 * [pi]) * $pole_radius / 90]] \n \
            set zero_x1 [decimal [expr cos($zero_angle / 180 * [pi]) * $pole_radius / 90]] \n \
            set zero_y1 [decimal [expr sin($zero_angle / 180 * [pi]) * $pole_radius / 90]] \n \
            set P0xy [concat P0($pole_x1,$pole_y1)] \n \
            set P1xy [concat P0($pole_x1, [expr $pole_y1 * -1])] \n \
            set Z0xy [concat P0($zero_x1,$zero_y1)] \n \
            set Z1xy [concat P0($zero_x1, [expr $zero_y1 * -1])] \n \
            \
            .x%lx.c.l2%lx configure -text [ concat $P0xy $P1xy $Z0xy $Z1xy] \n \
            } \n",
      x, canvas,
      x, canvas,
      x, canvas,
      x, canvas,
      x,canvas,
      x,canvas,
      x);

   sys_vgui("proc move_pole%lx {value} {\
            set radius [.x%lx.c.s1%lx get ] \n \
            set angle  [.x%lx.c.s2%lx get ] \n \
            set x1 [expr cos($angle / 180 * [pi]) * $radius] \n \
            set y1 [expr sin($angle / 180 * [pi]) * $radius] \n \
            .x%lx.c coords pole_one_%lx %d %d %d %d %d %d %d %d\n \
            .x%lx.c coords pole_two_%lx %d %d %d %d %d %d %d %d\n \
            .x%lx.c move pole_one_%lx $x1 $y1\n \
            .x%lx.c move pole_two_%lx $x1 [expr $y1 * -1] \n \
            pd [concat filter_circle%lx poles $radius $angle \\;]\n\
            update_labels%lx \n \
            }\n",
      x, canvas,
      x, canvas,
      x, canvas,
      x,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 115,
      canvas,
      x,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 115,
      canvas,
      x,
      canvas,
      x,
      x,
      x
      );

   sys_vgui("proc move_zero%lx {value} {\
            set radius [.x%lx.c.s3%lx get ] \n \
            set angle  [.x%lx.c.s4%lx get ] \n \
            set x1 [expr cos($angle / 180 * [pi]) * $radius] \n \
            set y1 [expr sin($angle / 180 * [pi]) * $radius] \n \
            .x%lx.c coords zero_one_%lx %d %d %d %d \n \
            .x%lx.c coords zero_two_%lx %d %d %d %d \n \
            .x%lx.c move zero_one_%lx $x1 $y1\n \
            .x%lx.c move zero_two_%lx $x1 [expr $y1 * -1] \n \
            pd [concat filter_circle%lx zeros $radius $angle \\;]\n\
            update_labels%lx \n \
            }\n",
      x,
      canvas,
      x,
      canvas,
      x,
      canvas,
      x,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,
      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,
      canvas,
      x,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,
      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,
      canvas,
      x,
      canvas,
      x,
      x,
      x
      );
}

// ---------------------------------------------------
// How to make it visible / invisible
// ---------------------------------------------------
static void filter_circle_vis(t_gobj *z, t_glist *glist, int vis){
   t_filter_circle *x = (t_filter_circle *)z;
   t_canvas * canvas = glist_getcanvas(glist);
   if(vis){ // VISIBLE

   sys_vgui(".x%lx.c create rectangle %d %d %d %d -tag rect%lx\n",
      canvas,
      x->x_obj.te_xpix,
      x->x_obj.te_ypix,
      x->x_obj.te_xpix + 355,
      x->x_obj.te_ypix + 220,
      x);
   sys_vgui(".x%lx.c create rectangle %d %d %d %d -tag inlet%lx\n",
      canvas,
      x->x_obj.te_xpix,
      x->x_obj.te_ypix,
      x->x_obj.te_xpix + 7,
      x->x_obj.te_ypix + 3,
      x);
   sys_vgui(".x%lx.c create rectangle %d %d %d %d -tag outlet%lx\n",
      canvas,
      x->x_obj.te_xpix,
      x->x_obj.te_ypix + 217,
      x->x_obj.te_xpix + 7,
      x->x_obj.te_ypix + 220,
      x);
   sys_vgui(".x%lx.c create oval %d %d %d %d -tag circle%lx\n",
      canvas,
      x->x_obj.te_xpix + 20,
      x->x_obj.te_ypix + 20,
      x->x_obj.te_xpix + 200,
      x->x_obj.te_ypix + 200,
      x);
   sys_vgui(".x%lx.c create line %d %d %d %d -tag x_axis_%lx -arrow both\n",
      canvas,
      x->x_obj.te_xpix,
      x->x_obj.te_ypix + 110,
      x->x_obj.te_xpix + 220,
      x->x_obj.te_ypix + 110,
      x);
   sys_vgui(".x%lx.c create line %d %d %d %d -tag y_axis_%lx -arrow both\n",
      canvas,
      x->x_obj.te_xpix + 110,
      x->x_obj.te_ypix + 0,
      x->x_obj.te_xpix + 110,
      x->x_obj.te_ypix + 220,
      x);

   sys_vgui(".x%lx.c create oval %d %d %d %d -tag zero_one_%lx -outline blue\n",
      canvas,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,
      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,
      x);

   sys_vgui(".x%lx.c create oval %d %d %d %d -tag zero_two_%lx -outline blue\n",
      canvas,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,
      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,
      x);

   sys_vgui(".x%lx.c create polygon %d %d %d %d %d %d %d %d -tag pole_one_%lx -fill red\n",
      canvas,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 115,
      x);

   sys_vgui(".x%lx.c create polygon %d %d %d %d %d %d %d %d -tag pole_two_%lx -fill red\n",
      canvas,
      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 115,

      x->x_obj.te_xpix + 115,
      x->x_obj.te_ypix + 105,

      x->x_obj.te_xpix + 105,
      x->x_obj.te_ypix + 115,
      x);

   sys_vgui("scale .x%lx.c.s1%lx \
               -from 0 -to 90 \
               -label \"Poles (Radius)\" \
               -orient horizontal \
               -resolution 0.001 \
               -showvalue false \
               \n",
      canvas,
      x);
   sys_vgui(".x%lx.c create window %d %d -window .x%lx.c.s1%lx \
               -tag poles_radius_%lx \
               \n",
      canvas,
      x->x_obj.te_xpix + 300,
      x->x_obj.te_ypix + 30,
      canvas,
      x,
      x);

   sys_vgui("scale .x%lx.c.s2%lx \
               -from 0 -to 180 \
               -label \"Poles (Angle)\" \
               -orient horizontal \
               -resolution 0.001 \
               -showvalue false \
               \n",
      canvas,
      x);
   sys_vgui(".x%lx.c create window %d %d -window .x%lx.c.s2%lx \
               -tag poles_angle_%lx \
               \n",
      canvas,
      x->x_obj.te_xpix + 300,
      x->x_obj.te_ypix + 70,
      canvas,
      x,
      x);

   sys_vgui("scale .x%lx.c.s3%lx \
               -from 0 -to 90 \
               -label \"Zero (Radius)\" \
               -orient horizontal \
               -resolution 0.01 \
               -showvalue false \
               \n",
      canvas,
      x);
   sys_vgui(".x%lx.c create window %d %d -window .x%lx.c.s3%lx \
               -tag zero_radius_%lx \
               \n",
      canvas,
      x->x_obj.te_xpix + 300,
      x->x_obj.te_ypix + 110,
      canvas,
      x,
      x);

   sys_vgui("scale .x%lx.c.s4%lx \
               -from 0 -to 180 \
               -label \"Zero (Angle)\" \
               -orient horizontal \
               -resolution 0.01 \
               -showvalue false \
               \n",
      canvas,
      x);
   sys_vgui(".x%lx.c create window %d %d -window .x%lx.c.s4%lx \
               -tag zero_angle_%lx \
               \n",
      canvas,
      x->x_obj.te_xpix + 300,
      x->x_obj.te_ypix + 150,
      canvas,
      x,
      x);

   sys_vgui("label .x%lx.c.l1%lx \
               -justify right \
               \n",
      canvas,
      x);
   sys_vgui(".x%lx.c create window %d %d \
               -window .x%lx.c.l1%lx \
               -tag label1_%lx \
               \n",
      canvas,
      x->x_obj.te_xpix + 200,
      x->x_obj.te_ypix + 190,
      canvas,
      x,
      x);

   sys_vgui("label .x%lx.c.l2%lx \
               -justify right \
               \n",
      canvas,
      x);
   sys_vgui(".x%lx.c create window %d %d \
               -window .x%lx.c.l2%lx \
               -tag label3_%lx \
               \n",
      canvas,
      x->x_obj.te_xpix + 200,
      x->x_obj.te_ypix + 210,
      canvas,
      x,
      x);

   // We need to create it in a function to update when moved
   filter_circle_create_procs(x, canvas);

   sys_vgui(".x%lx.c.s1%lx configure \
               -command {move_pole%lx} \
               \n",
      canvas,
      x,
      x);

   sys_vgui(".x%lx.c.s2%lx configure \
               -command {move_pole%lx} \
               \n",
      canvas,
      x,
      x);

   sys_vgui(".x%lx.c.s3%lx configure \
               -command {move_zero%lx} \
               \n",
      canvas,
      x,
      x);

   sys_vgui(".x%lx.c.s4%lx configure \
               -command {move_zero%lx} \
               \n",
      canvas,
      x,
      x);

   sys_vgui(".x%lx.c.s1%lx set %f \n",
      canvas,
      x,
      x->pole_radius);

   sys_vgui(".x%lx.c.s2%lx set %f \n",
      canvas,
      x,
      x->pole_angle);

   sys_vgui(".x%lx.c.s3%lx set %f \n",
      canvas,
      x,
      x->zero_radius);
   sys_vgui(".x%lx.c.s4%lx set %f \n",
      canvas,
      x,
      x->zero_angle);

   }else{
   sys_vgui(".x%lx.c delete rect%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete inlet%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete outlet%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete circle%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete x_axis_%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete y_axis_%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete zero_one_%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete zero_two_%lx\n", canvas, x);
   sys_vgui(".x%lx.c delete pole_one_%lx \n", canvas, x);
   sys_vgui(".x%lx.c delete pole_two_%lx \n", canvas, x);
   sys_vgui(".x%lx.c delete poles_radius_%lx \n", canvas, x);
   sys_vgui(".x%lx.c delete poles_angle_%lx \n", canvas, x);
   sys_vgui(".x%lx.c delete zero_radius_%lx \n", canvas, x);
   sys_vgui(".x%lx.c delete zero_angle_%lx \n", canvas, x);
   }
}
// ---------------------------------------------------
// what to do when moved
// ---------------------------------------------------
static void filter_circle_displace(t_gobj *z, t_glist *glist,int dx, int dy){
   t_canvas * canvas = glist_getcanvas(glist);
   t_filter_circle *x = (t_filter_circle *)z;
   x->x_obj.te_xpix += dx; // x movement
   x->x_obj.te_ypix += dy; // y movement
   sys_vgui(".x%lx.c move rect%lx          %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move inlet%lx         %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move outlet%lx        %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move circle%lx        %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move x_axis_%lx       %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move y_axis_%lx       %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move zero_one_%lx     %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move zero_two_%lx     %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move pole_one_%lx     %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move pole_two_%lx     %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move poles_radius_%lx %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move poles_angle_%lx  %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move zero_radius_%lx  %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move zero_angle_%lx   %d %d\n", canvas, x, dx, dy);
   sys_vgui(".x%lx.c move %lxSEL           %d %d\n", canvas, x, dx, dy);

   // update tcl procedures to move
   filter_circle_create_procs(x, canvas);

   canvas_fixlinesfor(glist, (t_text *)x);
}
// ---------------------------------------------------
// What to do when active
// ---------------------------------------------------
static void filter_circle_activate(t_gobj *x, struct _glist *glist, int state){
   (void)x;
   (void)glist;
   (void)state;
}
// ---------------------------------------------------
// What to do when selected
// ---------------------------------------------------
static void filter_circle_select(t_gobj *z, t_glist *glist, int state){
   t_filter_circle *x = (t_filter_circle *)z;
   if (state) {
      // We use to draw a blue contour here
      sys_vgui(".x%x.c create rectangle %d %d %d %d -tags %lxSEL -outline blue\n",
         glist_getcanvas(glist),
         x->x_obj.te_xpix,
         x->x_obj.te_ypix,
         x->x_obj.te_xpix + 355,
         x->x_obj.te_ypix + 220,
         x
         );
   }else {
      // We use to delete the blue contour here
      sys_vgui(".x%x.c delete %lxSEL\n",glist_getcanvas(glist), x);
   }
}
// ---------------------------------------------------
// What to do when clicked
// ---------------------------------------------------
static int filter_circle_click(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit){
   (void)z;
   (void)glist;
   (void)xpix;
   (void)ypix;
   (void)shift;
   (void)alt;
   (void)dbl;
   (void)doit;
//post("Clicked xpix:%d ypix:%d shift:%d alt:%d dbl:%d doit:%d", xpix,ypix, shift, alt, dbl, doit);
return 0;
}
// ---------------------------------------------------
// What to do when deleted
// ---------------------------------------------------
static void filter_circle_delete(t_gobj *z, t_glist *glist){
   t_text *x = (t_text *)z;
   canvas_deletelinesfor(glist_getcanvas(glist), x);
   //post("Object deleted!");
   //Something else?
}
// ---------------------------------------------------
// What to do when saved
// ---------------------------------------------------
static void filter_circle_save(t_gobj *c, t_binbuf *b){
   t_filter_circle *x = (t_filter_circle *)c;

   binbuf_addv(b, "ssiisffff",
      gensym("#X"),
      gensym("obj"),
      (t_int)x->x_obj.te_xpix,
      (t_int)x->x_obj.te_ypix,
      gensym("filter_circle"),
      x->pole_radius,
      x->pole_angle,
      x->zero_radius,
      x->zero_angle
      );
   binbuf_addv(b, ";");
}
// ---------------------------------------------------
// The properties window
// ---------------------------------------------------
static void filter_circle_properties(t_gobj *c, t_glist *list){
   (void)c;
   (void)list;
}
//EOF GUI stuff ---------------------------------------
// ---------------------------------------------------
// Setup
// ---------------------------------------------------
void filter_circle_setup(void) {
   filter_circle_class = class_new(gensym("filter_circle"),
      (t_newmethod) filter_circle_new, // Constructor
      (t_method) filter_circle_destroy, // Destructor
      sizeof (t_filter_circle),
      CLASS_DEFAULT,
      A_DEFFLOAT,
      A_DEFFLOAT,
      A_DEFFLOAT,
      A_DEFFLOAT,
      0);//Must always ends with a zero

   class_addmethod(filter_circle_class, (t_method) filter_circle_zeros,
         gensym("zeros"),A_DEFFLOAT, A_DEFFLOAT,  0);
   class_addmethod(filter_circle_class, (t_method) filter_circle_poles,
         gensym("poles"),A_DEFFLOAT, A_DEFFLOAT,  0);
   class_addbang(filter_circle_class, filter_circle_bang_method);


//   GUI STUFF---------------------------
   sys_gui(" if { [catch {pd}] } {proc pd {args} {pdsend [join $args " "]}}\n");
   sys_gui("proc pi {args} [subst -novariable {\n\
            expr [expr {atan2(0,-1)}] $args\n\
            }]\n");
   sys_gui("proc decimal {args} {\n\
               return [expr double(round(1000 * $args)) / 1000]\n\
               }\n");
   filter_circle_widgetbehavior.w_getrectfn = filter_circle_getrect;
   filter_circle_widgetbehavior.w_visfn= filter_circle_vis;
   filter_circle_widgetbehavior.w_displacefn= filter_circle_displace;
   filter_circle_widgetbehavior.w_selectfn= filter_circle_select;
   filter_circle_widgetbehavior.w_activatefn = filter_circle_activate;
   filter_circle_widgetbehavior.w_deletefn = filter_circle_delete;
   filter_circle_widgetbehavior.w_clickfn = filter_circle_click;
   class_setpropertiesfn(filter_circle_class, filter_circle_properties);
   class_setsavefn(filter_circle_class, filter_circle_save);
   class_setwidget(filter_circle_class, &filter_circle_widgetbehavior);
}
// EOF---------------------------------------------------
