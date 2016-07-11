//
// Created by patryk on 26.10.15.
//
#include <gl_core_3_3.hpp>
#include "Viewport.hpp"

#include <iostream>
#include <zinot-engine/eng/Engine.hpp>
#include <zinot-engine/res/Shader.hpp>
#include <zinot-engine/res/Texture.hpp>
#include <zinot-engine/res/models/Model.hpp>
#include <zinot-engine/res/GpuProgram.hpp>
#include <zinot-engine/eng/FPSCamera.hpp>
#include <zinot-engine/eng/Window.hpp>

#include <SFML/Window.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

void Zinot::Viewport::initializeScene()
{
   resMgr.reset(new MapResMgr());

   // Register names
   auto & namesRegister = resMgr->getNamesRegister();
   NamesRegister::NameId shaderVsPath = namesRegister.addName("media/shaders/shader.vs.glsl");
   NamesRegister::NameId shaderFsPath = namesRegister.addName("media/shaders/shader.fs.glsl");
   NamesRegister::NameId gpuProgPath = namesRegister.addName("media/virtual/shader.gpu");
   NamesRegister::NameId modelPath = namesRegister.addName("media/models/ursus.obj");

   // Create VertexPos Shader
   Shader * vs = (Shader *) resMgr->getRes(shaderVsPath);
   if (!vs)
      vs = (Shader *) resMgr->newRes(shaderVsPath, new Shader, true);
   vs->loadFromFile(gl::VERTEX_SHADER);

   // Create Fragment Shader
   Shader * fs = (Shader *) resMgr->getRes(shaderFsPath);
   if (!fs)
      fs = (Shader *) resMgr->newRes(shaderFsPath, new Shader, true);
   fs->loadFromFile(gl::FRAGMENT_SHADER);

   // Create GPU Program
   program = (GpuProgram *) resMgr->getRes(gpuProgPath);
   if (!program)
      program = (GpuProgram *) resMgr->newRes(gpuProgPath, new GpuProgram, true);
   program->loadFromShaders(vs->getShader(), fs->getShader());

   // Create model
   model = (Model *) resMgr->getRes(modelPath);
   if (!model)
      model = (Model *) resMgr->newRes(modelPath, new Model, true);
   bool modelRet = model->loadFromFile(resMgr.get());

   /*     -5-      -6-
    *
    *  -1-      -2-
    *
    *     -4-      -7-
    *
    *  -0-      -3-
    *
    */
   /*QVector<GLfloat> verts = {
		-0.5f, -0.5f, 0.5f, // 0
		-0.5f, 0.5f, 0.5f, // 1
		0.5f, 0.5f, 0.5f, // 2
		0.5f, -0.5f, 0.5f, // 3
		-0.5f, -0.5f, -0.5f, // 4
		-0.5f, 0.5f, -0.5f, // 5
		0.5f, 0.5f, -0.5f, // 6
		0.5f, -0.5f, -0.5f // 7
	};

   QVector<GLuint> elements = {
		1, 3, 0,  // front
		1, 2, 3,
		6, 4, 7,  // back
		6, 5, 4,

		2, 7, 3,  // right
		2, 6, 7,
		5, 0, 4,  // left
		5, 1, 0,

		0, 3, 4,  // bottom
		3, 7, 4,
		5, 2, 1,  // top
		5, 6, 2
	};

	gl::GenBuffers(1, &vbo);
	gl::GenBuffers(1, &ebo);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
   gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);

   gl::BufferData(gl::ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), gl::STATIC_DRAW);
   gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, 0);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);*/

   auto wndSize = parentWnd->getSFMLWindow()->getSize();
   gl::Viewport(0, 0, wndSize.x, wndSize.y);

   projMatrix = glm::perspective(glm::radians(70.0f),   // FOV
                                 (float) wndSize.x / (float) wndSize.y, // aspect
                                 0.1f, 100.0f); // near, far

   // Vao for compatibility
   GLuint vao;
   gl::GenVertexArrays(1, &vao);
   gl::BindVertexArray(vao);

   gl::Enable(gl::DEPTH_TEST);
   gl::DepthFunc(gl::LESS);
   gl::Enable(gl::TEXTURE_2D);

   gl::Enable(gl::CULL_FACE);
   gl::CullFace(gl::BACK);

   cam.setPosition(glm::vec3(0, 0, 0));
   cam.setVectorUp(glm::vec3(0, 1, 0));
}

void Zinot::Viewport::render()
{
   gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

   gl::UseProgram(program->getProgram());

   viewMatrix = cam.getMatrix();
   modelMatrix = glm::translate(glm::vec3(0.0f, 0.0f, -2.0f));

   GLint modelLoc = gl::GetUniformLocation(program->getProgram(), "model");
   GLint viewLoc = gl::GetUniformLocation(program->getProgram(), "view");
   GLint projLoc = gl::GetUniformLocation(program->getProgram(), "proj");
   gl::UniformMatrix4fv(modelLoc, 1, gl::FALSE_, glm::value_ptr(modelMatrix));
   gl::UniformMatrix4fv(viewLoc, 1, gl::FALSE_, glm::value_ptr(viewMatrix));
   gl::UniformMatrix4fv(projLoc, 1, gl::FALSE_, glm::value_ptr(projMatrix));

   model->draw(program->getProgram());
}

bool Zinot::Viewport::dispatchEvent(sf::Event & event)
{
   if (event.type == sf::Event::MouseMoved)
   {
      static glm::vec2 lastMousePos;
      glm::vec2 mousePos(event.mouseMove.x, event.mouseMove.y);

      glm::vec2 deltaPos(mousePos - lastMousePos);
      const float mouseSensitivity = 0.1f;
      deltaPos *= mouseSensitivity;
      deltaPos.y *= -1;
      cam.addRotation(deltaPos);

      sf::Window const & sfWindow = *parentWnd->getSFMLWindow();
      auto windowSize = sfWindow.getSize();

      float maxMousePosRadius = glm::min(windowSize.x, windowSize.y) / 3;
      glm::vec2 windowCenter(windowSize.x / 2, windowSize.y / 2);

      if (glm::distance(mousePos, windowCenter) > maxMousePosRadius)
      {
         lastMousePos = windowCenter;
         sf::Mouse::setPosition(sf::Vector2i((int) windowCenter.x, (int) windowCenter.y), sfWindow);
      }
      else
      {
         lastMousePos = mousePos;
      }
   }
   if (event.type == sf::Event::KeyPressed)
   {
      if (event.key.code == sf::Keyboard::Right)
         cam.addRotation(glm::vec2(1, 0));
      if (event.key.code == sf::Keyboard::Left)
         cam.addRotation(glm::vec2(-1, 0));
      if (event.key.code == sf::Keyboard::Up)
         cam.addRotation(glm::vec2(0, 1));
      if (event.key.code == sf::Keyboard::Down)
         cam.addRotation(glm::vec2(0, -1));
      if (event.key.code == sf::Keyboard::W)
      {
         glm::vec3 direction = cam.getDirection();
         cam.translate(glm::normalize(direction) * 0.1f);
      }
      if (event.key.code == sf::Keyboard::S)
      {
         glm::vec3 direction = cam.getDirection();
         cam.translate(glm::normalize(direction) * -0.1f);
      }
      if (event.key.code == sf::Keyboard::A)
      {
         /*  ^ = cross(up x direction)
          *  |   ^
          *  |  / = direction
          *  | /
          *  |/      = up
          *  *-------->
          */

         glm::vec3 leftDir = glm::cross(cam.getUpVector(), cam.getDirection());
         cam.translate(glm::normalize(leftDir) * 0.1f);
      }
      if (event.key.code == sf::Keyboard::D)
      {
         glm::vec3 rightDir = glm::cross(cam.getDirection(), cam.getUpVector());
         cam.translate(glm::normalize(rightDir) * 0.1f);
      }
   }

   return true;
}

