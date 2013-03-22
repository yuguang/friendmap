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
#include <vector>
#include "Reply.h"

class LoginReply : public Reply
{
public:
	bool parse(const QByteArray& data);
	QString getType() const;

	QString getSessionKey() const;
	std::vector<QString> getFriends() const;

private:
	bool m_status;
	QString m_sessionKey;
	std::vector<QString> m_friends;
};

#endif /* LOGINREPLY_H_ */
