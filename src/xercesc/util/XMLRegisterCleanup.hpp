/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 1999-2000 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id$
 * $Log$
 * Revision 1.4  2004/02/24 22:57:28  peiyongz
 * XercesDeprecatedDOMLib
 *
 * Revision 1.3  2004/01/29 11:48:47  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.2  2002/11/04 15:22:05  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:15  peiyongz
 * sane_include
 *
 * Revision 1.4  2001/10/25 21:55:29  peiyongz
 * copy ctor explicity declared private to prevent supprise.
 *
 * Revision 1.3  2001/10/24 18:13:06  peiyongz
 * CVS tag added
 *
 *
 */

#if !defined(XMLREGISTERCLEANUP_HPP)
#define XMLREGISTERCLEANUP_HPP

#include <xercesc/util/Mutexes.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  For internal use only.
//
//  This class is used by the platform utilities class to support
//  reinitialisation of global/static data which is lazily created.
//  Since that data is widely spread out the platform utilities
//  class cannot know about them directly. So, the code that creates such
//  objects creates an registers a cleanup for the object. The platform
//  termination call will iterate the list and delete the objects.
//
//  N.B. These objects need to be statically allocated.  I couldn't think
//  of a neat way of ensuring this - can anyone else?

class XMLUTIL_EXPORT XMLRegisterCleanup
{
public :
	// The cleanup function to be called on XMLPlatformUtils::Terminate()
	typedef void (*XMLCleanupFn)();
	
	void doCleanup(); 

	// This function is called during initialisation of static data to
	// register a function to be called on XMLPlatformUtils::Terminate.
	// It gives an object that uses static data an opportunity to reset
	// such data.
	void registerCleanup(XMLCleanupFn cleanupFn);

	// This function can be called either from XMLPlatformUtils::Terminate
	// to state that the cleanup has been performed and should not be
	// performed again, or from code that you have written that determines
	// that cleanup is no longer necessary.
	void unregisterCleanup();

	// The default constructor sets a state that ensures that this object
	// will do nothing
	XMLRegisterCleanup();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
	XMLRegisterCleanup(const XMLRegisterCleanup&);
    XMLRegisterCleanup& operator=(const XMLRegisterCleanup&);

	// This is the cleanup function to be called
	XMLCleanupFn m_cleanupFn;

	// These are list pointers to the next/prev cleanup function to be called
	XMLRegisterCleanup *m_nextCleanup, *m_prevCleanup;

	// This function reinitialises the object to the default state
	void resetCleanup();
};

XERCES_CPP_NAMESPACE_END

#endif
