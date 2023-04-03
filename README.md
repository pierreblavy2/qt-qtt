# Introduction
This small template library makes the creation of qt objects easier
* qtt.hpp contains functions to easily create widgets in layouts
* qtt_layout.hpp contains functions to create specific layouts and widgets.
* qtt_Translatable contains function to make your objects translatable.


# qtt.hpp

## `void cstr_auto(Widget_t*me &, A...a)`: Create a new Widget_t

* Throw if me is not null
* Create a new Widget_t by fowarding A... to Widget_t constructor.
* Return a pointer to the newly created widget. The user OWNS the pointer.


## `void cstr_in_layout(Widget_t*me &, Layout_t *layout, A...a)` Create a new Widget_t in an existing layout

* Throw if me is not null
* Throw if layout is null
* Create a new Widget_t by fowarding A... to Widget_t constructor.
* Add the widget to the layout
* Return a pointer to the newly created widget. The user DO NOT OWN the pointer.

##  `void cstr_in_grid(Widget_t* &me, Layout_t *layout, int row, int column,  A...a)`
