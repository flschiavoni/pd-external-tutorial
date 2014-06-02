// PD external API
#include "m_pd.h"
// PG GUI external API
#include "g_canvas.h"

static t_class *example15_class;
t_widgetbehavior widgetbehavior; // This represents the external GUI

typedef struct _example15 {
    t_object x_obj;
    t_float x_f;          /* place to hold inlet's value if it's set by message */
} t_example15;


// Constructor of the class
void * example15_new(t_symbol *s, int argc, t_atom * argv) {
    t_example15 *x = (t_example15 *) pd_new(example15_class);

    return (void *) x;
}

// Destroy the class
void example15_destroy(t_example15 *x) {
   post("You say good bye and I say hello");
}

/* -------------------------------------------------------------------------------------------------------------------------------------------
	GUI!
   -------------------------------------------------------------------------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------------------------------------------------------------------------
	GUI!
   -------------------------------------------------------------------------------------------------------------------------------------------*/
// THE BOUNDING RECTANGLE
static void my_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2){
	t_example15 *x = (t_example15 *)z;
 	*xp1 = x->x_obj.te_xpix;
 	*yp1 = x->x_obj.te_ypix;
 	*xp2 = x->x_obj.te_xpix + 30;
 	*yp2 = x->x_obj.te_ypix + 50;
}

// MAKE VISIBLE OR INVISIBLE
static void my_vis(t_gobj *z, t_glist *glist, int vis){
	t_example15 *x = (t_example15 *)z;
	t_canvas * canvas = glist_getcanvas(glist);

	if(vis){ // VISIBLE
	// Define the tk/tcl commands / functions
	sys_vgui("proc do_something {} {\n set name [.x%x.c.s%xtx get]\n puts \"OIA: $name\" \n}\n",canvas,x);
	sys_vgui("proc do_otherthing {val} {\n set name [.x%x.c.s%xtx get]\n puts \"OIA: $name\" \n}\n",canvas,x);
    	// The text field
	sys_vgui("entry .x%x.c.s%xtx -width 12 -bg yellow \n", canvas,x);
	// The button
	sys_vgui("button .x%x.c.s%xbb -text {click} -command do_something\n", canvas,x);
	// The radio button	
	sys_vgui("radiobutton .x%x.c.s%xrb -value 1 -command do_something\n", canvas,x);
	// The h slider
	sys_vgui("scale .x%x.c.s%xsb -orient horizontal -command do_otherthing \n", canvas,x);
	// A checkbutton
	sys_vgui("checkbutton .x%x.c.s%xcb -foreground blue -background yellow -command do_something\n", canvas,x);
	// The red rectangle
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xrr -fill #FF0000\n",
		glist_getcanvas(glist),
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 170,
		x->x_obj.te_ypix + 150,
		x
		);
	// A window to the button (bb)
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xbb -tags %xbb\n",
		canvas,
		x->x_obj.te_xpix + 70,
		x->x_obj.te_ypix + 120,
		canvas,
		x,
		x);
	// A window to the radiobutton
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xrb -tags %xrb\n",
		canvas,
		x->x_obj.te_xpix + 70,
		x->x_obj.te_ypix,
		canvas,
		x,
		x);
	// A window to the combo box 
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xcb -tags %xcb\n",
		canvas,
		x->x_obj.te_xpix  + 100,
		x->x_obj.te_ypix,
		canvas,
		x,
		x);
	// A window to the slider button
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xsb -tags %xsb\n",
		canvas,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix + 80,
		canvas,
		x,
		x);
	// A window to the text
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xtx -tags %xtx\n",
		canvas,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix + 60,
		canvas,
		x,
		x);
	// a label field
       sys_vgui(".x%x.c create text %d %d -text {example15~} -anchor w  -tags %xlb\n",
                canvas,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix + 40,
		x);

	}else{ // INVISIBLE
		sys_vgui(".x%x.c delete %xbb\n",canvas, x);
		sys_vgui(".x%x.c delete %xcb\n",canvas, x);
		sys_vgui(".x%x.c delete %xrb\n",canvas, x);
		sys_vgui(".x%x.c delete %xsb\n",canvas, x);
		sys_vgui(".x%x.c delete %xrr\n",canvas, x);
		sys_vgui(".x%x.c delete %xlb\n",canvas, x);
		sys_vgui(".x%x.c delete %xtx\n",canvas, x);
	}
}

// DISPLACE IT
void my_displace(t_gobj *z, t_glist *glist,int dx, int dy){
	t_canvas * canvas = glist_getcanvas(glist);
	t_example15 *x = (t_example15 *)z;
	x->x_obj.te_xpix += dx;
	x->x_obj.te_ypix += dy;

        sys_vgui(".x%lx.c coords %xSEL %d %d %d %d \n", //MOVE O SELECIONADO
		glist_getcanvas(glist),
		x,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 170,
		x->x_obj.te_ypix + 150
		);
        sys_vgui(".x%x.c coords %xrr %d %d %d %d\n",canvas,x,x->x_obj.te_xpix,x->x_obj.te_ypix,x->x_obj.te_xpix + 170,x->x_obj.te_ypix + 150);
        sys_vgui(".x%x.c coords %xbb %d %d \n",canvas,x,x->x_obj.te_xpix,x->x_obj.te_ypix);
        sys_vgui(".x%x.c coords %xcb %d %d \n",canvas,x,x->x_obj.te_xpix + 30,x->x_obj.te_ypix);
        sys_vgui(".x%x.c coords %xsb %d %d \n",canvas,x,x->x_obj.te_xpix,x->x_obj.te_ypix + 80);
        sys_vgui(".x%x.c coords %xtx %d %d \n",canvas,x,x->x_obj.te_xpix,x->x_obj.te_ypix + 120);
        sys_vgui(".x%x.c coords %xrb %d %d \n",canvas,x,x->x_obj.te_xpix + 60,x->x_obj.te_ypix);
        sys_vgui(".x%x.c coords %xlb %d %d \n",canvas,x,x->x_obj.te_xpix,x->x_obj.te_ypix + 40);

	canvas_fixlinesfor(glist, (t_text *)x);
}

// WHAT TO DO IF SELECTED?
static void my_select(t_gobj *z, t_glist *glist, int state){
 	t_example15 *x = (t_example15 *)z;
 	if (state) {
        sys_vgui(".x%x.c create rectangle %d %d %d %d -tags %xSEL -outline blue\n",
		glist_getcanvas(glist),
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 170,
		x->x_obj.te_ypix + 150,
		x
		);
	}else {
 	sys_vgui(".x%x.c delete %xSEL\n",glist_getcanvas(glist), x);
	}
}

static int my_click(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit){
	return (1); 
}

static void my_delete(t_gobj *z, t_glist *glist){
	t_text *x = (t_text *)z;
	canvas_deletelinesfor(glist_getcanvas(glist), x);
} 

void example15_setup(void) {
    example15_class = class_new(gensym("example15"),
            (t_newmethod) example15_new, // Constructor
            (t_method) example15_destroy, // Destructor
            sizeof (t_example15),
	    CLASS_DEFAULT,
	    A_GIMME, // Allows various parameters
            0); // LAST argument is ALWAYS zero

    widgetbehavior.w_getrectfn = my_getrect; // The external GUI rectangle definition
    widgetbehavior.w_visfn= my_vis; //How to make ir visible / invisible
    widgetbehavior.w_displacefn= my_displace; //what to do whe moved
    widgetbehavior.w_selectfn= my_select, // What to do when selected
    widgetbehavior.w_activatefn = NULL; // What to do when active
    widgetbehavior.w_deletefn = my_delete; // What to do when deleted
    widgetbehavior.w_clickfn = my_click; // What to do when clicked

    class_setwidget(example15_class, &widgetbehavior);
}

