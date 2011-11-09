#!/usr/bin/wish

# ZetCode Tcl/Tk tutorial
#
# In this script, we show how to
# use the listbox widget.
#
# author: Jan Bodnar
# last modified: March 2011
# website: www.zetcode.com


frame .fr
pack .fr -fill both -expand 1

listbox .fr.lb 
.fr.lb insert end "Scarlett Johansson" "Rachel Weiss" "Natalie Portman" \
    "Jessica Alba" 

bind .fr.lb <<ListboxSelect>> { setLabel [%W curselection]}

place .fr.lb -x 20 -y 20 

label .fr.lbl 
place .fr.lbl -x 20 -y 210

wm title . listbox
wm geometry . 300x250+300+300

proc setLabel { idx } {

    set val [.fr.lb get $idx]
    .fr.lbl configure -text $val

}

