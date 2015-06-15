#! /usr/local/bin/wish8.5
button .b -text 0 -command {.b config -text [expr {[.b cget -text]+1}]}
pack   .b ;#RS
