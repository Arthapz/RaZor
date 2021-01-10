#pragma once

#ifndef RAZOR_APPWINDOW_HPP
#define RAZOR_APPWINDOW_HPP

#include <RaZ/Application.hpp>

#include <QWindow>

#include <unordered_map>

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
#include <QHash>

template <>
struct std::hash<QString> {
  std::size_t operator()(const QString& str) const noexcept { return static_cast<std::size_t>(qHash(str)); }
};
#endif

class MainWindow;

namespace Raz {

class Camera;
class Collider;
class Light;
class Mesh;
class RenderSystem;
class Sound;
class Transform;

} // namespace Raz

class AppWindow : public QWindow {
  friend MainWindow;

public:
  AppWindow();

  void initialize();
  void render();
  void updateLights() const;
  Raz::Entity& addEntity(QString name);
  Raz::Entity& recoverEntity(const QString& name);
  void enableEntity(const QString& name, bool enabled = true);
  void disableEntity(const QString& name) { enableEntity(name, false); }
  void loadComponents(const QString& entityName);
  void clearComponents();

protected:
  bool event(QEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void exposeEvent(QExposeEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

private:
  void importMesh(const Raz::FilePath& filePath);
  void loadCubemap(const Raz::FilePath& rightTexturePath, const Raz::FilePath& leftTexturePath,
                   const Raz::FilePath& topTexturePath, const Raz::FilePath& bottomTexturePath,
                   const Raz::FilePath& frontTexturePath, const Raz::FilePath& backTexturePath);

  void showTransformComponent(Raz::Entity& entity);
  void showCameraComponent(Raz::Camera& camera);
  void showMeshComponent(Raz::Mesh& mesh);
  void showLightComponent(Raz::Light& light);
  void showColliderComponent(Raz::Collider& collider);
  void showSoundComponent(Raz::Sound& sound);
  void showAddComponent(Raz::Entity& entity, const QString& entityName, const Raz::RenderSystem& renderSystem);
  void processActions();

  MainWindow* m_parentWindow {};

  QOpenGLContext* m_context {};

  Raz::Application m_application {};
  Raz::Entity* m_cameraEntity {};
  Raz::Camera* m_cameraComp {};
  Raz::Transform* m_cameraTrans {};

  std::unordered_map<QString, Raz::Entity*> m_entities {};

  bool m_movingRight    = false;
  bool m_movingLeft     = false;
  bool m_movingUp       = false;
  bool m_movingDown     = false;
  bool m_movingForward  = false;
  bool m_movingBackward = false;

  bool m_leftClickPressed   = false;
  bool m_middleClickPressed = false;
  bool m_rightClickPressed  = false;

  QPointF m_prevMousePos {};
};

#endif // RAZOR_APPWINDOW_HPP
