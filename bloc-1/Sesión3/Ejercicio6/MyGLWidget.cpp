#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers();
}

void MyGLWidget::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  glViewport (0, 0, width(), height()); // Aquesta crida no cal, Qt la fa de forma automàtica amb aquests paràmetres

  // Activem l'Array a pintar 
  modelTransform1();
  glBindVertexArray(VAO1);
 
  // Pintem l'escena
  // CAMBIO
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  modelTransform2();
  glBindVertexArray(VAO2);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  // Aquí anirà el codi que cal fer quan es redimensiona la finestra
}

void MyGLWidget::createBuffers ()
{
  // CAMBIO
  glm::vec3 Vertices[4];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(0.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(-1.0, 0.0, 0.0);
  Vertices[3] = glm::vec3(0.0, 0.0, 0.0);

  glm::vec3 Vertices2[3];
  Vertices2[0] = glm::vec3(0.0, 0.0, 0.0);
  Vertices2[1] = glm::vec3(1.0, 0.0, 0.0);
  Vertices2[2] = glm::vec3(0.5, 1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex  
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // CAMBIO
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);

  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");
  transLoc = glGetUniformLocation (program->programId(), "TG"); 
}

void MyGLWidget::modelTransform1 () {
  glm::mat4 TG(1.0);
  TG = glm::scale(TG, scl);
  TG = glm::rotate(TG, angulo1, glm::vec3(0, 0, 1));
  TG = glm::translate(TG, glm::vec3(val_x, val_y, 0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransform2 () {
  glm::mat4 TG(1.0);
  TG = glm::scale(TG, scl);
  TG = glm::rotate(TG, angulo2, glm::vec3(0, 0, 1));
  TG = glm::translate(TG, glm::vec3(val_x, val_y, 0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *e) {
  makeCurrent();

  // CAMBIO
  switch (e->key()) {
    case Qt::Key_S:
      scl.y -= 0.1;
      break;
    case Qt::Key_W:
      scl.y += 0.1;
      break;
    case Qt::Key_D:
      scl.x += 0.1;
      break;
    case Qt::Key_A:
      scl.x -= 0.1;
      break;
    case Qt::Key_P: // CAMBIO
      angulo1 += M_PI/6;
      angulo2 -= M_PI/6;
      break;
    default:
      e->ignore();
  }

  update();
}