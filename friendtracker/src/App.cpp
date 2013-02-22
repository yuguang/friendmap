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

#include "App.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/platform/bbm/UserProfile>
#include <bb/platform/bbm/ContactService>
#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/Contact>
#include <bb/system/SystemDialog>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QList>
#include <sstream>
#include <string>


using namespace bb::cascades;
using namespace bb::platform::bbm;
using namespace bb::system;

App::App(bb::platform::bbm::Context * ctx, QObject *parent)
    : QObject(parent)
{
	m_contextPtr = ctx;
	m_nwam = new QNetworkAccessManager(this);
	bool res = connect(m_nwam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
	Q_ASSERT(res);
	connect(m_nwam, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> &)), this, SLOT(errors(QNetworkReply*, const QList<QSslError> &)));
}

//! [0]
void App::show()
{
    QmlDocument * qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Provide access to signals, slots and properties of App to QML
    qml->setContextProperty("_app", this);

    m_root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(m_root);

    bb::platform::bbm::UserProfile up(m_contextPtr, this);
    bb::platform::bbm::ContactService cs(m_contextPtr, this);
    QList<Contact> contactList = cs.contacts();

    std::stringstream ss;
    ss << contactList.count();

    SystemDialog *ppidDialog = new SystemDialog("OK");
	ppidDialog->setTitle((std::string("YOUR PPID\n") + ss.str().c_str()).c_str());
	ppidDialog->setBody(up.ppId());
	bool res = connect(ppidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
	Q_ASSERT(res);
	ppidDialog->show();

	m_ppid = up.ppId();

	contactList.count();


	m_root->setProperty("labelText","Loading!");

	if(QNetworkReply * reply = requestApi()){
		requestFinished(reply);


	}
    // Do further initialization
    // You can use RegistrationHandler::context() now to access the bound BBM context


}
//! [0]

void App::dialogFinished(bb::system::SystemUiResult::Type value) {
	m_root->setProperty("labelText","Sent STUFF!");
}


void App::sendHttpRequest(QString url){

}

QNetworkReply *App::requestApi()
{
	m_root->setProperty("labelText","Loading.");
	// Build your JSON string as usual
	QByteArray jsonString = "{\"type\":\"RegistrationRequest\",\"ppid\":\"" + m_ppid.toLatin1() + "\"}";

	// For your "Content-Length" header
	QByteArray postDataSize = QByteArray::number(jsonString.size());

	// Time for building your request
	QUrl serviceURL("www.google.ca");
	QNetworkRequest request(serviceURL);

	// Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
	request.setRawHeader("User-Agent", "FriendTracker v0.1");
	request.setRawHeader("X-Custom-User-Agent", "FriendTracker v0.1");
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Content-Length", postDataSize);

	// Use QNetworkReply * QNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data); to send your request. Qt will rearrange everything correctly.
	m_root->setProperty("labelText","Loading...");
	connect(m_nwam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
	QNetworkReply * reply = m_nwam->get(request);
	return reply;
}

void App::requestFinished(QNetworkReply* reply){
	m_root->setProperty("labelText", "Loading....");
	if (reply->error() == QNetworkReply::NoError)
	{
		// read data from QNetworkReply here
		QByteArray bytes = reply->readAll();  // bytes
		QString sstring(bytes); // string

		m_root->setProperty("labelText", sstring);

	}else{
		// read data from QNetworkReply here
		QByteArray bytes = reply->readAll();  // bytes
		QString sstring(bytes); // string

		m_root->setProperty("labelText", sstring);
	}

}

void App::errors(QNetworkReply * reply, const QList<QSslError> & errors){
	m_root->setProperty("labelText", "ERROR");
}

