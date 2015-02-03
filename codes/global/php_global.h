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

#ifndef PHP_GLOBAL_H
#define PHP_GLOBAL_H

extern zend_module_entry global_module_entry;
#define phpext_global_ptr &global_module_entry

#define PHP_GLOBAL_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_GLOBAL_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GLOBAL_API __attribute__ ((visibility("default")))
#else
#	define PHP_GLOBAL_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(global);
PHP_MSHUTDOWN_FUNCTION(global);
PHP_RINIT_FUNCTION(global);
PHP_RSHUTDOWN_FUNCTION(global);
PHP_MINFO_FUNCTION(global);



ZEND_BEGIN_MODULE_GLOBALS(global)
	long  counter;
	char *name;
  int name_len;
ZEND_END_MODULE_GLOBALS(global)


#ifdef ZTS
#define GLOBAL_G(v) TSRMG(global_globals_id, zend_global_globals *, v)
#else
#define GLOBAL_G(v) (global_globals.v)
#endif

#endif	/* PHP_GLOBAL_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
