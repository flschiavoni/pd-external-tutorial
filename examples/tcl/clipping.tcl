 # clipping.tcl --
 #    Add a "clip window" to a canvas
 #

 # clipwindow --
 #    Add a rectangular clip window to a canvas
 #
 # Arguments:
 #    cnv       Canvas widget
 #    xmin      Minimum x value (in pixels!)
 #    ymin      Minimum y value (in pixels!)
 #    xmax      Maximum x value (in pixels!)
 #    ymax      Maximum y value (in pixels!)
 # Result:
 #    ID of the created polygon
 # Side effects:
 #    An opaque polygon is added to the canvas that has a
 #    hole in it. The polygon has the same colour as the
 #    canvas's background and the tag "CLIP".
 #
 proc clipwindow { cnv xmin ymin xmax ymax } {
 
    set width  [$cnv cget -width]
    set height [$cnv cget -height]
    set colour [$cnv cget -background]

    # Take care of border cases
    set xmin [expr {$xmin>0? $xmin : 0}]
    set ymin [expr {$ymin>0? $ymin : 0}]
    set xmax [expr {$xmax<$width?  $xmax : $width}]
    set ymax [expr {$ymax<$height? $ymax : $height}]

    set id [$cnv create polygon \
       0 0 \
       $width 0 $width $height 0 $height \
       0 0 \
       $xmin $ymin $xmin $ymax $xmax $ymax $xmax $ymin $xmin $ymin \
       0 0 \
       -tags CLIP -fill $colour -outline $colour]

    return $id
 } 

 #
 # Test code
 #
 canvas .c -width 200 -height 200
 pack   .c -fill both
 .c create oval  50  50 150 150 -fill green -outline black -width 3

 clipwindow .c 100 100 190 190

 .c create oval  50  50 150 150 -outline black -width 1
