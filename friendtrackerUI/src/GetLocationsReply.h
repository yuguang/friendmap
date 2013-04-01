/*
 * GetLocationsReply.h
 *
 *  Created on: 2013-03-25
 *      Author: Sukwon Oh
 */

#ifndef GETLOCATIONSREPLY_H_
#define GETLOCATIONSREPLY_H_

#include <QString>
#include <QByteArray>
#include <QStringList>
#include "Reply.h"

struct User {
	QString ppId;
	double x;
	double y;
	int visibility;
	User()
	: x(0.0), y(0.0), visibility(1)
	{}
	User(const QString& ppId, double x, double y, int visibility)
	: ppId(ppId), x(x), y(y), visibility(visibility)
	{}
};

class GetLocationsReply : public Reply
{
public:
	GetLocationsReply();

	bool parse(const QByteArray& data);
	QString getType() const;

	QList<User> getFriends() const;

private:
	bool m_status;
	QList<User> m_friends;
};


#endif /* GETLOCATIONSREPLY_H_ */
