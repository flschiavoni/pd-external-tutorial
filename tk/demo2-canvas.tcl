#!/bin/sh
# Restart with tcl: -*- mode: tcl; tab-width: 4; -*- \
exec wish $0 ${1+"$@"}

# demo2-canvas.tcl - HaJo Gurt - 2005-12-13 - http://wiki.tcl.tk/15073
#: CanvasDemo: On button-click, draw something on the canvas

package require Tk

proc ClrCanvas {w} {
    $w delete "all"
}

proc DrawAxis {w} {
    set midX [expr { $::maxX / 2 }]
    set midY [expr { $::maxY / 2 }]
    $w create line 0     $midY  $::maxX   $midY  -tags "axis"
    $w create line $midX 0        $midX $::maxY  -tags "axis"
}

proc PaintText {w Txt} {
    global y
    incr y 10
    $w create text 20 $y -text $Txt -tags "text"
}

proc DrawBox {w} {
    global x1 y1 x2 y2 
    $w create rect  50  10  100  60  -tags "box"
    $w create rect $x1 $y1  $x2 $y2  -tags "box"
    incr x1 15
    incr x2 15
    incr y1 10
    incr y2 10
}

proc DrawFn1 {w} {
    $w create line 0 100  50 200  100 50  150 70  200 155  250 50  300 111  350 222\
             -tags "Fn1"  -smooth bezier
}

proc DrawFn2 {w} {
    set offY 0    ;# [expr { $::maxY / 2 }]

    for { set x 0 } { $x <= $::maxX } { incr x 5 } {
      set y [expr { rand() * $::maxY + $offY }]

     #puts "$x $y"
      if {$x>0} { $w create line $x0 $y0 $x $y -tags "Fn2" }
      set x0 $x
      set y0 $y
    }
}

#: Main :
frame .f1
frame .f2
pack  .f1 .f2

set maxX 320
set maxY 240
set y      0

set x1 120
set x2 150
set y1  50
set y2  80

canvas  .cv -width $maxX -height $maxY  -bg white
pack    .cv -in .f1

button  .b0 -text "Clear" -command { ClrCanvas .cv }
button  .b1 -text "Text"  -command { PaintText .cv "Canvas" }
button  .b2 -text "Axis"  -command { DrawAxis  .cv }
button  .b3 -text "Box"   -command { DrawBox   .cv }
button  .b4 -text "Fn1"   -command { DrawFn1   .cv }
button  .b5 -text "Fn2"   -command { DrawFn2   .cv }
pack .b0 .b1 .b2 .b3 .b4 .b5  -in .f2  -side left -padx 2

#catch {console show}
