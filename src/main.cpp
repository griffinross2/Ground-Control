#include "application.h"

#include "bluetooth_layer.h"
#include "debug_layer.h"

int main(int argc, char** argv) {
    int ret;

    Application app;

    ret = app.Init();
    if (ret != 0) {
        return ret;
    }

    app.PushLayer<DebugLayer>();
    app.PushLayer<BluetoothLayer>();

    ret = app.Run();
    app.Shutdown();

    return ret;
}

