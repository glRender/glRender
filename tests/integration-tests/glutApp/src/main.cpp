#include <GL/freeglut.h>

#include "glRender.h"

#include "Mark.hpp"
#include "WoodenBox.hpp"
#include "BrickBox.hpp"
#include "QuadraticBezeirCurve.hpp"
#include "SinusLine.hpp"
#include "Line.hpp"

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;

using namespace glRender;

Render * render;

PerspectiveCamera * camera;

Mark * np;
Mark * fp;
Line * l;

Scene * scene;

NodePicker * nodePicker;

void init ()
{
    camera = new PerspectiveCamera( 90.0 / 180.0 * MATH_PI, 16.0f/9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());
//    camera->lookAt(Vec3(-10,0,-10), Vec3(10,0,-10), Vec3::AXE_Y());

    scene = new Scene();
    scene->setActiveCamera(camera);

    nodePicker = new NodePicker(camera, scene);

    srand( time(0) );

    Mark * m = new Mark(0,1,0,1);
    m->model()->setWireframeMode(false);
    m->setOrigin(0.0f, 0.0f, -3.0f);
    scene->addNode(m);

    for (int i=0; i<1000; i++)
    {
        if ((int)(rand() % 5) == 0)
        {
//             WoodenBox *n = new WoodenBox();
//             n->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
//             n->model()->setWireframeMode(false);
//             scene->addNode(n);
        } else
        if ((int)(rand() % 3) == 1)
        {
//             BrickBox *bb = new BrickBox();
//             bb->model()->setWireframeMode(false);
//             bb->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
//             scene->addNode(bb);
        } else
        if ((int)(rand() % 3) == 0)
        {
             Mark * m = new Mark(0,1,0,1);
             m->model()->setWireframeMode(false);
             m->setOrigin(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, 0));
             scene->addNode(m);
        }
        else
        if ((int)(rand() % 3) == 1)
        {
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
        }
        else
        if ((int)(rand() % 5) == 4)
        {
//            Vec3 p0 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
//            Vec3 p1 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
//            Vec3 p2 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));

//            float r = (rand() % 255) / 255.0;
//            float g = (rand() % 255) / 255.0;
//            float b = (rand() % 255) / 255.0;

//            QuadraticBezeirCurve * l = new QuadraticBezeirCurve(p0, p1, p2, 512, r, g, b);
//            scene->addNode(l);
        }
    }

    Vec3 p0 = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 p1 = Vec3(10.0f, 0.0f, -1.0f);

    float r = 0.0f;
    float g = 0.0f;
    float b = 1.0f;

    l = new Line(p0, p1, 1, r, g, b);
//    l->setOrigin(Vec3(0.0f, 0.0f, 0.0f));

    scene->addNode(l);

}

void idle()
{
    scene->update();
    glutPostRedisplay();
}

void display()
{
    render->draw(scene);
    glutSwapBuffers ();
}

void reshape ( int w, int h )
{
    render->setViewportSize(w, h);
}

void key ( unsigned char key, int x, int y )
{
    if ( key == 27 )    //  quit requested
        exit ( 0 );

    float cameraMoveSpeed = 0.3f;
    float cameraRotationSpeed = 5.0f;

    // w
    if(key == 'w')
    {
        camera->setPosition( camera->position() + camera->front() * cameraMoveSpeed );
        std::cout << "w" << std::endl;

    }

    // s
    if(key == 's')
    {
        camera->setPosition( camera->position() - camera->front() * cameraMoveSpeed );
        std::cout << "s" << std::endl;
    }

    // a
    if(key == 'a')
    {
        camera->setPosition( camera->position() - camera->right() * cameraMoveSpeed );
        std::cout << "a" << std::endl;
    }

    // d
    if(key == 'd')
    {
        camera->setPosition( camera->position() + camera->right() * cameraMoveSpeed );
        std::cout << "d" << std::endl;
    }

    // q
    if(key == 'q')
    {
        camera->setEulerAngles( camera->pitch(), camera->yaw() + cameraRotationSpeed, camera->roll() );
        std::cout << 'q' << std::endl;
    }

    // e
    if(key == 'e')
    {
        camera->setEulerAngles( camera->pitch(), camera->yaw() - cameraRotationSpeed, camera->roll() );
        std::cout << "e" << std::endl;
    }

    std::cout << "camera: " << camera->position().x << camera->position().y << camera->position().z << std::endl;

    glutPostRedisplay();
}

float distance = 0;
Node * pressedNode = nullptr;

void mouse(int button, int state, int x, int y)
{
    printf("%d, %d\n", x, y);
    std::cout << "" << std::endl;

    Vec2 normDeviceCoords(
        2.0f * (float)x / WINDOW_WIDTH - 1.0f,
        1.0f - 2.0f * (float)y / WINDOW_HEIGHT );

    Ray * ray = nodePicker->ray(normDeviceCoords);

//    AbstractBuffer * b = l->model()->geometry()->get("vertex");
//    Buffer<Vec3> * a = dynamic_cast<Buffer<Vec3> *>(b);
//    a->rewrite(0, ray->origin());
//    a->rewrite(1, ray->target());

    scene->traverse([ray, normDeviceCoords](Node * node) {
        if (node->isSelectable())
        {
            if (node->bb()->intersects(ray))
            {
                Mark * mark = dynamic_cast<Mark *>(node);
                if (mark != nullptr)
                {
                    mark->changeColor();
                }

                Vec3 n = camera->front();
                Vec3 M1 = camera->position();
                Vec3 M2 = mark->model()->origin();

                float D1 = -(n.x*M1.x + n.y*M1.y + n.z*M1.z);
                float D2 = -(n.x*M2.x + n.y*M2.y + n.z*M2.z);

                float top = fabs(D2-D1);
                float bottom = sqrt( pow(n.x, 2) +
                                     pow(n.y, 2) +
                                     pow(n.z, 2) );

                distance = top / bottom;
                pressedNode = node;

                std::cout << "Has intersection!" << std::endl;
                printf("The distance to plane: %f\n", distance);
                std::cout << "" << std::endl;
            }
        }
    });

    delete ray;

    glutPostRedisplay();
}


void mouseMotion(int x, int y)
{
    if (pressedNode != nullptr)
    {
        Vec2 normDeviceCoords(
            2.0f * (float)x / WINDOW_WIDTH - 1.0f,
            1.0f - 2.0f * (float)y / WINDOW_HEIGHT );

        Vec3 newPos = nodePicker->coordOnDistance(normDeviceCoords, distance);
        pressedNode->setOrigin(newPos);

        printf("New position: %f, %f, %f\n", newPos.x, newPos.y, newPos.z);
        std::cout << "" << std::endl;
    }

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
