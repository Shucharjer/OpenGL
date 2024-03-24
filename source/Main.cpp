
#include "Application.h"
#include "Logger.h"

int main()
{
    // global configuration. contains sth. about the application
    Config global_config("config/window.cfg");
    Application application(&global_config);

    application.Init();
    application.Run();

    

    
    return 0;
}
