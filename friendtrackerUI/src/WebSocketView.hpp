/*
 * WebSocketView.hpp
 *
 *  Created on: 2013-03-29
 *      Author: Sukwon Oh
 */

#ifndef WEBSOCKETVIEW_HPP_
#define WEBSOCKETVIEW_HPP_

#include <QObject>
#include <QString>

class WebSocketView : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString pageContent READ pageContent)

public:
	WebSocketView(QObject* parent = 0);

	QString pageContent() const;
};


#endif /* WEBSOCKETVIEW_HPP_ */
