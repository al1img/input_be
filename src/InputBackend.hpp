/*
 *  Input backend
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

#ifndef INPUTBACKEND_HPP_
#define INPUTBACKEND_HPP_

#include <xen/be/BackendBase.hpp>
#include <xen/be/FrontendHandlerBase.hpp>
#include <xen/be/RingBufferBase.hpp>
#include <xen/be/Log.hpp>

#include <xen/io/kbdif.h>

/***************************************************************************//**
 * @defgroup input_be Input backend
 * Backend related classes.
 ******************************************************************************/

/***************************************************************************//**
 * Ring buffer used to send events to the frontend.
 * @ingroup input_be
 ******************************************************************************/
class EventRingBuffer : public XenBackend::RingBufferOutBase<xenkbd_page,
															 xenkbd_in_event>
{
public:
	/**
	 * @param domId     frontend domain id
	 * @param port      event channel port number
	 * @param ref       grant table reference
	 * @param offset    start of the ring buffer inside the page
	 * @param size      size of the ring buffer
	 */
	EventRingBuffer(int domId, int port, int ref, int offset, size_t size) :
		RingBufferOutBase<xenkbd_page, xenkbd_in_event>(domId, port, ref,
														offset, size)
		{}
};

/***************************************************************************//**
 * Input frontend handler.
 * @ingroup input_be
 ******************************************************************************/
class InputFrontendHandler : public XenBackend::FrontendHandlerBase
{
public:

	/**
	 * @param domId     frontend domain id
	 * @param backend   backend instance
	 * @param id        frontend instance id
	 */
	InputFrontendHandler(int domId, XenBackend::BackendBase& backend, int id) :
		FrontendHandlerBase(domId, backend, id),
		mLog("InputFrontend") {}

protected:

	/**
	 * Is called on connected state when ring buffers binding is required.
	 */
	void onBind();

private:
	XenBackend::Log mLog;
};

/***************************************************************************//**
 * Input backend class.
 * @ingroup input_be
 ******************************************************************************/
class InputBackend : public XenBackend::BackendBase
{
public:
	/**
	 * @param domId         domain id
	 * @param deviceName    device name
	 * @param id            instance id
	 */
	InputBackend(int domId, const std::string& deviceName, int id) :
		BackendBase(domId, deviceName, id) {}

protected:

	/**
	 * Is called when new input frontend appears.
	 * @param domId domain id
	 * @param id    instance id
	 */
	void onNewFrontend(int domId, int id);
};

#endif /* INPUTBACKEND_HPP_ */
