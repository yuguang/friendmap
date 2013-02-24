// Default empty project template
#ifndef WebView_HPP_
#define WebView_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class WebView : public QObject
{
    Q_OBJECT
public:
    WebView(bb::cascades::Application *app);
    virtual ~WebView() {}
};


#endif /* WebView_HPP_ */
