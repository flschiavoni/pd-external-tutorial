 #!/bin/sh
 # -*- mode: tcl; tab-width: 4; coding: iso-8859-1 -*-
 # Restart with tcl:  \
 exec wish $0 ${1+"$@"}

 # neuro1.tcl - HaJo Gurt - 2006-10-17 - http://wiki.tcl.tk/17067
 #: Widgets on a canvas : Sliders + Entryfields
 # Simple Schema of a neuron, summing its input-signals,
 # and firing when the sum exceeds a threshold.

  package require Tk

  array set S { x1 20  w1 1   x2 50  w2  8 \
                t1 500 title "Neuronal Processing" \
                s1 0   s2 0  sum 0  out 0 }

  proc int x { expr int($x) }

  proc Calc x {
  #: Calculate results + update display
    global S

    set S(s1)  [expr {$S(x1) * $S(w1)} ]
    set S(s2)  [expr {$S(x2) * $S(w2)} ]
    set S(sum) [expr {$S(s1) + $S(s2)} ]
    set S(out) [expr {$S(sum) >= $S(t1)} ]
    if { $S(out) } {
      .c itemconfig out -fill red
    } else {
      .c itemconfig out -fill cyan
    }
  }

  proc Init {} {
  #: Build GUI
    global S

    wm title . "Neuro1"
    canvas .c -relief raised  -borderwidth 0  -height 400  -width 560  -bg white
    pack   .c

    option add *Scale.highlightThickness 0
    option add *Scale.orient vertical
    option add *Scale.relief ridge
    option add *Entry.relief sunken

    scale .c.sx1 -from 100 -to    0 -variable S(x1) -command Calc -label "x1"  
    scale .c.sx2 -from 100 -to    0 -variable S(x2) -command Calc -label "x2"  
    scale .c.sw1 -from  10 -to    0 -variable S(w1) -command Calc -label "w1"  
    scale .c.sw2 -from  10 -to    0 -variable S(w2) -command Calc -label "w2"  
    scale .c.st1 -from   0 -to 2000 -variable S(t1) -command Calc -label "Threshold" -orient horizontal 

    entry .c.es1 -width 5 -textvar S(s1)  -state readonly
    entry .c.es2 -width 5 -textvar S(s2)  -state readonly
   #entry .c.es3 -width 5 -textvar S(sum) -state readonly  ;##
    scale .c.ss3 -from 2000 -to   0 -variable S(sum) -length 200 -sliderlength 5 -state disabled -bg green2
    entry .c.es4 -width 3 -textvar S(out) -state readonly

    .c create text   280  20          -text $S(title) -font {Times 24 bold}

    .c create text    12  80          -text "Input 1"   -anchor w
    .c create line    30 100  310 100 -width 5 -arrow last
    .c create window  50  50          -window .c.sx1    -anchor nw
    .c create window  50 200          -window .c.sx2    -anchor nw
    .c create window 240  75          -window .c.es1    -anchor w

    .c create text    12 230          -text "Input 2"   -anchor w
    .c create line    30 250  310 250 -width 5 -arrow last
    .c create window 150  50          -window .c.sw1    -anchor nw
    .c create window 150 200          -window .c.sw2    -anchor nw
    .c create window 240 225          -window .c.es2    -anchor w

    .c create text   160 315          -text "Weight"    -anchor w

    .c create window 275 320          -window .c.st1    -anchor nw
    .c create line   350 320  350 300 -width 1 -arrow last

    .c create oval   300  50  400 300 -width 3 -fill green2
    .c create text   350  65          -text "Sum"
    .c create window 350 175          -window .c.ss3  ;## .c.es3 / .c.ss3
    .c create line   400 175  450 175 -width 5 -arrow last

    .c create oval   450 125  530 225 -width 3 -tag out
    .c create text   490 150          -text "Output"
    .c create window 490 175          -window .c.es4

    # Debug: show cursor-position :
   #bind .c <Motion>  {wm title . [int [%W canvasx %x]],[int [%W canvasy %y]]}
  }

  Init
  return
