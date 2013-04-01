/*
 * Reply.h
 *
 *  Created on: 2013-03-16
 *      Author: Sukwon Oh
 */

#ifndef REPLY_H_
#define REPLY_H_

#include <QByteArray>

class Reply
{
public:
	virtual bool parse(const QByteArray &) = 0;
	virtual QString getType() const = 0;
	virtual ~Reply() {}
};


#endif /* REPLY_H_ */
