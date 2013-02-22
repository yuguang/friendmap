/* Copyright (c) 2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef APP_HPP
#define APP_HPP

#include <QtCore/QObject>
#include <bb/cascades/AbstractPane>
#include <bb/platform/bbm/UserProfile>
#include <bb/platform/bbm/Context>
#include <bb/system/SystemUiResult>
#include <bb/system/SystemDialog>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
/**
 * The main business logic object in the application.
 *
 * This object normally provides signals, slots and properties
 * that are accessed by the main page of the application's UI.
 */
//! [0]
class App : public QObject
{
    Q_OBJECT

    // Add your Q_PROPERTY declarations here.

public:
    App(bb::platform::bbm::Context * ctx = 0, QObject *parent = 0);


private:
    bb::platform::bbm::Context * m_contextPtr;
    void sendHttpRequest(QString url);
    QNetworkReply * requestApi();
    bb::cascades::AbstractPane *m_root;
    QString m_ppid;
    QNetworkAccessManager * m_nwam;

public Q_SLOTS:
    void show();

private Q_SLOTS:
    void dialogFinished(bb::system::SystemUiResult::Type value);
    void requestFinished(QNetworkReply* reply);
    // Add your slot declarations here.
    void errors(QNetworkReply* reply, const QList<QSslError> & errors);

Q_SIGNALS:
	void bob();
    // Add your signal declarations here.
};
//! [0]

#endif
