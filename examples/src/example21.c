#include "m_pd.h"
#include "g_canvas.h" // To gui

#include <stdio.h>
#include <string.h>
#include <math.h>


static t_class *example21_class;
t_widgetbehavior widgetbehavior; // THE GUI

int ar,j,i;

typedef struct _example21{
    t_object x_obj;

    t_outlet * start_outlet; //envia um bang quando começa a processar o arquivo
    t_outlet * end_outlet; //envia um bang quando termina de processar o arquivo

    t_float alfa; //armazena o parametro alfa (2o. inlet): fator de escala temporal
    t_float beta; //armazena o parametro beta (3o. inlet): fator de transposicao
    char * file_name; // nome do arquivo de entrada

    t_canvas * canvas;
} t_example21;

// Metodo para definir o nome do arquivo com retorno para a GUI
void example21_set_file_name(t_example21 *x, char * file_name){
    sys_vgui(".x%x.c.s%xtx delete 0 end \n", x->canvas, x);
    sys_vgui(".x%x.c.s%xtx insert end %s\n", x->canvas, x , file_name);
    x->file_name = file_name;
    // DO SOMETHING
}

void example21_alfa(t_example21 *x, t_floatarg f){
    if( f >= 2) f = 2;
    if( f <= 0.5) f = 0.5; 
    sys_vgui(".x%x.c.s%xsb1 set %f\n",x->canvas,x,f);
    x->alfa = f;
}

void example21_beta(t_example21 *x, t_floatarg f){
    if( f >= 2) f = 2;
    if( f <= 0.5) f = 0.5; 
    sys_vgui(".x%x.c.s%xsb2 set %f\n",x->canvas,x,f);
    x->beta = f;
}

// BANG!
void example21_bang(t_example21 *x) {
    post("Iniciando o processamento");
}


// THE BOUNDING RECTANGLE
static void my_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2){
	t_example21 *x = (t_example21 *)z;
 	*xp1 = x->x_obj.te_xpix;
 	*yp1 = x->x_obj.te_ypix;
 	*xp2 = x->x_obj.te_xpix + 300;
 	*yp2 = x->x_obj.te_ypix + 200;
}

// MAKE VISIBLE OR INVISIBLE
static void my_vis(t_gobj *z, t_glist *glist, int vis){
	t_example21 *x = (t_example21 *)z;
	x->canvas = glist_getcanvas(glist);

	if(vis){ // VISIBLE

	    char buf[256];
	    sprintf(buf,"example21%lx", (long unsigned int)x);
	    pd_bind(&x->x_obj.ob_pd, gensym(buf));
	    sys_vgui("proc slide_alfa {val} {\n pd [concat example21%x alfa $val \\;]\n}\n",x);
	    sys_vgui("proc slide_beta {val} {\n pd [concat example21%x beta $val \\;]\n}\n",x);
	    sys_vgui("proc botao_ok {} {\n set name [.x%x.c.s%xtx get]\n pd [concat example21%x btok $name \\;]\n}\n",x->canvas,x,x);
	    sys_vgui("proc botao_file_chooser {} {\n\
						   set filename [tk_getOpenFile]\n\
						  .x%x.c.s%xtx delete 0 end \n\
						  .x%x.c.s%xtx insert end $filename \n}\n",x->canvas,x,x->canvas,x);

        // janela principal
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xrr -fill #DCDCDC\n",
		x->canvas,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 300,
		x->x_obj.te_ypix + 200,
		x
		);
       // Titulo da janela
       sys_vgui(".x%x.c create text %d %d -text {example21~} -anchor w  -tags %xlb1\n",
                x->canvas,
		x->x_obj.te_xpix + 75,
		x->x_obj.te_ypix + 15,
		x);
	// LABEL: file name:
       sys_vgui(".x%x.c create text %d %d -text {file:} -anchor w  -tags %xlb2\n",
                x->canvas,
		x->x_obj.te_xpix + 5,
		x->x_obj.te_ypix + 40,
		x);
	// Entrada de texto para o nome do arquivo
	sys_vgui("entry .x%x.c.s%xtx -width 25 -bg white -textvariable \"teste\" \n", x->canvas,x);
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xtx -tags %xtx\n",
		x->canvas,
		x->x_obj.te_xpix + 40,
		x->x_obj.te_ypix + 30,
		x->canvas,
		x,
		x);
	// BOTAO FILE CHOOSER
	sys_vgui("button .x%x.c.s%xbfc -text {...} -command botao_file_chooser\n", x->canvas,x);
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xbfc -tags %xbfc\n",
		x->canvas,
		x->x_obj.te_xpix + 260,
		x->x_obj.te_ypix + 27,
		x->canvas,
		x,
		x);
	// LABEL: alfa
       sys_vgui(".x%x.c create text %d %d -text {alfa:} -anchor w  -tags %xlb3\n",
                x->canvas,
		x->x_obj.te_xpix + 5,
		x->x_obj.te_ypix + 80,
		x);
	// SLIDE 1 - ALPHA
	sys_vgui("scale .x%x.c.s%xsb1 -length 250 -resolution 0.01 -from 0.5 -to 2 -orient horizontal -command slide_alfa \n", x->canvas,x);
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xsb1 -tags %xsb1\n",
		x->canvas,
		x->x_obj.te_xpix + 40,
		x->x_obj.te_ypix + 60,
		x->canvas,
		x,
		x);
	// LABEL: beta
       sys_vgui(".x%x.c create text %d %d -text {beta:} -anchor w  -tags %xlb4\n",
                x->canvas,
		x->x_obj.te_xpix + 5,
		x->x_obj.te_ypix + 140,
		x);
	// SLIDE 2 - BETA
	sys_vgui("scale .x%x.c.s%xsb2 -length 250 -resolution 0.01 -from 0.5 -to 2 -orient horizontal -command slide_beta \n", x->canvas,x);
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xsb2 -tags %xsb2\n",
		x->canvas,
		x->x_obj.te_xpix + 40,
		x->x_obj.te_ypix + 120,
		x->canvas,
		x,
		x);
	// BOTAO OK
	sys_vgui("button .x%x.c.s%xbt -text {start} -command botao_ok\n", x->canvas,x);
	sys_vgui(".x%x.c create window %d %d -anchor nw -window .x%x.c.s%xbt -tags %xbt\n",
		x->canvas,
		x->x_obj.te_xpix + 127,
		x->x_obj.te_ypix + 163,
		x->canvas,
		x,
		x);
	// OUTLET ESQUERDO
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xrol -fill #999999\n",
		x->canvas,
		x->x_obj.te_xpix + 0,
		x->x_obj.te_ypix + 197,
		x->x_obj.te_xpix + 8,
		x->x_obj.te_ypix + 200,
		x
		);
	// OUTLET CENTRAL
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xroc -fill #FFFFFF\n",
		x->canvas,
		x->x_obj.te_xpix + 146,
		x->x_obj.te_ypix + 197,
		x->x_obj.te_xpix + 154,
		x->x_obj.te_ypix + 200,
		x
		);
	// OUTLET DIREITO
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xror -fill #FFFFFF\n",
		x->canvas,
		x->x_obj.te_xpix + 292,
		x->x_obj.te_ypix + 197,
		x->x_obj.te_xpix + 300,
		x->x_obj.te_ypix + 200,
		x
		);
	// INLET ESQUERDO
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xril -fill #FFFFFF\n",
		x->canvas,
		x->x_obj.te_xpix + 0,
		x->x_obj.te_ypix + 0,
		x->x_obj.te_xpix + 8,
		x->x_obj.te_ypix + 3,
		x
		);
	// INLET CENTRAL
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xric -fill #FFFFFF\n",
		x->canvas,
		x->x_obj.te_xpix + 146,
		x->x_obj.te_ypix + 0,
		x->x_obj.te_xpix + 154,
		x->x_obj.te_ypix + 3,
		x
		);
	// INLET DIREITO
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xrir -fill #FFFFFF\n",
		x->canvas,
		x->x_obj.te_xpix + 292,
		x->x_obj.te_ypix + 0,
		x->x_obj.te_xpix + 300,
		x->x_obj.te_ypix + 3,
		x
		);
	// Agora que todos foram criados, setos os valores guardados pelo construtor
	example21_set_file_name(x,x->file_name);
	example21_alfa(x,x->alfa);
	example21_beta(x,x->beta);
	}else{ // INVISIBLE
		sys_vgui(".x%x.c delete %xrr\n",  x->canvas, x);
		sys_vgui(".x%x.c delete %xlb1\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xlb2\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xlb3\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xlb4\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xtx\n",  x->canvas, x);
		sys_vgui(".x%x.c delete %xsb1\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xsb2\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xbt\n",  x->canvas, x);
		sys_vgui(".x%x.c delete %xbfc\n",  x->canvas, x);
		sys_vgui(".x%x.c delete %xrol\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xroc\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xror\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xril\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xric\n", x->canvas, x);
		sys_vgui(".x%x.c delete %xrir\n", x->canvas, x);
	}
}

// DISPLACE IT
void my_displace(t_gobj *z, t_glist *glist,int dx, int dy){
	t_example21 *x = (t_example21 *)z;
	x->x_obj.te_xpix += dx;
	x->x_obj.te_ypix += dy;

        sys_vgui(".x%lx.c coords %xSEL %d %d %d %d \n", //MOVE O SELECIONADO
		x->canvas,
		x,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 300,
		x->x_obj.te_ypix + 200
		);
        sys_vgui(".x%x.c coords %xrr %d %d %d %d\n",x->canvas,x, x->x_obj.te_xpix, x->x_obj.te_ypix, x->x_obj.te_xpix + 300, x->x_obj.te_ypix + 200);
        sys_vgui(".x%x.c coords %xrol %d %d %d %d\n",x->canvas,x, x->x_obj.te_xpix, x->x_obj.te_ypix + 197, x->x_obj.te_xpix + 8, x->x_obj.te_ypix + 200);
        sys_vgui(".x%x.c coords %xroc %d %d %d %d\n",x->canvas,x, x->x_obj.te_xpix + 146, x->x_obj.te_ypix + 197, x->x_obj.te_xpix + 154, x->x_obj.te_ypix + 200);
        sys_vgui(".x%x.c coords %xror %d %d %d %d\n",x->canvas,x, x->x_obj.te_xpix + 292, x->x_obj.te_ypix + 197, x->x_obj.te_xpix + 300, x->x_obj.te_ypix + 200);
        sys_vgui(".x%x.c coords %xril %d %d %d %d\n",x->canvas,x, x->x_obj.te_xpix, x->x_obj.te_ypix + 0, x->x_obj.te_xpix + 8, x->x_obj.te_ypix + 3);
        sys_vgui(".x%x.c coords %xric %d %d %d %d\n",x->canvas,x, x->x_obj.te_xpix + 146, x->x_obj.te_ypix + 0, x->x_obj.te_xpix + 154, x->x_obj.te_ypix + 3);
        sys_vgui(".x%x.c coords %xrir %d %d %d %d\n",x->canvas,x, x->x_obj.te_xpix + 292, x->x_obj.te_ypix + 0, x->x_obj.te_xpix + 300, x->x_obj.te_ypix + 3);

        sys_vgui(".x%x.c coords %xlb1 %d %d \n",x->canvas,x, x->x_obj.te_xpix + 75, x->x_obj.te_ypix + 15);
        sys_vgui(".x%x.c coords %xlb2 %d %d \n",x->canvas,x, x->x_obj.te_xpix + 05, x->x_obj.te_ypix + 40);
        sys_vgui(".x%x.c coords %xlb3 %d %d \n",x->canvas,x, x->x_obj.te_xpix + 05, x->x_obj.te_ypix + 80);
        sys_vgui(".x%x.c coords %xlb4 %d %d \n",x->canvas,x, x->x_obj.te_xpix + 05, x->x_obj.te_ypix + 120);
        sys_vgui(".x%x.c coords %xtx %d %d \n",x->canvas,x, x->x_obj.te_xpix + 40, x->x_obj.te_ypix + 30);
        sys_vgui(".x%x.c coords %xsb1 %d %d \n",x->canvas,x, x->x_obj.te_xpix + 40, x->x_obj.te_ypix + 60);
        sys_vgui(".x%x.c coords %xsb2 %d %d \n",x->canvas,x, x->x_obj.te_xpix + 40, x->x_obj.te_ypix + 120);
        sys_vgui(".x%x.c coords %xbt %d %d \n",x->canvas,x, x->x_obj.te_xpix + 127, x->x_obj.te_ypix + 163);
        sys_vgui(".x%x.c coords %xbfc %d %d \n",x->canvas,x, x->x_obj.te_xpix + 260, x->x_obj.te_ypix + 30);

	canvas_fixlinesfor(glist, (t_text *)x);
}

// WHAT TO DO IF SELECTED?
static void my_select(t_gobj *z, t_glist *glist, int state){
 	t_example21 *x = (t_example21 *)z;
 	if (state) {
        sys_vgui(".x%x.c create rectangle %d %d %d %d -tags %xSEL -outline blue\n",
		x->canvas,
		x->x_obj.te_xpix,
		x->x_obj.te_ypix,
		x->x_obj.te_xpix + 300,
		x->x_obj.te_ypix + 200,
		x
		);
	}else {
 	sys_vgui(".x%x.c delete %xSEL\n",x->canvas, x);
	}
}

static int my_click(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit){
	return (1); 
}

static void my_delete(t_gobj *z, t_glist *glist){
 	t_example21 *x = (t_example21 *)z;
	t_text *t = (t_text *)z;
	canvas_deletelinesfor(x->canvas, t);
} 

// Metodo associado ao botao ok
static void example21_btok(t_example21* x, t_symbol * file_name){
    x->file_name = file_name->s_name;
    example21_bang(x); 
}


void example21_start(t_example21 *x){
    example21_bang(x);
    post("START / BANG");
}

void example21_stop(t_example21 *x){
    outlet_bang(x->end_outlet);
    post("STOP");
}

void example21_open(t_example21 *x, t_symbol *s){
    example21_set_file_name(x, s->s_name);
    post("open %s",s->s_name);
}


void example21_destroy(t_example21 *x) {
   post("You say good bye and I say hello");
}


void *example21_new(t_symbol * file_name, t_floatarg alpha, t_floatarg beta) {

    t_example21 *x = (t_example21 *) pd_new(example21_class);

    x->start_outlet = outlet_new(&x->x_obj, gensym("bang"));
    x->end_outlet = outlet_new(&x->x_obj, gensym("bang"));

    inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("alfa"));
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("beta"));

    // armazeno os valores passados ao construtor para depois poder inicializar a GUI com eles
    x->file_name = file_name->s_name;
    x->alfa = alpha;
    x->beta = beta;

    return (void *) x;
}


void example21_setup(void) {
    example21_class = class_new(gensym("example21"),
            (t_newmethod) example21_new,
            (t_method) example21_destroy,
            sizeof (t_example21),
            CLASS_DEFAULT, //[example21~ arg1 arg2 arg3]
	    A_DEFSYMBOL,// arg1 - PRIMEIRO PARAMETRO PASSADO PELO OBJETO: nome do arquivo
	    A_DEFFLOAT,// arg2 - SEGUNDO PARAMETRO PASSADO PELO OBJETO: alfa
	    A_DEFFLOAT,// arg3 - TERCEIRO PARAMETRO PASSADO PELO OBJETO: beta
            0);
 
// Definimos uma metodo para cada "tipo" de mensagem. Como estas mensagens nao serao associadas a nenhum inlet, serão recebidas pelo 1
    class_addbang(example21_class, example21_bang);
    class_addmethod(example21_class, (t_method) example21_start,gensym("start"), 0);
    class_addmethod(example21_class, (t_method)example21_start, gensym("bang"),  0);
    class_addmethod(example21_class, (t_method)example21_stop,  gensym("stop"),  0);
    class_addmethod(example21_class, (t_method)example21_open,  gensym("open"),  A_DEFSYMBOL,0);

// depois associaremos estes "tipos" de mensagem aos inlets 2 e 3
    class_addmethod(example21_class, (t_method)example21_alfa,  gensym("alfa"), A_DEFFLOAT,0); 
    class_addmethod(example21_class, (t_method)example21_beta,  gensym("beta"), A_DEFFLOAT,0); 
// metodo do botao ok
    class_addmethod(example21_class, (t_method)example21_btok,gensym("btok"), A_DEFSYMBOL,0); 
// associa o objeto a sua gui
    class_setwidget(example21_class, &widgetbehavior);

// Comportamentos padroes da GUI - estes metodos estao definidos no example21~-gui.c
    widgetbehavior.w_getrectfn = my_getrect;
    widgetbehavior.w_visfn= my_vis;
    widgetbehavior.w_displacefn= my_displace;
    widgetbehavior.w_selectfn= my_select,
    widgetbehavior.w_activatefn = NULL;
    widgetbehavior.w_deletefn = my_delete;
    widgetbehavior.w_clickfn = my_click;
}
