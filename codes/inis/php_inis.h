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

#ifndef PHP_INIS_H
#define PHP_INIS_H

extern zend_module_entry inis_module_entry;
#define phpext_inis_ptr &inis_module_entry

#define PHP_INIS_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_INIS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_INIS_API __attribute__ ((visibility("default")))
#else
#	define PHP_INIS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(inis);
PHP_MSHUTDOWN_FUNCTION(inis);
PHP_RINIT_FUNCTION(inis);
PHP_RSHUTDOWN_FUNCTION(inis);
PHP_MINFO_FUNCTION(inis);

PHP_FUNCTION(inis_report);	/* For testing, remove later. */

   
ZEND_BEGIN_MODULE_GLOBALS(inis)
	char *name;
  long level;
ZEND_END_MODULE_GLOBALS(inis)


#ifdef ZTS
#define INIS_G(v) TSRMG(inis_globals_id, zend_inis_globals *, v)
#else
#define INIS_G(v) (inis_globals.v)
#endif

#endif	/* PHP_INIS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
