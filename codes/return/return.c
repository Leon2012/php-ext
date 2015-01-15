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
#include "php_return.h"

//返回null
static PHP_FUNCTION(return_null) {
  RETURN_NULL();
}

//返回bool类型
static PHP_FUNCTION(return_bool) {
    RETURN_BOOL(0);
}


//返回string类型
static PHP_FUNCTION(return_string) {
  RETURN_STRING("中华人民共和国", 1);
}

//返回string类型的另一种写法
static PHP_FUNCTION(return_string1) {
  ZVAL_STRING(return_value, "Hello World", 1);
  return;
}

//返回double
static PHP_FUNCTION(return_double) {
  RETURN_DOUBLE(2.15);
}

//返回long类型
static PHP_FUNCTION(return_long) {
  RETURN_LONG(100);
}

//返回array类型
static PHP_FUNCTION(return_array) {
  zval *sub;

  //zval *return_value ，此参数已经被定义在zif函数声明里了，要操作返回值时只需要操作此值函数会自动返回这个结果出去
  array_init(return_value); // $ret = array();
  add_next_index_bool(return_value, 1); // $ret[] = true;
  add_index_string(return_value, 5, "Hello", 1); // $ret[5] = "Hello";
  add_assoc_long(return_value, "a", 42); //$ret["a"] = 42;
  add_assoc_string(return_value, "c", "d", 1); //$ret["c"] = "d"; 

  //$sub = array()
  MAKE_STD_ZVAL(sub);
  array_init(sub);

  add_assoc_double(sub, "pi", 3.1415926535); //$sub["pi"] = 3.1415926535
  add_next_index_zval(return_value, sub); //$ret[] = $sub;

}

//返回object类型
static PHP_FUNCTION(return_object) {
  object_init(return_value);//$ret = new stdClass;
  zend_update_property_double(NULL, return_value, "e", strlen("e"), 2.718281828459 TSRMLS_CC); //$ret->e = 2.718281828459
  add_property_string(return_value, "a", "hello world!", 1); //$ret->a = "hello world!";
}


//定义函数
const zend_function_entry return_functions[] = {
	PHP_FE(return_bool,	NULL)		
  PHP_FE(return_string, NULL)
  PHP_FE(return_string1, NULL)
  PHP_FE(return_long, NULL)
  PHP_FE(return_array, NULL)
  PHP_FE(return_object, NULL)
  PHP_FE(return_null, NULL)
  PHP_FE(return_double, NULL)
	PHP_FE_END	/* Must be the last line in return_functions[] */
};


//导出函数
zend_module_entry return_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"return",
	return_functions,
	NULL,
	NULL,
	NULL,		
	NULL,	
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_RETURN_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_RETURN
ZEND_GET_MODULE(return)
#endif






/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
