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

UnderOverlayScene * scene;
OverlayScene * overlayScene;

NodePickerPtr nodePicker;

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
    ResourceManager * resMng = &ResourceManager::instance();

    std::pair<const char *, const char *> texturesPathes[] = {
        {"Plywood_1024x640.png", "data/Plywood_1024x640.png"},
        {"TexturesCom_BricksSmallOld0080_1_seamless_S_1024x1024.png", "data/TexturesCom_BricksSmallOld0080_1_seamless_S_1024x1024.png"}
    };

    std::pair<const char *, std::map<ShaderType, const char *>> shadersPathes[] = {
        {"coloredShP",           {{ShaderType::VertexShader, "data/colored.vertex"},           {ShaderType::FragmentShader, "data/colored.frag"}}},
        {"shader0ShP",           {{ShaderType::VertexShader, "data/shader0.vertex"},           {ShaderType::FragmentShader, "data/shader0.frag"}}},
        {"transparentPointsShP", {{ShaderType::VertexShader, "data/transparentPoints.vertex"}, {ShaderType::FragmentShader, "data/transparentPoints.frag"}}}
    };

    for (auto & i : texturesPathes)
    {
        resMng->textures().create(i.first, [&i]() {
            return createTextureFromFile(i.second);
        });
    }

    for (auto & i : shadersPathes)
    {
        resMng->shaderPrograms().create(i.first, [&i]() {
            return createShaderProgramFromFiles(i.second);
        });
    }



    camera = new PerspectiveCamera( 35.0, 16.0f/9.0f, 1.0f, 200.0f );
//    camera = new OrthographicCamera(3.0f, 16.0f / 9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());
//    camera->lookAt(Vec3(3,0,4), Vec3(-5,0,-15), Vec3::AXE_Y());

    scene = new UnderOverlayScene();
    scene->setCamera(camera);

    nodePicker = std::make_shared<NodePicker>(camera, scene);

    Render::instance()->scenes().add(scene);

    srand( time(0) );

    Node * t = new Tran();

//    Node * t1 = new Tran1();

//    Node * t2 = new Tran2();

//    scene->add(t1);

//    Node * t1 = new Tran1();
//    Node * t2 = new Tran2();
//    t1->add(t);
//    t2->add(t1);

    for (int i=0; i<30; i++)
    {
        for (int j=0; j<30; j++)
        {
            for (int k=0; k<30; k++)
            {
        //        BrickBox *bb = new BrickBox();
        //        bb->model()->setWireframeMode(false);
        //        bb->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
        //        scene->addNode(bb);
                WoodenBox * m = new WoodenBox();
        //        Mat4 mm = camera->projectionMatrix();
        //        m->m_model->m_shaderProgram->setUniform<Mat4>("projection", mm );

                m->model()->setOrigin(Vec3(((rand() % 200)) - 25, ((rand() % 200)) - 25, ((rand() % 200)) - 25));
                t->add(m);
            }
        }
    }
    scene->add(t);

    CameraControlNode * cn = new CameraControlNode(camera);

    scene->add(cn);
//    t1->add(t);
//    t2->add(t1);
//    scene->add(t2);

    overlayCamera = new OrthographicCamera(10.0f, 16.0f / 9.0f, 1.0f, 200.0f );
    overlayCamera->lookAt(Vec3(0,0,10), Vec3(0,0,-10), Vec3::AXE_Y());

    overlayScene = new OverlayScene();
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
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::W);
    }

    // s
    if(key == 's')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::S);
    }

    // a
    if(key == 'a')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::A);
    }

    // d
    if(key == 'd')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::D);
    }

    // q
    if(key == 'q')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::Q);
    }

    // e
    if(key == 'e')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::E);
    }

    // z
    if(key == 'z')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::Z);
    }

    // x
    if(key == 'x')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::X);
    }

    // r
    if(key == 'r')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::R);
    }

    // f
    if(key == 'f')
    {
        Render::instance()->processKeyboardsKeys(IKeyPressable::KeyboardKey::F);
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
