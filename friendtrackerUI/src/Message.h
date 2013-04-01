/*
 * Message.h
 *
 *  Created on: 2013-03-16
 *      Author: soh
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <QByteArray>
#include <QUrl>

/**
 * Abstract Message
 */
class Message
{
public:
	virtual QByteArray serialize() const = 0;
	virtual QUrl getUrl() const = 0;
	virtual ~Message() {};
};


#endif /* MESSAGE_H_ */
