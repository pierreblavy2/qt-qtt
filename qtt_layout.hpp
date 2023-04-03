#ifndef QTT_LAYOUT_HPP
#define QTT_LAYOUT_HPP

//--- extra utilities to make layouts easily ---
//should be included in cpp, not in hpp

#include <QLayout>
#include <QFrame>
#include <QMainWindow>

#include "qtt.hpp"

namespace qtt{

//usage
//  auto [widget,widget_layout] = qtt::make_widget_layout<QVBoxLayout>(parent);
//  parent  will contain a unique QWidget   : widget
//  widget  will have a QVBoxLayout called  : widget_layout

template<typename QLayout_t, typename ... A>
std::tuple<QWidget*,QLayout_t*> make_widget_layout(QWidget * parent, A... layout_args){
    assert(parent!=nullptr);

    QVBoxLayout * main_layout = nullptr;
    qtt::cstr_auto (main_layout);
    parent->setLayout(main_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    //Widget
    QWidget * widget = nullptr;
    qtt::cstr_in_layout(widget , main_layout);

    QLayout_t * widget_layout=nullptr;
    qtt::cstr_auto(widget_layout, std::forward<A>(layout_args)... );
    widget->setLayout(widget_layout);

    return std::make_tuple(widget,widget_layout);
}

template<typename QLayout_t, typename ... A>
std::tuple<QWidget*,QLayout_t*> make_widget_layout(QMainWindow * window, A... layout_args){
    assert(window != nullptr);


    //Widget
    QWidget * widget = nullptr;
    QLayout_t * widget_layout=nullptr;

    qtt::cstr_auto(widget);
    qtt::cstr_auto(widget_layout, std::forward<A>(layout_args)... );

    widget->setLayout(widget_layout);
    window->setCentralWidget(widget);

    return std::make_tuple(widget,widget_layout);
}




//usage
//  auto [frame,frame_layout] = qtt::make_framed_layout<QVBoxLayout>(parent);
//  parent   will contain a unique QFrame   : frame
//  frame    will have a QVBoxLayout called : frame_layout

template<typename QLayout_t, typename ... A>
std::tuple<QFrame*,QLayout_t*> make_framed_layout(QWidget * parent, A... layout_args){
    assert(parent != nullptr);

    QVBoxLayout * main_layout = nullptr;
    qtt::cstr_auto (main_layout);
    parent->setLayout(main_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    //Frame
    QFrame * frame = nullptr;
    qtt::cstr_in_layout(frame , main_layout);
    frame->setFrameStyle(QFrame::Box);

    QLayout_t * frame_layout=nullptr;
    qtt::cstr_auto(frame_layout, std::forward<A>(layout_args)... );
    frame->setLayout(frame_layout);

    return std::make_tuple(frame,frame_layout);
}




}





#endif // QTT_LAYOUT_HPP
