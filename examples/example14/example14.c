// PD external API
#include "m_pd.h"
// PG GUI external API
#include "g_canvas.h"

static t_class *example14_class;
t_widgetbehavior widgetbehavior; // This represents the external GUI

typedef struct _example14 {
    t_object x_obj;
    t_float x_f;          /* place to hold inlet's value if it's set by message */
} t_example14;


// Constructos of the class
void * example14_new(t_symbol *s, int argc, t_atom * argv) {
    t_example14 *x = (t_example14 *) pd_new(example14_class);

    return (void *) x;
}

// Destroy the class
void example14_destroy(t_example14 *x) {
   post("You say good bye and I say hello");
}

/* -------------------------------------------------------------------------------------------------------------------------------------------
	GUI!
   -------------------------------------------------------------------------------------------------------------------------------------------*/
// THE BOUNDING RECTANGLE
static void my_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2){
	t_example14 *x = (t_example14 *)z;
 	*xp1 = x->x_obj.te_xpix;
 	*yp1 = x->x_obj.te_ypix;
 	*xp2 = x->x_obj.te_xpix + 30;
 	*yp2 = x->x_obj.te_ypix + 50;
}

// MAKE VISIBLE OR INVISIBLE
static void my_vis(t_gobj *z, t_glist *glist, int vis){
	t_example14 *x = (t_example14 *)z;

	// takes the Canvas to draw a GUI
	t_canvas * canvas = glist_getcanvas(glist);

	if(vis){ // VISIBLE
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xrr -fill #FF0000\n",
		glist_getcanvas(glist),
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 70,
		x->x_obj.te_ypix + 50,
		x
		);

	}else{ // INVISIBLE
		sys_vgui(".x%x.c delete %xrr\n",canvas, x);
	}
//	canvas_fixlinesfor(glist, (t_text *)x);
}

// DISPLACE IT
void my_displace(t_gobj *z, t_glist *glist,int dx, int dy){
	t_canvas * canvas = glist_getcanvas(glist);
	t_example14 *x = (t_example14 *)z;
	x->x_obj.te_xpix += dx; // x movement
	x->x_obj.te_ypix += dy; // y movement

        sys_vgui(".x%lx.c coords %xSEL %d %d %d %d \n", //MOVE O SELECIONADO
		canvas,
		x,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 70,
		x->x_obj.te_ypix + 50
		);
        sys_vgui(".x%x.c coords %xrr %d %d %d %d\n",canvas,x,x->x_obj.te_xpix,x->x_obj.te_ypix,x->x_obj.te_xpix + 70,x->x_obj.te_ypix + 50);

	canvas_fixlinesfor(glist, (t_text *)x);
}

// What to do if activated?
static void my_activate(t_gobj *x, struct _glist *glist, int state){
	post("Activated");
}

// WHAT TO DO IF SELECTED?
static void my_select(t_gobj *z, t_glist *glist, int state){
 	t_example14 *x = (t_example14 *)z;
 	if (state) {
        sys_vgui(".x%x.c create rectangle %d %d %d %d -tags %xSEL -outline blue\n",
		glist_getcanvas(glist),
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 70,
		x->x_obj.te_ypix + 50,
		x
		);
	}else {
 	sys_vgui(".x%x.c delete %xSEL\n",glist_getcanvas(glist), x);
	}
}

static int my_click(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit){
	post("Clicked xpix:%d ypix:%d shift:%d alt:%d dbl:%d doit:%d", xpix,ypix, shift, alt, dbl, doit);
	return (1);
}

static void my_delete(t_gobj *z, t_glist *glist){
	t_text *x = (t_text *)z;
	canvas_deletelinesfor(glist_getcanvas(glist), x);
	post("Object deleted!");
} 

void example14_setup(void) {
    example14_class = class_new(gensym("example14"),
            (t_newmethod) example14_new, // Constructor
            (t_method) example14_destroy, // Destructor
            sizeof (t_example14),
	    CLASS_DEFAULT,
	    A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero

    widgetbehavior.w_getrectfn = my_getrect; // The external GUI rectangle definition
    widgetbehavior.w_visfn= my_vis; //How to make ir visible / invisible
    widgetbehavior.w_displacefn= my_displace; //what to do whe moved
    widgetbehavior.w_selectfn= my_select, // What to do when selected
    widgetbehavior.w_activatefn = my_activate; // What to do when active
    widgetbehavior.w_deletefn = my_delete; // What to do when deleted
    widgetbehavior.w_clickfn = my_click; // What to do when clicked

    class_setwidget(example14_class, &widgetbehavior);

}

