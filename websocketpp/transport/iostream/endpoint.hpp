/*
 * Copyright (c) 2013, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef WEBSOCKETPP_TRANSPORT_IOSTREAM_HPP
#define WEBSOCKETPP_TRANSPORT_IOSTREAM_HPP

#include <websocketpp/common/memory.hpp>
#include <websocketpp/logger/levels.hpp>

#include <websocketpp/transport/iostream/connection.hpp>

#include <iostream>

namespace websocketpp {
namespace transport {
namespace iostream {

template <typename config>
class endpoint {
public:
    /// Type of this endpoint transport component
    typedef endpoint type;
    /// Type of a pointer to this endpoint transport component
    typedef lib::shared_ptr<type> ptr;
    
    /// Type of this endpoint's concurrency policy
    typedef typename config::concurrency_type concurrency_type;
    /// Type of this endpoint's error logging policy
    typedef typename config::elog_type elog_type;
    /// Type of this endpoint's access logging policy
    typedef typename config::alog_type alog_type;

    /// Type of this endpoint transport component's associated connection
    /// transport component.
	typedef iostream::connection<config> transport_con_type;
    /// Type of a shared pointer to this endpoint transport component's 
    /// associated connection transport component
    typedef typename transport_con_type::ptr transport_con_ptr;
    
	// generate and manage our own io_service
	explicit endpoint() 
	{
		std::cout << "transport::iostream::endpoint constructor" << std::endl; 
	}
	
	void register_ostream(std::ostream* o) {
        m_alog->write(log::alevel::devel,"register_ostream");
		output_stream = o;
	}
protected:
    /// Initialize logging
    /**
     * The loggers are located in the main endpoint class. As such, the 
     * transport doesn't have direct access to them. This method is called
     * by the endpoint constructor to allow shared logging from the transport
     * component. These are raw pointers to member variables of the endpoint.
     * In particular, they cannot be used in the transport constructor as they
     * haven't been constructed yet, and cannot be used in the transport 
     * destructor as they will have been destroyed by then.
     */
    void init_logging(elog_type* e, alog_type* a) {
        m_elog = e;
        m_alog = a;
    }

	void init(transport_con_ptr tcon) {
		tcon->register_ostream(output_stream);
	}
private:
	std::ostream* output_stream;
    elog_type* m_elog;
    alog_type* m_alog;
};


} // namespace iostream
} // namespace transport
} // namespace websocketpp

#endif // WEBSOCKETPP_TRANSPORT_IOSTREAM_HPP
