     #  Create the main message window
     message .m -text "Hello Tcl!" -background white
     pack .m -expand true -fill both -ipadx 100 -ipady 40

     #  Create the main menu bar with a Help-About entry
     menu .menubar
     menu .menubar.help -tearoff 0
     .menubar add cascade -label "Help" -menu .menubar.help -underline 0
     .menubar.help add command -label "About Hello ..." \
          -accelerator "F1" -underline 0 \
          -command showAbout

     #  Define a procedure - an action for Help-About
     proc showAbout {} {
          tk_messageBox -message "Tcl/Tk\nHello Windows\nVersion 1.0" \
               -title "About Hello"
     }

     #  Configure the main window
     wm title . "Hello Foundation Application"
     . configure -menu .menubar -width 200 -height 150
     bind . "<Key F1>" {showAbout}
