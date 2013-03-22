// Navigation pane project template
#include "FriendtrackerUI.hpp"

#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>

#include "WebMaps.hpp"
#include "RegistrationHandler.hpp"
#include "ServerInterface.h"
#include "LoginMessage.h"

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    // this is where the server is started etc
    Application app(argc, argv);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "friendtrackerUI_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    const QString uuid(QLatin1String("4cd89845-5af7-4432-816e-31afb7b7f824"));

    // create the application pane object to init UI etc.
    FriendtrackerUI* ui = new FriendtrackerUI(&app, uuid);
    Q_UNUSED(ui);

    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
