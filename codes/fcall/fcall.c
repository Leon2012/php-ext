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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_fcall.h"


ZEND_BEGIN_ARG_INFO(fcall_bycallback_arginfo, 0)
    ZEND_ARG_INFO(0, cb)
ZEND_END_ARG_INFO()

PHP_FUNCTION(fcall_bycallback) {
    zend_fcall_info finfo;
    zend_fcall_info_cache fcache;

    zval **params[1];
    zval *arg, *retval = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &finfo, &fcache) == FAILURE) {
        return;
    }

    php_printf("function name : %s \n", Z_STRVAL_P(finfo.function_name));

    MAKE_STD_ZVAL(arg);//初始化arg
    ZVAL_STRING(arg,  "Hello World", 1);//付值"Hello World" 给arg
    params[0] = &arg;//填充params

    finfo.param_count = 1;
    finfo.params = params;
    finfo.retval_ptr_ptr = &retval;

    if (zend_call_function(&finfo, &fcache TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed calling callback");//输出warning信息
    }

    if (retval) {
        //RETVAL_ZVAL(retval, 1, 1);//返回值
        zval_ptr_dtor(&retval);//release返回值，函数不会有返回值
    }

    zval_ptr_dtor(&arg);//release arg


    for(int i=0; i<10; i++) {
        char str[10];
        snprintf(str, 10, "%d", i+1);

        MAKE_STD_ZVAL(arg);//初始化arg
        ZVAL_STRING(arg,  str, 1);//付值"Hello World" 给arg
        params[0] = &arg;//填充params

        finfo.param_count = 1;
        finfo.params = params;
        finfo.retval_ptr_ptr = &retval;

        if (zend_call_function(&finfo, &fcache TSRMLS_CC) == FAILURE) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed calling callback");//输出warning信息
        }

        if (retval) {
            //RETVAL_ZVAL(retval, 1, 1);//返回值
            zval_ptr_dtor(&retval);//release返回值，函数不会有返回值
        }

        zval_ptr_dtor(&arg);//release arg
    }

}



PHP_FUNCTION(fcall_byname) {
    zend_fcall_info finfo;
    zend_fcall_info_cache fcache;
    zval fname, *arg, **params[1], *retval = NULL;
    char *name = NULL;

    ZVAL_STRING(&fname, "strtolower", 0);
    if (zend_fcall_info_init(&fname, IS_CALLABLE_STRICT, &finfo, &fcache, &name, NULL TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "WTF??? Can't find the strtolower() function!");
        return;
    }

    MAKE_STD_ZVAL(arg);
    ZVAL_STRING(arg, "Hello World", 1);
    params[0] = &arg;

    finfo.param_count = 1;
    finfo.params = params;
    finfo.retval_ptr_ptr = &retval;

    if (zend_call_function(&finfo, &fcache TSRMLS_CC) == FAILURE) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed calling %s()", name);
    }
    efree(name);

    if (retval) {
        RETVAL_ZVAL(retval, 1, 1);
    }

    zval_ptr_dtor(&arg);
}

const zend_function_entry fcall_functions[] = {
	PHP_FE(fcall_byname,	NULL)		
    PHP_FE(fcall_bycallback, fcall_bycallback_arginfo)
	PHP_FE_END	
};


zend_module_entry fcall_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"fcall",
	fcall_functions,
	NULL,
	NULL,
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_FCALL_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_FCALL
ZEND_GET_MODULE(fcall)
#endif




/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
