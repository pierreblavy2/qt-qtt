# Introduction
This small template library makes the creation of qt objects easier
* qtt.hpp contains functions to easily create widgets in layouts
* qtt_layout.hpp contains functions to create specific layouts and widgets.
* qtt_Translatable contains function to make your objects translatable.


# qtt.hpp

## Creates a new Widget_t
```void cstr_auto(Widget_t*me &, A...a)```
* Throw if me is not null
* Create a new Widget_t by fowarding A... to Widget_t constructor.
* Return a pointer to the newly created widget. 
* The user OWNS the me pointer.


##  Creates a new Widget_t in an existing layout
```void cstr_in_layout(Widget_t*me &, Layout_t *layout, A...a)```

* Throw if me is not null
* Throw if layout is null
* Create a new Widget_t by fowarding A... to Widget_t constructor.
* Add the widget to the layout
* The user DO NOT OWN the me pointer, as it's a child of the layout.

## Creates a new widget in a grid layout at position
```
void cstr_in_grid     (Widget_t* &me, Layout_t *layout, int row, int column,  A...a)
void cstr_in_grid_span(Widget_t* &me, Layout_t *layout, int row, int column, int rowspan, int colspan,  A...a)
```

* Throw if me is not null
* Throw if layout is null
* Create a new Widget_t by fowarding A... to Widget_t constructor.
* Add the widget to the layout, at position row, column
* The user DO NOT OWN the me pointer, as it's a child of the layout.

## Create spacer items in layout
```
QSpacerItem* space_h(Layout_t *layout, int x=0); //horizontal
QSpacerItem* space_v(Layout_t *layout, int y=0); //vertical

//horizontal for QHBoxLayout, Vertical for QVBoxLayout
QSpacerItem* space(QHBoxLayout *layout, int x_or_y=0);
QSpacerItem* space(QVBoxLayout *layout, int x_or_y=0);
```

* Throw if layout is null
* Create a new QSpacerItem
* Add the QSpacerItem to the layout
* Returns a pointer on the created spacer item. The user DO NOT OWN the returned pointer, as it's a child of the layout.

## Example
```
//Example.hpp
class Example : public QWidget{
  Q_OBJECT
  public:
  explicit Example(QWidget*parent=nullptr);
  
  QLabel * hello = nullptr;
  QLabel * word  = nullptr;
};

//Example.cpp
#include <qtt.hpp>

explicit Example::Example(QWidget*parent):QWidget(parent){
    QHBoxLayout * layout = new QHBoxLayout;
    this->setLayout(layout);
    qtt::cstr_in_layout(hello,layout);
    qtt::cstr_in_layout(world,layout);
    hello->setText("hello");
    world->setText("world");
}
```


# qtt_layout.hpp

## Encapsulate layout in widget
```
std::tuple<QWidget*,QLayout_t*> make_widget_layout(QWidget     * parent, A... layout_args); //1
std::tuple<QWidget*,QLayout_t*> make_widget_layout(QMainWindow * parent, A... layout_args); //2
std::tuple<QFrame* ,QLayout_t*>  make_framed_layout(QWidget     * parent, A... layout_args); //3
```
* throw if parent is null
* Create a QWidget and a QLayout as childs of parent, sent the margins to 0
* Returns a QWidget* QLayout* that are NOT OWNED by the user, as they are (sub) childs of parent.

## Example 1 : simple layout in main window
```
//MainWindow.hpp
class MainWindow : public QMainWindow{
  Q_OBJECT
  public:
  MainWindow();
  QLabel * hello =nullptr;
  QLabel * word  =nullptr;
};

//MainWindow.cpp
#include <qtt.hpp>
#include <qtt_layout.hpp>
MainWindow::MainWindow(){
  auto [widget, main_layout] = qtt::make_widget_layout<QVBoxLayout>(this);
  qtt::cstr_in_layout(hello,main_layout);
  qtt::cstr_in_layout(world,main_layout);
  hello->setText("hello");
  world->setText("world");
}

```



## Example 2 : Widgets in a QFrame (or in a QWidget)
```
If you want a QWidget instead of a QFrame, replace line 1 by `qtt::make_widget_layout<QHBoxLayout>(this)`
//FrameWidget.hpp
class FrameWidget : public QWidget{
  Q_OBJECT
  public:
  explicit MyWidget(QWidget*parent=nullptr);
  QLabel * hello =nullptr;
  QLabel * word  =nullptr;
};

//FrameWidget.cpp
#include <qtt.hpp>
#include <qtt_layout.hpp>
FrameWidget::FrameWidget(QWidget*parent):QWidget(parent){
  auto [widget, layout] = qtt::make_framed_layout<QHBoxLayout>(this); //1
  qtt::cstr_in_layout(hello,main_layout);
  qtt::cstr_in_layout(world,main_layout);
  hello->setText("hello");
  world->setText("world");
}
```





