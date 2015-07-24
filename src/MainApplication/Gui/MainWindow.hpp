#ifndef RADIUMENGINE_MAINWINDOW_HPP
#define RADIUMENGINE_MAINWINDOW_HPP

#include <QMainWindow>
#include <ui_MainWindow.h>

#include <qdebug.h>

namespace Ra { namespace Engine { class Entity; } }
namespace Ra { namespace Gui { class EntityTreeModel; } }
namespace Ra { namespace Gui { class Viewer; } }

namespace Ra { namespace Gui {

// Just forwards everything to the viewer.
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

    void createConnections();


    inline const std::vector<Core::KeyEvent>& getKeyEvents() const;
    inline const std::vector<Core::MouseEvent>& getMouseEvents() const;
    inline void flushEvents();

private slots:
    void loadFile();
    void clicked(QModelIndex index);
    void activated(QModelIndex index);

public slots:
    void entitiesUpdated();

signals:
    void entitiesUpdated(const std::vector<Engine::Entity*>&);

private:
    // Basic I/O management
    // Intercept key events from Qt

    virtual void keyPressEvent(QKeyEvent * event) override;
    virtual void keyReleaseEvent(QKeyEvent * event) override;
public:
    // Accept viewer mouse events.
    inline void viewerMousePressEvent(QMouseEvent* event);
    inline void viewerMouseReleaseEvent(QMouseEvent* event);
    inline void viewerMouseMoveEvent(QMouseEvent* event);
    inline void viewerWheelEvent(QWheelEvent* event);

private:
    static Core::MouseEvent mouseEventQtToRadium(const QMouseEvent* qtEvent);
    static Core::MouseEvent wheelEventQtToRadium(const QWheelEvent* qtEvent);
    static Core::KeyEvent   keyEventQtToRadium  (const QKeyEvent* qtEvent);

    // Output gui management
    void updateEntitiesTree();

private:
    // Stores the events received by the UI during last frame.
    std::vector<Core::MouseEvent> m_mouseEvents;
    std::vector<Core::KeyEvent>   m_keyEvents;

    EntityTreeModel* m_entityTreeModel;
};

} // namespace Gui
} // namespace Ra

#include <MainApplication/Gui/MainWindow.inl>

#endif // RADIUMENGINE_MAINWINDOW_HPP
