     #include "gpu.h"
#include <QtDebug>
#include<QPair>
#include<QtAlgorithms>
#include<math.h>
gpu::gpu()
{
    isCoor = new QMap<coordinates, gItem*>;
}
int gpu::kolG = 12;

void gpu::print(){
//    for(QMap<coordinates, gItem*>::iterator i = isCoor.begin(); i != isCoor.end(); ++i){
//        gItem *v =i.value();
//        qInfo() << v->getCoor().x <<" "<< v->getCoor().y<<" " << v->getCoor().z;
//    }
}

void gpu::structGen(int sz, coordinates start = coordinates(1, 1, 1)){
    this->start = start;

    QQueue< QPair<coordinates, coordinates> > dynQue;

    QVector< QPair< coordinates, QString > > NotStable;

    bool ock = 1;

    dynQue.push_back({start, coordinates(start.x - 1, start.y -1,start.z -1)});

    while(!dynQue.empty()){
        coordinates v = dynQue.first().first;
        coordinates pred = dynQue.first().second;
        dynQue.removeFirst();
        if (v.x <= sz && v.y <= sz && v.z <= sz && !(isCoor->contains(v))) createElem(v, pred);
        else if  (v.x <= sz && v.y <= sz && v.z <= sz){
            gItem *PredItem =  isCoor->find(pred).value();
            gItem *vItem =  isCoor->find(v).value();
            PredItem->Neighbors->push_back(vItem);
            vItem->Neighbors->push_back(PredItem);
            continue;
        }else continue;

        pred = v;

        v.x += 1;
            dynQue.push_back({v, pred});
        v.x -= 1;

        v.y += 1;
            dynQue.push_back({v, pred});
        v.y -= 1;

        v.z += 1;
            dynQue.push_back({v, pred});
        v.z -= 1;

        if (ock){
            v.x += 0.5; v.y += 0.5; v.z += 0.5;
            NotStable.push_back({v, "OCK"});
            v.x -= 0.5; v.y -= 0.5; v.z -= 0.5;
        }
    }

    for(int i = 0; i < NotStable.size(); ++i){
        QString Type = NotStable[i].second;
        coordinates v = NotStable[i].first;

        if (Type == "OCK"){

            if  (v.x <= sz && v.y <= sz && v.z <= sz){
                createElem(v, coordinates(v.x - 0.5f, v.y - 0.5f, v.z - 0.5f));
                gItem *vItem =  isCoor->find(v).value();

                 vItem->Neighbors->push_back(isCoor->find(coordinates(v.x + 0.5f, v.y + 0.5f, v.z + 0.5f)).value());
                 isCoor->find(coordinates(v.x + 0.5f, v.y + 0.5f, v.z + 0.5f)).value()->Neighbors->push_back(vItem);

                 vItem->Neighbors->push_back(isCoor->find(coordinates(v.x + 0.5f, v.y + 0.5f, v.z - 0.5f)).value());
                 isCoor->find(coordinates(v.x + 0.5f, v.y + 0.5f, v.z - 0.5f)).value()->Neighbors->push_back(vItem);

                 vItem->Neighbors->push_back(isCoor->find(coordinates(v.x + 0.5f, v.y - 0.5f, v.z + 0.5f)).value());
                 isCoor->find(coordinates(v.x + 0.5f, v.y - 0.5f, v.z + 0.5f)).value()->Neighbors->push_back(vItem);

                 vItem->Neighbors->push_back(isCoor->find(coordinates(v.x + 0.5f, v.y - 0.5f, v.z - 0.5f)).value());
                 isCoor->find(coordinates(v.x + 0.5f, v.y - 0.5f, v.z - 0.5f)).value()->Neighbors->push_back(vItem);

                 vItem->Neighbors->push_back(isCoor->find(coordinates(v.x - 0.5f, v.y + 0.5f, v.z + 0.5f)).value());
                 isCoor->find(coordinates(v.x - 0.5f, v.y + 0.5f, v.z + 0.5f)).value()->Neighbors->push_back(vItem);

                 vItem->Neighbors->push_back(isCoor->find(coordinates(v.x - 0.5f, v.y + 0.5f, v.z - 0.5f)).value());
                 isCoor->find(coordinates(v.x - 0.5f, v.y + 0.5f, v.z - 0.5f)).value()->Neighbors->push_back(vItem);

                 vItem->Neighbors->push_back(isCoor->find(coordinates(v.x - 0.5f, v.y - 0.5f, v.z + 0.5f)).value());
                 isCoor->find(coordinates(v.x - 0.5f, v.y - 0.5f, v.z + 0.5f)).value()->Neighbors->push_back(vItem);
            }
        }
    }

    qInfo() << "SUCCESS GEN!!";
    return;
}

void gpu::createOCK(coordinates coor, coordinates pred){

}


void gpu::createElem(coordinates coor, coordinates pred){
    kolG++;
//    qInfo() << coor.x <<" "<<coor.y<<" "<<coor.z;
    gItem *v = new gItem(coor);
//    qInfo() << "OK!";
    if (pred.x != start.x - 1){
       gItem *pr = isCoor->find(pred).value();

       pr->Neighbors->push_back(v);
       v->Neighbors->push_back(pr);
    }
//    qInfo() <<"OK!2";

    isCoor->insert(coor, v);

//    qInfo() << "OK!3";
    return;
}

bool gpu::cmp(coordinates a, coordinates b){
    float dist1 = tmpSort.dist(a);
    float dist2 = tmpSort.dist(b);

    return (dist1 < dist2);
}
QVector<coordinates>* gpu::SortByCS(coordinates Elem){
   QVector<coordinates> *Items = new QVector<coordinates>;
   gpu::tmpSort = Elem;

   for(auto *i: *isCoor){
        Items->push_back(i->getCoor());
   }

   std::sort(Items->begin(), Items->end(), gpu::cmp);

   return Items;
}

coordinates gpu::tmpSort = coordinates(0, 0, 0);

gpu::~gpu(){

};
