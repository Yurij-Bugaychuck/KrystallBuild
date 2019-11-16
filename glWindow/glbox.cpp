#include "glbox.h"
#include <QAxAggregated>
#include <QUuid>
//! [0]
#include <objsafe.h>
//! [0]

#if defined(Q_CC_MSVC)
#pragma warning(disable:4305) // init: truncation from const double to float
#endif

/*!
  Create a GLBox widget
*/

GLBox::GLBox(QWidget *parent, const char *name, QVector<coordinates> *Planes, gpu *Gpu)
    : QGLWidget(parent)
{
    m_xRot = 0;
    m_yRot = 0;
    m_zRot = 0;       // default object rotation
    m_scale = 2;                       // default object scale
    m_object = 0;

    MPlanes = Planes;
    GPU = Gpu;
}


/*!
  Release allocated resources
*/

GLBox::~GLBox()
{
    makeCurrent();

    if (m_object)
        glDeleteLists(m_object, 1);
}


/*!
  Paint the box. The actual openGL commands for drawing the box are
  performed here.
*/

void GLBox::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslated(-5, -5.0, -10.0);
    glScalef(m_scale, m_scale, m_scale);
//    glFrustum(-10, 10, -10, 10, 10, 150);
    glRotatef(-90, 1, 0, 0);
    glRotatef(m_xRot, 1.0, 0.0, 0.0);
    glRotatef(m_yRot, 0.0, 1.0, 0.0);
    glRotatef(m_zRot, 0.0, 0.0, 1);

//    qInfo() << m_xRot <<" "<< m_yRot << " " << m_zRot;
    glCallList(m_object);
}


/*!
  Set up the OpenGL rendering state, and define display list
*/

void GLBox::initializeGL()
{
    initializeOpenGLFunctions();

    qglClearColor(Qt::black);           // Let OpenGL clear to black
    m_object = makeObject();            // Generate an OpenGL display list
    glShadeModel(GL_FLAT);
}



/*!
  Set up the OpenGL view port, matrix mode, etc.
*/

void GLBox::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, 5, 150);
    glMatrixMode(GL_MODELVIEW);
}


/*!
  Generate an OpenGL display list for the object to be shown, i.e. the box
*/

GLuint GLBox::makeObject()
{
    GLuint list;

    list = glGenLists(1);

    glNewList(list, GL_COMPILE);

    float a = 20; //Размер системы

    //xAxis
    glColor3ub(255,0,0); //red
    glBegin(GL_LINE_STRIP);
        glVertex3f(-a, 0, 0);
        glVertex3f(a, 0, 0);
    glEnd();

    //yAxis
    glColor3ub(0,255,0); //green

    glBegin(GL_LINE_STRIP);
        glVertex3f(0, -a, 0);
        glVertex3f(0, a, 0);
    glEnd();

    //zAxis
    glColor3ub(0,0,255); //blue

    glBegin(GL_LINE_STRIP);
        glVertex3f(0, 0, -a);
        glVertex3f(0, 0, a);
    glEnd();

    //render StructGen

     QMap<coordinates, gItem*> *PointsList = GPU->getCoor();
    qInfo() << "OKKK2";

//     qInfo() << (*PointsList);

     glColor3ub(255,87, 34);


     glBegin(GL_LINES);

        for(QMap<coordinates, gItem*>::iterator i = PointsList->begin(); i != PointsList->end(); ++i){
            gItem *TElem = i.value();
            QVector<gItem*> *TmpV = TElem->Neighbors;
            coordinates Poi =  TElem->getCoor();
            for(int i = 0; i < TmpV->size(); ++i){
                glVertex3f(Poi.x, Poi.y, Poi.z);
                glVertex3f(TmpV->at(i)->getCoor().x,TmpV->at(i)->getCoor().y, TmpV->at(i)->getCoor().z);
            }
//            if (PointsList->contains(coordinates(Poi.x + 1, Poi.y, Poi.z))) {
//                glVertex3f(Poi.x, Poi.y, Poi.z);
//                glVertex3f(Poi.x + 1, Poi.y, Poi.z);
//            }

//             if (PointsList->contains(coordinates(Poi.x, Poi.y + 1, Poi.z))) {
//                 glVertex3f(Poi.x, Poi.y, Poi.z);
//                 glVertex3f(Poi.x, Poi.y + 1, Poi.z);
//             }

//              if (PointsList->contains(coordinates(Poi.x, Poi.y, Poi.z + 1))) {
//                  glVertex3f(Poi.x, Poi.y, Poi.z);
//                  glVertex3f(Poi.x, Poi.y, Poi.z + 1);
//              }

        }

     glEnd();

     glPointSize(10);
     glColor3ub(0,188,212);

     glEnable(GL_POINT_SMOOTH);
     glBegin(GL_POINTS);

        for(QMap<coordinates, gItem*>::iterator i = PointsList->begin(); i != PointsList->end(); ++i){
            gItem *TElem = i.value();
            coordinates Poi =  TElem->getCoor();
//            qInfo() << Poi.x << " " << Poi.y <<" "<<Poi.z;
            if (Poi.x - (int)Poi.x > 0 || Poi.y - (int)Poi.y > 0 || Poi.z - (int)Poi.z > 0  ) glColor3ub(255,255, 255);
             glVertex3f(Poi.x, Poi.y, Poi.z);
            glColor3ub(0,188,212);
        }

     glEnd();


//    glColor3ub(139, 195, 74, 0.5);|
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4ub(139, 195, 74, 120);
     //Planes
    int cc = 4;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLES);
    for(auto i: *MPlanes){
        glVertex3f(i.x * cc + 1, 0, 0);
        glVertex3f(0, i.y * cc + 1, 0);
        glVertex3f(0, 0, i.z * cc + 1);
    }

    glEnd();






    //end

    glEndList();

    return list;
}
/*!
  Set the rotation angle of the object to \e degrees around the X axis.
*/

void GLBox::setXRotation(int degrees)
{
    m_xRot = (GLfloat)(degrees % 360);
    updateGL();
}


/*!
  Set the rotation angle of the object to \e degrees around the Y axis.
*/

void GLBox::setYRotation(int degrees)
{
    m_yRot = (GLfloat)(degrees % 360);
    updateGL();
}


/*!
  Set the rotation angle of the object to \e degrees around the Z axis.
*/

void GLBox::setZRotation(int degrees)
{
    m_zRot = (GLfloat)(degrees % 360);
    updateGL();
}

//! [1]
class ObjectSafetyImpl : public QAxAggregated,
                         public IObjectSafety
{
public:
//! [1] //! [2]
    explicit ObjectSafetyImpl() {}

    long queryInterface(const QUuid &iid, void **iface)
    {
        *iface = nullptr;
        if (iid == IID_IObjectSafety)
            *iface = (IObjectSafety*)this;
        else
            return E_NOINTERFACE;

        AddRef();
        return S_OK;
    }

//! [2] //! [3]
    QAXAGG_IUNKNOWN;

//! [3] //! [4]
    HRESULT WINAPI GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
    {
        *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
        *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
        return S_OK;
    }

    HRESULT WINAPI SetInterfaceSafetyOptions(REFIID riid, DWORD pdwSupportedOptions, DWORD pdwEnabledOptions)
    {
        return S_OK;
    }
};
//! [4] //! [5]

QAxAggregated *GLBox::createAggregate()
{
    return new ObjectSafetyImpl();
}
//! [5]
