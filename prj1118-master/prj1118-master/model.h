#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject {
    Q_OBJECT

 public:
    Model() {m_value = 0;}
    int value() const {return m_value;}

 public slots:
    void setValue(int);

 signals:
    void valueChanged(int);

 private:
    int m_value;

};

#endif // MODEL_H
