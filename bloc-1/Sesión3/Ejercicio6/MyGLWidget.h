#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent> // CAMBIO
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" // CAMBIO

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

    virtual void keyPressEvent (QKeyEvent *e);

  private:
    void createBuffers ();
    void carregaShaders ();
    void modelTransform1 ();  
    void modelTransform2 ();
    
    // attribute locations
    GLuint vertexLoc, colorLoc, transLoc;
    
    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1, VAO2, VBO1, VBO2;
    glm::vec3 scl = glm::vec3(1.0, 1.0, 1.0);
    GLfloat val_x = 0, val_y = 0;
    GLfloat angulo1 = 0.0, angulo2 = 0.0; 
};
