/*
 * LoginReply.h
 *
 *  Created on: 2013-03-16
 *      Author: soh
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

private:
	bool m_status;
	QString m_sessionKey;
	QStringList m_ppIds;
};

#endif /* LOGINREPLY_H_ */
