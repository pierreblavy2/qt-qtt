#ifndef QTT_HPP
#define QTT_HPP

//A Set of QT tool that allows to write code easily, without the Qt awkwardness.
// version 2

//=== USAGE ===
/*
  // Construct a widget inside a layout
  cstr_in_layout(My_button, My_layout, cstr_params...);

  // Construct a widget
  cstr_auto(My_button, cstr_params ...);

  //Construct the layout of a window
  //returns the central widget, created to encapsulate the layout
  //this central widget is correctly parented, so you don't need to store it
  cstr_window_layout(My_window, My_layout, layout_params...)

  //Declare a class as Translatable
  publically derive from Translatable;
  override the void translate() function

*/

class QWidget;
class QLayout;


#include <type_traits>
#include <utility>
#include <cassert>

#include <QSpacerItem>

#include <QHBoxLayout>
#include <QVBoxLayout>


#include <QWidget>

namespace qtt{

namespace details {
template<
        typename Widget_t,
        typename Layout_t,
        typename ...A
>
std::enable_if_t< std::is_base_of<QLayout,Widget_t>::value >
 add_widget_or_layout(Widget_t* &me, Layout_t *layout, A... a){
    layout->addLayout(me,std::forward<A>(a)...);
}
}


namespace details {
template<
        typename Widget_t,
        typename Layout_t,
        typename ...A
>
std::enable_if_t< ! std::is_base_of<QLayout,Widget_t>::value >
add_widget_or_layout(Widget_t* &me, Layout_t *layout, A... a){
    layout->addWidget(me,std::forward<A>(a)...);
}
}


template<typename Widget_t, typename ...A>
inline void cstr_auto(Widget_t* &me, A...a){
    assert(me==nullptr);
    me = new Widget_t(std::forward<A>(a)... );
}



template<typename Widget_t, typename Layout_t, typename ...A>
inline void cstr_in_layout(Widget_t* &me, Layout_t *layout, A...a){
    // https://doc.qt.io/qt-6/qtwidgets-tutorials-widgets-nestedlayouts-example.html
    //NOTE : setLayout and addWidget automatically set the parent of the widgets
    assert(me==nullptr);
    assert(layout !=nullptr);
    me = new Widget_t(std::forward<A>(a)... );
    details::add_widget_or_layout(me,layout);
}


template<typename Widget_t, typename Layout_t, typename ...A>
inline void cstr_in_grid(Widget_t* &me, Layout_t *layout, int row, int column,  A...a){
    // https://doc.qt.io/qt-6/qtwidgets-tutorials-widgets-nestedlayouts-example.html
    //NOTE : setLayout and addWidget automatically set the parent of the widgets
    assert(me==nullptr);
    assert(layout !=nullptr);
    me = new Widget_t(std::forward<A>(a)... );
    details::add_widget_or_layout(me,layout,row,column);
}

template<typename Widget_t, typename Layout_t, typename ...A>
inline void cstr_in_grid_span(Widget_t* &me, Layout_t *layout, int row, int column, int rowspan, int colspan,  A...a){
    // https://doc.qt.io/qt-6/qtwidgets-tutorials-widgets-nestedlayouts-example.html
    //NOTE : setLayout and addWidget automatically set the parent of the widgets
    assert(me==nullptr);
    assert(layout !=nullptr);
    me = new Widget_t(std::forward<A>(a)... );
    details::add_widget_or_layout(me,layout,row,column,rowspan,colspan);
}


/*
//DEPRECIATED instead use
//    auto [widget, main_layout] = qtt::make_widget_layout<QVBoxLayout>(this);
//    with this a QMainWindow*
template<typename MainWindow_t, typename Layout_t, typename...A>
inline QWidget* cstr_window_layout(MainWindow_t* main_window, Layout_t *&layout, A... a ){
    assert(main_window != nullptr);
    assert(layout      == nullptr);

    cstr_auto(layout,std::forward<A>(a)...);

    QWidget * wid = new QWidget(main_window);
    main_window->setCentralWidget(wid);
    wid->setLayout(layout);

    return wid;
}
*/







//--- spaces ---
template<typename Layout_t> inline QSpacerItem* space_h(Layout_t *layout, int x=0){QSpacerItem * r=new QSpacerItem(x,0, QSizePolicy::Expanding , QSizePolicy::Minimum  ); layout->addItem(r); return r; }
template<typename Layout_t> inline QSpacerItem* space_v(Layout_t *layout, int y=0){QSpacerItem * r=new QSpacerItem(0,y, QSizePolicy::Minimum   , QSizePolicy::Expanding); layout->addItem(r); return r; }

inline QSpacerItem* space(QHBoxLayout *layout, int x_or_y=0){return space_h(layout,x_or_y );}
inline QSpacerItem* space(QVBoxLayout *layout, int x_or_y=0){return space_v(layout,x_or_y );}

}//end namespace qtt

#endif // QTT_HPP
