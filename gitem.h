#ifndef GITEM_H
#define GITEM_H
#include<QVector>
#include<math.h>
struct coordinates{
    float x, y, z;
    int id = 0;
    coordinates(){
        x = 0;
        y = 0;
        z = 0;
    }
    coordinates(float x,float y,float z){
        this->x = x;
        this->y = y;
        this->z = z;

    }

    void setId(int p){
        id = p;
    }


    float dist(coordinates a){
        return sqrt((x - a.x)*(x - a.x) + (y - a.y)*(y - a.y) + (z - a.z)*(z - a.z));
    }

    bool operator < (const coordinates& nelem) const {
        if (x < nelem.x) return true;
        if (x > nelem.x) return  false;

        if (y < nelem.y) return true;
        if (y > nelem.y) return  false;

        return  (z < nelem.z);
    }
};

class gItem{
    coordinates coor;

public:
    gItem(coordinates Coor);
    ~gItem();

    coordinates getCoor(){
        return coor;
    };

    QVector<gItem*> *Neighbors;
};

#endif // GITEM_H
