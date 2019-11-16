#ifndef GLBOX_H
#define GLBOX_H

#include <QtOpenGL>
#include <QOpenGLFunctions_4_3_Compatibility>
//! [0]
#include <QAxBindable>
#include "gpu.h"

class GLBox : public QGLWidget,
              public QOpenGLFunctions_4_3_Compatibility,
              public QAxBindable
{
    Q_OBJECT
    Q_CLASSINFO("ClassID",     "{5fd9c22e-ed45-43fa-ba13-1530bb6b03e0}")
    Q_CLASSINFO("InterfaceID", "{33b051af-bb25-47cf-a390-5cfd2987d26a}")
    Q_CLASSINFO("EventsID",    "{8c996c29-eafa-46ac-a6f9-901951e765b5}")
    //! [0] //! [1]
    QVector<coordinates> *MPlanes;
public:
    gpu *GPU;
    explicit GLBox(QWidget *parent, const char *name = nullptr, QVector<coordinates> *Planes = nullptr, gpu *Gpu = nullptr);
    virtual ~GLBox();
    QAxAggregated *createAggregate();

public slots:
    void                setXRotation(int degrees);
//! [1]
    void                setYRotation(int degrees);
    void                setZRotation(int degrees);

protected:
    void                initializeGL();
    void                paintGL();
    void                resizeGL(int w, int h);
    virtual GLuint      makeObject();

private:
    GLuint  m_object;
    GLfloat m_xRot;
    GLfloat m_yRot;
    GLfloat m_zRot;
    GLfloat m_scale;
};

#endif // GLBOX_H
