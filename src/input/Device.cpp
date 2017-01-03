/*
 *  Input device
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * Copyright (C) 2016 EPAM Systems Inc.
 */

#include "Device.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Exception.hpp"

namespace Input {

/*******************************************************************************
 * Device
 ******************************************************************************/

Device::Device(const std::string& name) :
	mName(name),
	mFd(-1),
	mLog("Input")
{
	try
	{
		init();
	}
	catch(const InputException& e)
	{
		release();

		throw;
	}
}

Device::~Device()
{
	release();
}

/*******************************************************************************
 * Private
 ******************************************************************************/

void Device::init()
{
	mFd = open(mName.c_str(), O_RDONLY);

	if (mFd < 0)
	{
		if (errno == EACCES && getuid() != 0)
		{
			throw InputException("You do not have access to " + mName +
								 ". Try running as root instead.");
		}
		else
		{
			throw InputException("Can't open device " + mName +
								 ". Error: " + strerror(errno));
		}
	}

	LOG(mLog, DEBUG) << "Open device: " << mName;
}

void Device::release()
{
	if (mFd >= 0)
	{
		close(mFd);
	}

	LOG(mLog, DEBUG) << "Close device: " << mName;
}

}
