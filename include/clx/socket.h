/* ------------------------------------------------------------------------- */
/*
 *  socket.h
 *
 *  Copyright (c) 2004 - 2008, clown. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    - No names of its contributors may be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  Last-modified: Fri 07 Nov 2008 20:46:00 JST
 */
/* ------------------------------------------------------------------------- */
#ifndef CLX_SOCKET_H
#define CLX_SOCKET_H

#include "config.h"

#ifdef CLX_WIN32
#include "win32/socket.h"
#else
#include "unix/socket.h"
#endif // CLX_WIN32

#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include "shared_ptr.h"
#include "exception.h"

namespace clx {
	/* --------------------------------------------------------------------- */
	/*
	 *  basic_rawsocket
	 *
	 *  The basic_rawsocket class is the base class of other socket
	 *  classes (e.g., tcp::socket, udp::socket, ...).
	 *
	 *  Design of the class is that instances generated by using copy
	 *  constructor and/or self-assignment operator share the file
	 *  descriptor. So, one of them calles close method, other socket
	 *  instances also finish their transmission.
	 *  
	 *  If none of instances shared the same descriptor call close method,
	 *  transmission is finished when the destructor of last-destroyed
	 *  instance is called.
	 */
	/* --------------------------------------------------------------------- */
	template <
		int Type,
		int Family,
		int Protocol = 0
	>
	class basic_rawsocket {
	public:
		// constructor and destructor
		basic_rawsocket() : p_() {}
		
		basic_rawsocket(const basic_rawsocket& cp) : p_(cp.p_) {}
		
		explicit basic_rawsocket(socket_int s) : p_() {
			this->assign(s);
		}
		
		virtual ~basic_rawsocket() throw() {}
		
		basic_rawsocket& operator=(const basic_rawsocket& cp) {
			return this->assign(cp);
		}
		
		basic_rawsocket& operator=(socket_int s) {
			return this->assign(s);
		}
		
		basic_rawsocket& assign(const basic_rawsocket& cp) {
			if (cp.p_) p_ = cp.p_;
			return *this;
		}
		
		basic_rawsocket& assign(socket_int s) {
			if (static_cast<int>(s) >= 0) p_ = shared_ptr<socket_impl>(new socket_impl(s));
			return *this;
		}
		
		virtual socket_int open() {
			socket_int s = open_socket(Family, Type, Protocol);
			if (static_cast<int>(s) >= 0) p_ = shared_ptr<socket_impl>(new socket_impl(s));
			return s;
		}
		
		virtual void close() { if (p_.get() != NULL) p_->close(); }
		
		/* ----------------------------------------------------------------- */
		/*
		 *  pending
		 *
		 *  If the socket has data in the internal buffer, the pending
		 *  method returns the size of data. Note that general socket
		 *  classes return zero because they have no internal buffers.
		 */
		/* ----------------------------------------------------------------- */
		virtual int pending() const { return 0; }
		
		bool is_open() const { return (p_.get() != NULL) ? static_cast<int>(p_->socket()) >= 0 : false; }
		socket_int socket() const { return (p_.get() != NULL) ? p_->socket() : -1; }
		
	private:
		class socket_impl {
		public:
			explicit socket_impl(socket_int s) : s_(s) {}
			~socket_impl() { this->close(); }
			
			const socket_int& socket() const { return s_; }
			
			void close(){
				if (static_cast<int>(s_) >= 0) {
					close_socket(s_);
					s_ = -1;
				}
			}
			
		private:
			socket_int s_;
		};
		
		shared_ptr<socket_impl> p_;
	};
}

#endif // CLX_SOCKET_H
