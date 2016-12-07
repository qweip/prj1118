#include "model.h"

void Model::setValue(int value){
    if(value!=m_value){
        m_value=value;
        emit valueChanged(m_value);
    }
}
