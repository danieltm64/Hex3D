#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#endif

#include <hex3d/application.hpp>

int main(int argc, char* argv[])
{
    hex3d::application app("data/demo_scene1.xml");

    return app.run();
}
