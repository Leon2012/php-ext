/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_FCALL_H
#define PHP_FCALL_H

extern zend_module_entry fcall_module_entry;
#define phpext_fcall_ptr &fcall_module_entry

#define PHP_FCALL_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_FCALL_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_FCALL_API __attribute__ ((visibility("default")))
#else
#	define PHP_FCALL_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif


PHP_FUNCTION(fcall_byname);	
PHP_FUNCTION(fcall_bycallback);



#ifdef ZTS
#define FCALL_G(v) TSRMG(fcall_globals_id, zend_fcall_globals *, v)
#else
#define FCALL_G(v) (fcall_globals.v)
#endif

#endif	/* PHP_FCALL_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
