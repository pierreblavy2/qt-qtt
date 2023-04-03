#ifndef QTT_TRANSLATABLE_HPP_
#define QTT_TRANSLATABLE_HPP_

namespace qtt{
struct Translatable{
    virtual ~Translatable(){}
    virtual void translate(bool tr_sons=true)=0;
    // tr_sons avoid the double translate bug (translated once in member constructor, once again when translate is called from this constructor)
    // see example above
};
}


/*
//USAGE :
void MyClass: public QWidget, Translatable{
  Q_OBJECT
  public :

  MyTranslatable * my_translatable = nullptr;
  QWidget        * my_widget       = nullptr; //not Translatable


  MyClass(QWidget*parent):QWidget(parent){
    my_translatable =new ???;
    my_widget       =new ???;

    translate(false); //<< HERE call with false, as my_translatable constructor will call translate itself
  }

  void translate(bool tr_sons=true)override{

    //call translate on each translatable member only if translate_sons is true
    if(tr_sons){
      my_translatable->translate();
    }

    //translate non translatable widgets directly
    my_widget->setText(tr("Hello"));
  }

};




int main(int argc,char**argv){
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

        //...

        return app.exec();


}

*/




#endif
