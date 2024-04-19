#include "App.h"

int main()
{
    App& app = App::instance();

    app.InitApp();
    app.RunApp();

    return 0;
}
