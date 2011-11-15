# http://www2.tcl.tk/1155
 set t .demo
 destroy $t
 toplevel $t

 set _paint(top) $t
 set _paint(width) 800
 set _paint(height) 600

 set _paint(bg) white
 set _paint(color) black

 # Canvas

 set _paint(can) [canvas $t.c \
    -width $_paint(width) \
    -height $_paint(height) \
    -background $_paint(bg) \
    ]

 grid $_paint(can) -row 0 -column 0

 # Image

 set _paint(image) [image create photo \
    -width $_paint(width) \
    -height $_paint(height) \
    -palette 256/256/256 \
    ]

 # Canvas image item

 set _paint(image_id) [$_paint(can) create image \
    0 0 \
    -anchor nw \
    -image $_paint(image) \
    ]

 # Paint pixel at a X,Y coord

 proc Paint {x y} {
    global _paint

    if {$x >= 0 && $y >= 0} {
        $_paint(image) put $_paint(color) \
            -to $x $y \
                [expr {$x + 1}] [expr {$y + 1}]
    }
 }

 bind $_paint(can) <1> {Paint %x %y}
 bind $_paint(can) <B1-Motion> {Paint %x %y}

 # Button 3 will select a new paint color

 proc ChangeColor {} {
    global _paint
    set _paint(color) [tk_chooseColor]
    raise $_paint(top)
 }

 bind $_paint(can) <3> {ChangeColor}
