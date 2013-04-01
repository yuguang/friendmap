/*
 * WebSocketView.cpp
 *
 *  Created on: 2013-03-29
 *      Author: soh
 */

#include "WebSocketView.hpp"
#include "Exceptions.h"

#include <QFile>

WebSocketView::WebSocketView(QObject* parent)
: QObject(parent)
{

}

QString WebSocketView::pageContent() const
{
	QFile file("app/native/assets/websocket.html");
	if (!file.open(QIODevice::ReadOnly)) {
		throw WebSocketInitException();
	}

	QByteArray content = file.readAll();
	return QString::fromUtf8(content);
}
