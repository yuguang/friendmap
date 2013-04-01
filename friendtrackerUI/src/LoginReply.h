/*
 * LoginReply.h
 *
 *  Created on: 2013-03-16
 *      Author: Sukwon Oh
 */

#ifndef LOGINREPLY_H_
#define LOGINREPLY_H_

#include <QString>
#include <QByteArray>
#include <QStringList>
#include "Reply.h"

class LoginReply : public Reply
{
public:
	LoginReply();

	bool parse(const QByteArray& data);
	QString getType() const;

	QString getSessionKey() const;
	QStringList getFriends() const;
	QStringList getPins() const;

private:
	bool m_status;
	QString m_sessionKey;
	QStringList m_ppIds;
	QStringList m_pins;
};

#endif /* LOGINREPLY_H_ */
