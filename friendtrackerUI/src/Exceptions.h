/*
 * Exceptions.h
 *
 *  Created on: 2013-03-28
 *      Author: Sukwon Oh
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class InitializationException : public std::exception
{
public:
	InitializationException()
	: std::exception()
	{}

	InitializationException(const std::string& msg)
	: std::exception()
	, msg(msg)
	{}

	const char* what() const throw() {
		return msg.c_str();
	}
private:
	std::string msg;
};

class ScaleImageException : public std::exception
{
public:
	ScaleImageException()
	: std::exception()
	{}

	ScaleImageException(const std::string& msg)
	: std::exception()
	, msg(msg)
	{}

	const char* what() const throw() {
		return msg.c_str();
	}
private:
	std::string msg;
};

class WebSocketInitException : public std::exception
{
public:
	WebSocketInitException()
	: std::exception()
	{}

	WebSocketInitException(const std::string& msg)
	: std::exception()
	, msg(msg)
	{}

	const char* what() const throw() {
		return msg.c_str();
	}
private:
	std::string msg;
};

#endif /* EXCEPTIONS_H_ */
