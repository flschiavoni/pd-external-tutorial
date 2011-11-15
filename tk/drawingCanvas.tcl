# http://www2.tcl.tk/3179

  package require Tk
  proc polydraw {w} {
    #-- add bindings for drawing/editing polygons to a canvas
    bind $w <Button-1>        {polydraw'mark   %W %x %y}
    bind $w <Double-1>        {polydraw'insert %W}
    bind $w <B1-Motion>       {polydraw'move   %W %x %y}
    bind $w <Shift-B1-Motion> {polydraw'move   %W %x %y 1}
    bind $w <Button-2>        {polydraw'rotate %W  0.1}
    bind $w <Shift-2>         {polydraw'rotate %W -0.1}
    bind $w <Button-3>        {polydraw'delete %W}
    bind $w <Shift-3>         {polydraw'delete %W 1}
    interp alias {} tags$w {} $w itemcget current -tags
  }
  proc polydraw'add {w x y} {
    #-- start or extend a line, turn it into a polygon if closed
    global polydraw
    if {![info exists polydraw(item$w)]} {
        set coords [list [expr {$x-1}] [expr {$y-1}] $x $y]
        set polydraw(item$w) [$w create line $coords -fill red -tag poly0]
    } else {
        set item $polydraw(item$w)
        foreach {x0 y0} [$w coords $item] break
        if {hypot($x-$x0,$y-$y0) < 5} {
            set coo [lrange [$w coords $item] 2 end]
            $w delete $item
            unset polydraw(item$w)
            set new [$w create poly $coo -fill {} -tag poly -outline black]
            polydraw'markNodes $w $new
        } else {
            $w coords $item [concat [$w coords $item] $x $y]
        }
    }
  }
  proc polydraw'delete {w {all 0}} {
    #-- delete a node of, or a whole polygon
    set tags [tags$w]
    if {[regexp {of:([^ ]+)} $tags -> poly]} {
        if {$all} {
            $w delete $poly of:$poly
        } else {
            regexp {at:([^ ]+)} $tags -> pos
            $w coords $poly [lreplace [$w coords $poly] $pos [incr pos]]
            polydraw'markNodes $w $poly
        }
    }
    $w delete poly0 ;# possibly clean up unfinished polygon
    catch {unset ::polydraw(item$w)}
  }
  proc polydraw'insert {w} {
    #-- create a new node halfway to the previous node
    set tags [tags$w]
    if {[has $tags node]} {
        regexp {of:([^ ]+)} $tags -> poly
        regexp {at:([^ ]+)} $tags -> pos
        set coords [$w coords $poly]
        set pos2 [expr {$pos==0? [llength $coords]-2 : $pos-2}]
        foreach {x0 y0} [lrange $coords $pos end] break
        foreach {x1 y1} [lrange $coords $pos2 end] break
        set x [expr {($x0 + $x1) / 2}]
        set y [expr {($y0 + $y1) / 2}]
        $w coords $poly [linsert $coords $pos $x $y]
        polydraw'markNodes $w $poly
    }
  }
  proc polydraw'mark {w x y} {
    #-- extend a line, or prepare a node for moving
    set x [$w canvasx $x]; set y [$w canvasy $y]
    catch {unset ::polydraw(current$w)}
    if {[has [tags$w] node]} {
        set ::polydraw(current$w) [$w find withtag current]
        set ::polydraw(x$w)       $x
        set ::polydraw(y$w)       $y
    } else {
        polydraw'add $w $x $y
    }
  }
  proc polydraw'markNodes {w item} {
    #-- decorate a polygon with square marks at its nodes
    $w delete of:$item
    set pos 0
    foreach {x y} [$w coords $item] {
        set coo [list [expr $x-2] [expr $y-2] [expr $x+2] [expr $y+2]]
        $w create rect $coo -fill blue -tag "node of:$item at:$pos"
        incr pos 2
    }
  }
  proc polydraw'move {w x y {all 0}} {
    #-- move a node of, or a whole polygon
    set x [$w canvasx $x]; set y [$w canvasy $y]
    if {[info exists ::polydraw(current$w)]} {
        set dx [expr {$x - $::polydraw(x$w)}]
        set dy [expr {$y - $::polydraw(y$w)}]
        set ::polydraw(x$w) $x
        set ::polydraw(y$w) $y
        if {!$all} {
            polydraw'redraw $w $dx $dy
            $w move $::polydraw(current$w) $dx $dy
        } elseif [regexp {of:([^ ]+)} [tags$w] -> poly] {
            $w move $poly    $dx $dy
            $w move of:$poly $dx $dy
        }
    }
  }
  proc polydraw'redraw {w dx dy} {
    #-- update a polygon when one node was moved
    set tags [tags$w]
    if [regexp {of:([^ ]+)} $tags -> poly] {
        regexp {at:([^ ]+)} $tags -> from
        set coords [$w coords $poly]
        set to [expr {$from + 1}]
        set x [expr {[lindex $coords $from] + $dx}]
        set y [expr {[lindex $coords $to]   + $dy}]
        $w coords $poly [lreplace $coords $from $to $x $y]
    }
  }
  proc polydraw'rotate {w angle} {
    if [regexp {of:([^ ]+)} [tags$w] -> item] {
        canvas'rotate      $w $item $angle
        polydraw'markNodes $w $item
    }
  }
  #--------------------------------------- more general routines
  proc canvas'center {w item} {
    foreach {x0 y0 x1 y1} [$w bbox $item] break
    list [expr {($x0 + $x1) / 2.}] [expr {($y0 + $y1) / 2.}]
  }
  proc canvas'rotate {w item angle} {
    # This little code took me hours... but the Welch book saved me!
    foreach {xm ym} [canvas'center $w $item] break
    set coords {}
    foreach {x y} [$w coords $item] {
        set rad [expr {hypot($x-$xm, $y-$ym)}]
        set th  [expr {atan2($y-$ym, $x-$xm)}]
        lappend coords [expr {$xm + $rad * cos($th - $angle)}]
        lappend coords [expr {$ym + $rad * sin($th - $angle)}]
    }
    $w coords $item $coords
  }
  proc has {list element} {expr {[lsearch $list $element]>=0}}

if 0 {

 #------------------------------------------------ demo and test code...

  if {[file tail [info script]]==[file tail $argv0]} {
    pack [canvas .c] [canvas .d -bg white] -fill both -expand 1
    polydraw .c; polydraw .d             ;# test: are they independent?
    bind . <Escape> {exec wish $argv0 &; exit}         ;# quick restart
    bind . ? {console show}          ;# little (? BIG) debugging helper
  }

}

if 1 {

 #------------------------------------------------ Application2 - Outlining:

  proc help {w} {
  #: Show usage info
    set msg "Help:\n"
    append msg "Left-click : Create point. To close polygon, click on first point.\n"
    append msg "Drag blue marks to edit polygon.\n"
    append msg "Double-click on mark: insert new mark in adjacent line.\n"
    append msg "Shift / Right-click : Delete mark/line/polygon\n"
    append msg "Shift / Middle-click on mark: Rotate polygon\n"
    append msg "F1: Show console\n"
    append msg "F3: Load Picture      \t F4: Delete Picture\n"
    append msg "F5: Show User-polygon \t F6: Delete User-polygon\n"
    $w insert end "$msg\n"
  }

  proc ReadPic {w fn} {
  #: Read imagefile, put image on canvas
    if { $fn == "" } {
        set fn [tk_getOpenFile  -filetypes {{{GIF Files} {*.gif}} {{All Files} {*.*}}}]
        if { $fn == "" } {return}
    }
    set width  [winfo reqwidth  $w]
    set height [winfo reqheight $w]
    set x [expr { $width  / 2 }]
    set y [expr { $height / 2 }]
    catch {image delete $img1}
    set img1 [image create photo -file $fn]
    $w create image $x $y -image $img1 -tag "img"
  }

  proc ShowPoly {w} {
  #: !! Paste user-made polygon here: !!
    $w create poly \
      117.0 206.0 117.0 60.0 264.0 60.0 264.0 206.0 \
     -fill {} -tag user -outline blue
  }

  #: Main :
  pack [canvas .c -width 320 -height 320 -bg white] -fill both -expand 1
  pack [text   .t -width  50 -height   9]
  polydraw .c
  help     .t

  bind .  <F3> { ReadPic .c "" }
  bind .  <F4> { .c delete img }
  bind .  <F5> { ShowPoly .c }
  bind .  <F6> { .c delete user }

  bind .  <Escape> {exec wish $argv0 &; exit}  ;# quick restart
  bind .  <F1>     {console show}              ;# debugging helper
  puts "Try:"
  puts "puts \[.c find withtag poly]"
  puts "puts \[.c coords \[.c find withtag poly] ]"
  puts "foreach p \[.c find withtag poly] \{puts \"\$p: \[.c coords \$p ]\\n\"\}"

  proc int x  { expr int($x) }
  bind .c <Motion> {wm title . [int [%W canvasx %x]],[int [%W canvasy %y]]}

 #ReadPic  .c "mypic.gif"
 #ShowPoly .c
  focus -force .

}
