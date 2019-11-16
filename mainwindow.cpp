#include "mainwindow.h"
#include<QDebug>
#include<algorithm>
#include <QtOpenGL>
#include<QAxFactory>
#include "glWindow/globjwin.h"
#include "glWindow/glbox.h"
#include<QString>
MainWindow::MainWindow(QObject *parent) : QObject(parent)
{

}

MainWindow::MainWindow(QQmlApplicationEngine *eng):engine(eng)
{

}

QString MainWindow::buttonClicked(const QString& sA, const QString& sB, const QString& sC){
    if (QOpenGLContext::openGLModuleType() != QOpenGLContext::LibGL) {
        qWarning("This system does not support OpenGL. Exiting.");
        return "";
    }

    float a = sA.toFloat();
    float b = sB.toFloat();
    float c = sC.toFloat();




    qInfo() << a <<" "<<b<<" " <<c;
    coordinates start = coordinates(a, 0, 0);
    GPU = new gpu;
    GPU->structGen(25, coordinates(-25,- 25, -25));

    qInfo() << "OK!";

    return  CalcBB(a, b, c);
//        QMap<coordinates, gItem* > *Elems = GPU->getCoor();

//        gItem *f = Elems->find(coordinates(7, 7, 7)).value();

}

float Plane(float a, float b, float c, coordinates P){

//    todo
    float plane = b*c*(P.x - a) + a*c*P.y + a * b * P.z;

    return plane;
}

float dPlane(float a, float b, float c, coordinates P){

    float plane = abs(Plane(a, b, c, P)) / sqrt(a*a + b*b + c*c);

    return plane;
}


struct cmp {
    bool operator()(const float& a, const float& b) const {
        return a < b;
    }
};

coordinates tmpSort = coordinates(0, 0, 0);
bool gcmp(coordinates a, coordinates b){
    float dist1 = tmpSort.dist(a);
    float dist2 = tmpSort.dist(b);

    return (dist1 < dist2);
}
QString MainWindow::CalcBB(float a,float b,float c){



        float mx = 1;
        if (a > 0) mx *= a;
        if (b > 0) mx *= b;
        if (c > 0) mx *= c;

       if (a != 0) a = mx / a;
        else a = 999999;

        if (b != 0) b = mx / b;
        else b = 999999;

        if (c != 0) c = mx / c;
        else c = 999999;

        float H = a; float K = b; float L = c;

        int dd = 0;
        coordinates start = coordinates(a, 0, 0);
        for(auto i : *GPU->getCoor()){
            if(dd == 100) break;
            if (Plane(H, K, L, i->getCoor()) == 0){
                start.x = i->getCoor().x;
                start.y = i->getCoor().y;
                start.z = i->getCoor().z;
                dd++;
            }
        }

        qInfo() << start.x <<" "<<start.y <<" "<<start.z << " | STAART" << " " << Plane(H, K, L, start);
       QVector<coordinates> *CS = GPU->SortByCS(start);

        QString ans = "";
        float d = 0;
        int kol = 0;
        int kol2 = 0;
        int kol3 = 0;

        int CS_A[1000] = {0};
        int BB_A[1000] = {0};
        bool isCS[10] = {0};

        memset(CS_A, 0, sizeof CS_A);
        memset(BB_A, 0, sizeof BB_A);
        float last = 0;

        for(auto i : *CS){
           if (kol2 > 5) break;

            if (start.dist(i) != last) kol2++, last  = start.dist(i);


            if (Plane(H, K, L, i) > 0) BB_A[kol2]++;
            CS_A[kol2]++;

//            qInfo() << start.dist(i) <<" "<<dPlane(a, b, c, i) <<" "<<kol2;
        }

        std::map< float, coordinates, cmp> q;
        coordinates MNP(a, 0, 0);
        float MND = 9999;

        for(auto i: *CS){
            if (Plane(a, b, c, i) < 0){
                MND = dPlane(H, K, L,i);
//                qInfo() << MND;
                q.insert({MND, i});
            }
        }

        qInfo() << q.size();
    int ttt = 0;
        for(std::map< float, coordinates>::iterator i = q.begin(); i != q.end(); ++i){
//            qInfo() << "----NEW---";
             ttt++;
             coordinates p = i->second;
             tmpSort = p;
             std::sort(CS->begin(), CS->end(), gcmp);
             //QVector<coordinates> *CS = GPU->SortByCS(p);
              kol2 = 0;
              last = 0;
              int ch = 0;

              qInfo() << "----CS-start---";
//              qInfo() << CS->size();

              for(auto j : *CS){
                 if (kol2 > 5) break;

                 if (p.dist(j) != last) kol2++, last  = p.dist(j);

                 if (kol2 == 1) qInfo() << j.x << " "<<j.y<<" "<<j.z << " " << j.dist(p)<< " " << Plane(H, K, L, j) <<" "<<kol2;


                 if (Plane(H, K, L, j) > 0) {
                     BB_A[kol2]++;
                     ch++;
                 };


             }
               qInfo() << "----CS-end---\n";
               qInfo() << i->first << " "<<ch <<" "<<ttt;
             if (ch == 0) break;


        }
        for(int i = 1; i <= 5; ++i){
            ans += "КС " + QString::number(i) + ": " + "Элементов " + QString::number(CS_A[i]) + ", разорванных связей: " + QString::number(BB_A[i]) + '\n';
        }

        return ans;
}


void MainWindow::buttonClickedDraw(const QString& sA, const QString& sB, const QString& sC){
    float a = sA.toFloat();
    float b = sB.toFloat();
    float c = sC.toFloat();

    float mx = std::max(a, std::max(b, c));

    if (a != 0) a = mx / a;
    else a = 999999;

    if (b != 0) b = mx / b;
    else b = 999999;

    if (c != 0) c = mx / c;
    else c = 999999;

    qInfo() << a <<" "<<b<<" " <<c;

    if (!QAxFactory::isServer()) {

       GLObjectWindow *w = new GLObjectWindow;
        w->newGPU(GPU);
        w->addPlane(a, b, c);
        w->resize(800, 600);
        w->show();
    }
}

