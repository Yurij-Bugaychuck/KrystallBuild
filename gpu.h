#ifndef GPU_H
#define GPU_H
#include<QMap>
#include "gitem.h"
#include<QQueue>
class gpu
{
    QMap<coordinates, gItem*>  *isCoor;

    static int kolG;
    coordinates start = coordinates(1, 1, 1);

    static coordinates tmpSort;
public:
    QString Kek = "asdasd";
    gpu();
    void structGen(int sz, coordinates start);


    QMap <coordinates, gItem*> *getCoor(){
        return isCoor;
    }
    void createElem(coordinates coor, coordinates pred);
    void createOCK(coordinates coor, coordinates pred);
    QVector<coordinates>* SortByCS(coordinates s);

    static bool cmp(coordinates a, coordinates b);

    void print();
    ~gpu();
};

#endif // GPU_H
