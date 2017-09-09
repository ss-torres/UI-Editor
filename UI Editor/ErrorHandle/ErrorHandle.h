#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

#include <exception>
#include <stdexcept>

namespace ExtraException
{

/*
 * 类名：unexpected_situation
 * 使用：根据设计的想法，在预料不会走到的分支，抛出这个异常
 */

class unexpected_situation : public std::logic_error
{
public:
	using _Mybase = std::logic_error;

	explicit unexpected_situation(const std::string& msg)
		: std::logic_error(msg)
	{

	}

	explicit unexpected_situation(const char* const msg)
		: std::logic_error(msg)
	{

	}
};

}


#endif	// ERROR_HANDLE_H