#include "gitem.h"

gItem::gItem(coordinates Coor):coor(Coor){
    Neighbors = new QVector<gItem*>;
}


gItem::~gItem(){
    Neighbors->clear();
    delete Neighbors;
}

