menu .menubar.plugins -tearoff 0

# Add plugin window -----------------------------------------------------------

frame .add_plugin
label .add_plugin.namelbl -text "Name"
entry .add_plugin.name
label .add_plugin.versionlbl -text "Version"
entry .add_plugin.version

button .add_plugin.ok -text "Ok" -command "pack"

grid .add_plugin.namelbl -column 0 -row 0
grid .add_plugin.name -column 1 -row 0

grid .add_plugin.versionlbl -column 0 -row 1
grid .add_plugin.version -column 1 -row 1

grid .add_plugin.ok -column 0 -row 2 -columnspan 2


pack .add_plugin

proc pack {} {
   puts [.add_plugin.name cget -value]
}

# Menu Bar --------------------------------------------------------------

.menubar add cascade -label "Plugins" -menu .menubar.plugins

.menubar.plugins add command -label "Add Plugin ..." -command plugin_show_add_window
.menubar.plugins add command -label "Remove Plugin ..." -command plugin_show_remove_window
.menubar.plugins add command -label "About ..." -command plugin_show_about

proc plugin_show_add_window {} {
   raise .add_plugin
}

proc plugin_show_remove_window {} {

}

proc plugin_show_about {} {
    tk_messageBox -message "Pd Plugin Manager\nBy Lucão\nVersion 0.0" \
         -title "About Plugins"
}
