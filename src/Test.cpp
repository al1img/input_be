/*
 * Test.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: al1
 */

#include "input/Device.hpp"

using std::exception;
using Input::Device;

int main(int argc, char *argv[])
{
	try
	{
		XenBackend::Log::setLogLevel("DEBUG");

		Device kbd("/dev/input/event4");
	}
	catch(const exception& e)
	{
		LOG("Main", ERROR) << e.what();
	}
	catch(...)
	{
		LOG("Main", ERROR) << "Unknown error";
	}

	return 0;
}

