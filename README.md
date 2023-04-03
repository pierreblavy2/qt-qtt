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



# Translatable

This class makes widgets easy to translate.
* call my_widget->translate() to update content according to current language.
* call translate(false) at the end of the constructor
* override the translate method, see example for details.
```
void XXX::translate(bool tr_sons){
    //translate regular members
    memer->setText(tr("xxx"));
    
    
    //translate translatable members, only if tr_sons is true
    if(tr_sons){
      translateble_member->translate();
    }
}
```




## Example
```
//my_xxx.hpp
#include <qtt_Translatable.hpp>

class MySubWidget:public QWidget, qtt::Translatable{
  Q_OBJECT
  public:
  explicit MyWidget(QWidget*parent=nullptr);
  void translate(bool tr_sons=false)override;
  
  QLabel * hello =nullptr;
  QLabel * word  =nullptr;
};


class MyWidget:public QWidget, qtt::Translatable{
  Q_OBJECT
  public:
  explicit MyWidget(QWidget*parent=nullptr);
  void translate(bool tr_sons=true)override;
  
  QLabel      * title =nullptr;
  MySubWidget * sub   =nullptr;
  
};


//my_xxx.cpp
MySubWidget::MySubWidget(QWidget*parent):Qwidget(parent){
  //as usual
  QHBoxLayout * layout = new QHBoxLayout;
  this->setLayout(layout);
  qtt::cstr_in_layout(hello,layout);
  qtt::cstr_in_layout(world,layout);
  
  //HERE : add translate
  translate(false);
}

void MySubWidget::translate(bool tr_sons){
  hello->setText(tr("hello"));
  world->setText(tr("world"));
}


MyWidget::MySWidget(QWidget*parent):Qwidget(parent){
  //as usual
  QVBoxLayout * layout = new QVBoxLayout;
  this->setLayout(layout); 
  qtt::cstr_in_layout(title,layout);
  qtt::cstr_in_layout(sub,layout);
  
  //HERE : add translate
  translate(false);
}

void MySubWidget::translate(bool tr_sons){
  //always translate non translatable
  title.setText(tr("TITLE"));
  
  //translate translatable sub objects only if tr_sons is true
  //this avoid multiple translation, as constructors call translate
  if(tr_sons){
    son->translate();
  }
}
```

## Main loop, for a translatable main window
```
int main(int argc, char *argv[]){
        QApplication app(argc, argv);

        QTranslator translator;
        const QString translation_path = "translations/fr.qm";
        bool tr_ok = translator.load(translation_path);
        if(tr_ok){
            std::cout << "Using translation "<< translation_path.toStdString() <<std::endl;
            app.installTranslator(&translator);
        }else{
            std::cerr << "Cannot find translation : "<< translation_path.toStdString() <<std::endl;
        }

        MainWindow mainWin;
        mainWin.translate();
        mainWin.show();
        
        return app.exec();
}
```











```












