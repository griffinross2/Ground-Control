#include "application.h"

#include "main_window.h"
#include "debug_overlay.h"

int main(int argc, char** argv) {
    int ret;

    Application app;

    ret = app.Init();
    if (ret != 0) {
        return ret;
    }
    app.PushLayer<MainWindow>();
    app.PushLayer<DebugOverlay>();

    ret = app.Run();
    app.Shutdown();

    return ret;
}
