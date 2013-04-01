/*
 * UpdateLocationReply.h
 *
 *  Created on: 2013-03-16
 *      Author: Sukwon Oh
 */

#ifndef UPDATELOCATIONREPLY_H_
#define UPDATELOCATIONREPLY_H_

#include "Reply.h"
#include <QByteArray>
#include <QString>

class UpdateLocationReply : public Reply
{
	bool parse(const QByteArray &);
	QString getType() const;
};


#endif /* UPDATELOCATIONREPLY_H_ */
