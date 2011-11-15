# http://www2.tcl.tk/11354

pack [canvas .c -bg darkgreen -borderwidth 0 -highlightthickness 0] -expand 1 -fill both
 namespace eval ::img {}
  image create photo ::img::ah -format gif -data {
       R0lGODlhRwBgAKEAAH//1AAAAP////8AACH5BAEAAAAALAAAAABHAGAAAAL/BIKpy+0PYzBH2I
       uz3rz7L0wBSJamiZzquqbawMZyOL7zfbrYwOP+p7vwYL+iJijo9YxMWkZJbBaDy2RUiqMOh9if
       bgvuZmvW51XMcm2FXHRM3bZW3SokfUq+G+36MRsW15dTs7YmOGgBZnhYAqd4xujhqBjZSPZYab
       mzmAmUJ9ep+RQqStryaVqaioK66umKCKsqK9lKe2R7i8Gnu5vb6wTMwStMLLPI6WdESen1u4KJ
       6WMM/Sit/GN9fUOtot2M7fMdNv1cPY7HND7HbX5uvef+Tp4ute3cRR8vFrjP39XtVkBaA2UVhH
       XQVcJVC1M1NPWQVMRQEztVzHTxDqSMYm76ceTH6SOWayKbaLNQUh28YLROspRVqE1KlYCqzLxz
       k05ONztnIJMp79DPJT19nrEZVOjKl7C2FTXKxlcvKBmeQmVn1ejGpJH6MW25IavPsFwZlnVYQV
       hVChLaun3b1kABADs=}
  image create photo ::img::as -format gif -data {
       R0lGODlhRwBgAKEAAH//1AAAAP///////yH5BAEAAAAALAAAAABHAGAAAAL/BIKpy+0PYzBH2I
       uz3rz7L0wBSJamiZzquqbZyMZyCGP1jJfuleQ+uLP0fsRNMBUsFo+jpPK3i96ePumCuoQ9sFDt
       1MllIYc0cPg0tk7PKjO7un535VRnnI7+uvHA25XfUtMA2OY1SKhjyICYKOSQcwfH00QDuTeTRI
       apUKcXibKodBnDyZn1VFr2GSja46qJM5qXRjvXRfsq23fblNur6wEc7BuiarxpWUtsSrrap9xr
       zMwqU/paDC1s49xhPVZW6c2toT2ZDb4MS1Iu7Ut5JV4YiPuLq1oLOn+fi02fllfoHzx099Cp6z
       bOXMFvDKPBA6bNnTSC4n7lA1XPkUCD3y68NcLI0d5DfgeNJOTYLkJKcOtOkhQJ02JJci7xLcRW
       UKPFlrP2jQw5aOaLmvUWbYHAchfGou6MBhW6LaBORSGnary41FPHrbD+8AyI9OrUR1hnkc3pc9
       pXMaHMZWoLsJNXIuxazrXV6hDdk4m27GVkCXAsvoKHFrZr+DAQmooR9pvU2OShunL8Un5jmTAf
       vZcrT+vsWU/kYIxHlzX9ATQj1XIFDWGNiowp2LETV0Kd1jXusX4005ESdXc40cK/BS9uxzcedb
       S5xGmO5bnywtB/VxDOYYIBCdy7e+duoAAAOw==}

 bind .c <ButtonPress-1> {bPress1 %W %x %y}
 bind .c <ButtonPress-3> {bPress3 %W %x %y}
 bind . <Configure> {wm title . "Canvas Example (Height = [winfo height .c] / Width = [winfo width .c])"}

 proc bPress1 {w x y} {

   set i [lindex [$w find overlapping $x $y $x $y] end]
   if { $i == "" } {
        set i [$w create image $x $y -anchor nw -image ::img::ah -tags card]
        setFocus $w $i
      } else {
        setFocus $w $i
      }

 };# bPress1

 proc bPress3 {w x y} {

   set close [lindex [$w find overlapping $x $y $x $y] end]
   if { $close != "" && [lsearch [.c gettags $close] "hasfocus"] != "-1" } {
        puts "Coords of Card: [.c coords $close] ($close)"
      } else {
        puts "Coords of Click: $x $y ($close)"
      }

 };# bPress3

 proc setFocus {w i} {

   if { [.c find withtag hasfocus] != "" } {
        $w itemconfigure [.c find withtag hasfocus] -image ::img::ah
        $w dtag [.c find withtag hasfocus] hasfocus
      }
   $w focus $i
   $w itemconfigure $i -image ::img::as
   $w addtag hasfocus withtag $i

 };# setFocus
