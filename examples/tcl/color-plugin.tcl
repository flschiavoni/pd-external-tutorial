# META NAME My nifty plugin
# META DESCRIPTION Does all kinds of magic that may not be necessary for everyone
# META AUTHOR <John the Developer> johndev@mail.com

package require Tcl 8.5
package require Ttk
package require pdwindow 0.1

.menubar.file configure -bg white
.menubar.edit configure -bg red
.menubar.put configure -bg green
.menubar.find configure -bg brown
.menubar.media configure -bg pink
.menubar.window configure -bg purple
.menubar.help configure -bg blue


proc window_focusin {mytoplevel} {
    if {$mytoplevel eq ".pdwindow"} {
        puts "pd window"
        .menubar.edit entryconfigure [_ "Copy"] -state disabled
    } else {
        .menubar.edit entryconfigure [_ "Copy"] -state normal
        puts "Other window"
    }
}

bind PdWindow <FocusIn>                "window_focusin %W"
bind PatchWindow <FocusIn>             "window_focusin %W"

