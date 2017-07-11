#include <GL/freeglut.h>

#include "glRender.h"

#include "Mark.hpp"
#include "WoodenBox.hpp"
#include "BrickBox.hpp"
//#include "QuadraticBezeirCurve.hpp"
//#include "SinusLine.hpp"
//#include "Line.hpp"
#include "aabbNodeVisualizator.hpp"

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;

using namespace glRender;

Render * render;

Camera * camera;
Camera * overlayCamera;

int counter = 0;
clock_t start;

//Mark * np;
//Mark * fp;
//Line * l;

UnderOverlayScene * scene;
OverlayScene * overlayScene;

NodePickerPtr nodePicker;

class CameraNode : public NodeMixedWith<IUpdateable, IDrawable, IKeyPressable>
{
public:
    CameraNode(Camera * camera) :
        m_camera(camera)
    {
        Geometry * geometry = GeometryHelper::Arrows();
        Textures * textures = new Textures();

        ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/colored.vertex", "data/colored.frag");
        shaderProgram->addAttribute<Vec3>("vertex");

        shaderProgram->addUniform<Mat4>("projection");
        shaderProgram->addUniform<Mat4>("view");
        shaderProgram->addUniform<Mat4>("model");
        shaderProgram->addUniform<Vec3>("color");

//        shaderProgram->setUniform<Vec3>("color", Vec3(0,1,0));

        m_model = new Model(geometry, textures, shaderProgram);
        m_model->setWireframeMode(true);
        Mat4 l = m_model->localMatrix();
        m_model->setLocalMatrix(l.scale(0.005f));
        m_model->setOrigin(0.5f, 0.25f, -2.0f);

//        transforms().translate(Vec3(0.5f, 0.25f, -2.0f));
    //    transforms().scale(0.2f);

//        transformsChanged();

    }

    void update() override
    {
//        transforms().rotateY(0.01f);
//        transformsChanged();
//        m_camera->setGlobalMatrix(globalTransforms());
    }

    void draw(Camera * camera) override
    {
//        m_model->shaderProgram()->setUniform<Vec3>("color", Vec3(0,1,0));
        m_model->draw(camera/*, parentsTransforms()*/);
    }

    void onKeyPress(KeyboardKey key) override
    {
        switch(key)
        {
        case IKeyPressable::KeyboardKey::W: {
            m_camera->setPosition(m_camera->position() + m_camera->front() * cameraMoveSpeed );
            m_model->setOrigin(m_model->origin() + m_camera->front() * cameraMoveSpeed);
        }; break;

        case IKeyPressable::KeyboardKey::S: {
            m_camera->setPosition(m_camera->position() - m_camera->front() * cameraMoveSpeed);
            m_model->setOrigin(m_model->origin() - m_camera->front() * cameraMoveSpeed);
        }; break;

        case IKeyPressable::KeyboardKey::A: {
            m_camera->setPosition(m_camera->position() - m_camera->right() * cameraMoveSpeed );
            m_model->setOrigin(m_model->origin() - m_camera->right() * cameraMoveSpeed);
        }; break;

        case IKeyPressable::KeyboardKey::D: {
            m_camera->setPosition(m_camera->position() + m_camera->right() * cameraMoveSpeed );
            m_model->setOrigin(m_model->origin() + m_camera->right() * cameraMoveSpeed);
        }; break;

        case IKeyPressable::KeyboardKey::Q: {
            m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() + cameraRotationSpeed, m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::E: {
            m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() - cameraRotationSpeed, m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::Z: {
            m_camera->setPosition(m_camera->position() + m_camera->up() * cameraMoveSpeed );
            m_model->setOrigin(m_model->origin() + m_camera->up() * cameraMoveSpeed);
        }; break;

        case IKeyPressable::KeyboardKey::X: {
            m_camera->setPosition(m_camera->position() - m_camera->up() * cameraMoveSpeed );
            m_model->setOrigin(m_model->origin() - m_camera->up() * cameraMoveSpeed);
        }; break;

        case IKeyPressable::KeyboardKey::R: {
            m_camera->setEulerAngles( m_camera->pitch() + cameraRotationSpeed, m_camera->yaw(), m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::F: {
            m_camera->setEulerAngles( m_camera->pitch() - cameraRotationSpeed, m_camera->yaw(), camera->roll() );
        }; break;

        default: {

        }

        }
    }

private:
    Camera * m_camera;
    float cameraMoveSpeed = 0.3f;
    float cameraRotationSpeed = 5.0f;

    Model * m_model;

};

class Tran : public NodeMixedWith<IUpdateable>
{
    void update() override
    {
//        transforms().rotateZ(0.1f);
//        transformsChanged();
    }

};

class Tran1 : public NodeMixedWith<IUpdateable>
{
    void update() override
    {
        transforms().rotateX(0.1f);
        transformsChanged();
    }

};

class Tran2 : public NodeMixedWith<IUpdateable>
{
    void update() override
    {
        transforms().rotateY(0.1f);
        transformsChanged();
    }

};


void init ()
{
    camera = new PerspectiveCamera( 35.0 / 180.0 * MATH_PI, 16.0f/9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());
//    camera->lookAt(Vec3(-10,0,-10), Vec3(10,0,-10), Vec3::AXE_Y());

    scene = new UnderOverlayScene();
    scene->setCamera(camera);

    nodePicker = std::make_shared<NodePicker>(camera, scene);

    Render::instance()->scenes().add(scene);

    srand( time(0) );

//    Mark * m = new Mark(0,1,0,1);
//    m->model()->setWireframeMode(false);
//    m->setOrigin(0.0f, 0.0f, -3.0f);
//    scene->addNode(m);

    Node * t = new Tran();

//    Node * t1 = new Tran1();

//    Node * t2 = new Tran2();

//    scene->add(t1);

//    Node * t1 = new Tran1();
//    Node * t2 = new Tran2();
//    t1->add(t);
//    t2->add(t1);

    for (int i=0; i<25; i++)
    {

    for (int j=0; j<25; j++)
    {

    for (int k=0; k<25; k++)
    {
//        if ((int)(rand() % 5) == 0)
//        {
//        } else
//        if ((int)(rand() % 3) == 1)
//        {
////             BrickBox *bb = new BrickBox();
////             bb->model()->setWireframeMode(false);
////             bb->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
////             scene->addNode(bb);
//        } else
//        if ((int)(rand() % 3) == 0)
//        {
            Mark * m = new Mark(Vec3(0,1,0),0.7,i,j,k);
//            Mat4 mm = camera->projectionMatrix();
//            m->m_model->m_shaderProgram->setUniform<Mat4>("projection", mm );

            m->model()->setOrigin(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50)) - 25));
            t->add(m);

//        }
//        else
//        if ((int)(rand() % 3) == 1)
//        {
////            Vec3 p0 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
////            Vec3 p1 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
//            Vec3 p0 = Vec3(-25.0f, 0.0f, -1.0f);
//            Vec3 p1 = Vec3(25.0f, 0.0f, -1.0f);

//            float r = (rand() % 255) / 255.0;
//            float g = (rand() % 255) / 255.0;
//            float b = (rand() % 255) / 255.0;

//            SinusLine * l = new SinusLine(p0, p1, 350, r, g, b);
//            l->setOrigin(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25)));

//            scene->addNode(l);
//        }
//        else
//        if ((int)(rand() % 5) == 4)
//        {
//            Vec3 p0 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
//            Vec3 p1 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
//            Vec3 p2 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));

//            float r = (rand() % 255) / 255.0;
//            float g = (rand() % 255) / 255.0;
//            float b = (rand() % 255) / 255.0;

//            QuadraticBezeirCurve * l = new QuadraticBezeirCurve(p0, p1, p2, 512, r, g, b);
//            scene->addNode(l);
//        }
    }
    }
    }
    scene->add(t);

//    Mark * mmm = new Mark(Vec3(0,1,0),1,0,0,0);
    CameraNode * cn = new CameraNode(camera);

//    Mark * aaa = new Mark(Vec3(1,0,0),0.05,0,0,5);
//    aaa->m_model->m_shaderProgram->setUniform<Mat4>("projection", mm );

//    Node * tmp = mmm;

//    for (int i=0; i<1000; i++)
//    {
//        Mark * m = new Mark(Vec3(0,0,1),0.7,i,0,0);
//        Mat4 mm = camera->projectionMatrix();
//        m->m_model->m_shaderProgram->setUniform<Mat4>("projection", mm );

////            m->model()->setOrigin(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, 0));
//        tmp->add(m);
//        tmp = m;
//    }

//    scene->add(mmm);

//    cn->add(aaa);

    scene->add(cn);
//    t1->add(t);
//    t2->add(t1);
//    scene->add(t2);

    overlayScene = new OverlayScene();
    overlayCamera = new PerspectiveCamera( 35.0 / 180.0 * MATH_PI, 16.0f/9.0f, 1.0f, 200.0f );
    overlayCamera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());
    overlayScene->setCamera(overlayCamera);

    WoodenBox *n = new WoodenBox();
    n->model()->setOrigin(0,0.0,-1);
    overlayScene->add(n);

    BrickBox *n1 = new BrickBox();
    n1->model()->setOrigin(0.1,0.1,-1.4);
    overlayScene->add(n1);

    Render::instance()->scenes().add(overlayScene);

}

void idle()
{
    render->update();
    glutPostRedisplay();
}

void display()
{
    render->drawFrame();

    glutSwapBuffers ();
    counter++;

    if (counter % 50 == 0)
    {
        float frameTime = ((float)(clock() - start) / counter) / CLOCKS_PER_SEC * 1000.0;
        float fps = 1000.0 / frameTime;
        std::cout << "FPS = " << fps << std::endl;
        counter = 0;
        start = clock();
    }


}

void reshape ( int w, int h )
{
    render->setViewportSize(w, h);
}

void key ( unsigned char key, int x, int y )
{
    if ( key == 27 )    //  quit requested
        exit ( 0 );

    // w
    if(key == 'w')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::W);
    }

    // s
    if(key == 's')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::S);
    }

    // a
    if(key == 'a')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::A);
    }

    // d
    if(key == 'd')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::D);
    }

    // q
    if(key == 'q')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::Q);
    }

    // e
    if(key == 'e')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::E);
    }

    // z
    if(key == 'z')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::Z);
    }

    // x
    if(key == 'x')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::X);
    }

    // r
    if(key == 'r')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::R);
    }

    // f
    if(key == 'f')
    {
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::F);
    }

//    std::cout << "camera: " << camera->position().x << camera->position().y << camera->position().z << std::endl;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    printf("%d, %d\n", x, y);
    std::cout << "" << std::endl;

    Vec2 normDeviceCoords(
        (float)x / WINDOW_WIDTH,
        (float)y / WINDOW_HEIGHT);

    if (state == GLUT_DOWN)
    {
        nodePicker->mouseDownUnderNearest(normDeviceCoords);
    } else if (state == GLUT_UP)
    {
        nodePicker->mouseUpUnderNearest(normDeviceCoords);
    }

    glutPostRedisplay();
}


void mouseMotion(int x, int y)
{
    Vec2 normDeviceCoords(
        (float)x / WINDOW_WIDTH,
        (float)y / WINDOW_HEIGHT);

    nodePicker->mouseMoveUnderNearest(normDeviceCoords);
    glutPostRedisplay();
}

int main ( int argc, char * argv [] )
{
    // initialize glut
    glutInit            ( &argc, argv );
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize  ( WINDOW_WIDTH, WINDOW_HEIGHT );

    // prepare context for 3.3
    glutInitContextVersion ( 3, 3 );
    glutInitContextFlags   ( GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG );
    glutInitContextProfile ( GLUT_CORE_PROFILE );

    // create window
    glutCreateWindow ( "GLUT application, which use glRender" );

    render = Render::instance();
    if (render == nullptr)
    {
        exit(3);
    }

    printf("%s\n\n", render->contextInformation());

    // register handlers
    glutDisplayFunc    ( display );
    glutReshapeFunc    ( reshape );
    glutKeyboardFunc   ( key     );
    glutMouseFunc      ( mouse   );
    glutMotionFunc     ( mouseMotion );
    glutIdleFunc       ( idle    );

    init();

    glutMainLoop ();

    return 0;
}
