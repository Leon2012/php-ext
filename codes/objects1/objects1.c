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
#include "php_objects1.h"

static zend_class_entry *hello_ce;

ZEND_BEGIN_ARG_INFO(hello___construct_arginfo, 0)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()

static PHP_METHOD(Hello, __construct) {
    char *name;
    int name_len;
    long age;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &name, &name_len, &age) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();

    zend_update_property_stringl(hello_ce, obj, "name", sizeof("name") -1, name, name_len TSRMLS_CC);//更新属性值, $this->name = name
    zend_update_property_long(hello_ce, obj, "age", sizeof("age") -1, age TSRMLS_CC); //this->age = age

}




static PHP_METHOD(Hello, updateProperties) {

    zval *obj;
    obj = getThis();

    zend_update_property_string(hello_ce, obj, "name", sizeof("name") -1, "name-update" TSRMLS_CC);//更新属性值, $this->name = name
    zend_update_property_long(hello_ce, obj, "age", sizeof("age") -1, 10 TSRMLS_CC); //this->age = age
    zend_update_property_string(hello_ce, obj, "last_name", sizeof("last_name") -1, "leon-update" TSRMLS_CC);//this->last_name = "leon"
    zend_update_property_null(hello_ce, obj, "first_name", sizeof("first_name") - 1 TSRMLS_CC); //this->first_name = null;
    zend_update_property_bool(hello_ce, obj, "sex", sizeof("sex") -1, 0 TSRMLS_CC); //this->sex = true
    zend_update_property_double(hello_ce, obj, "score", sizeof("score") -1, 15.50 TSRMLS_CC); //this->score = 12.50
}


static PHP_METHOD(Hello, addProperties) {
    zval *obj;
    obj = getThis();

    /*add zval property*/
    zval *arr;
    MAKE_STD_ZVAL(arr);
    array_init(arr);
    add_assoc_string(arr, "e", "hello", 1);
    add_index_string(arr, 1, "hello1111", 1);
    add_property_zval_ex(obj, "persons", strlen("persons")+1, arr TSRMLS_CC);
    Z_DELREF_P(arr);


    /*add double property*/
    add_property_double(obj, "d", 10.5);

    /*add bool property*/
    add_property_bool(obj, "b", 1);

    /*add string property*/
    char *str = "hello str";
    add_property_string(obj, "str", str, 1);
    
    /*add long property*/
    add_property_long(obj, "l", 12);
}


static PHP_METHOD(Hello,  __destruct) {
    php_printf("call __destruct function...\n");
}

static PHP_METHOD(Hello, __toString) {
    RETURN_STRING("Hello Class\n", 1);
}


const zend_function_entry hello_methods[] = {
	PHP_ME(Hello, __construct, hello___construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)	
    PHP_ME(Hello, __destruct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)	
    PHP_ME(Hello, __toString, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Hello, updateProperties, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Hello, addProperties, NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

zend_module_entry objects1_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"objects1", //extname
	NULL, //functions
	PHP_MINIT(objects1),
	PHP_MSHUTDOWN(objects1),
	PHP_RINIT(objects1),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(objects1),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(objects1),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_OBJECTS1_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_OBJECTS1
ZEND_GET_MODULE(objects1)
#endif


PHP_MINIT_FUNCTION(objects1)
{

    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Hello", hello_methods);

    hello_ce = zend_register_internal_class(&ce TSRMLS_CC);



    zend_declare_property_string(hello_ce, "name", sizeof("name") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_long(hello_ce, "age", sizeof("age") - 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_string(hello_ce, "last_name", sizeof("last_name") -1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(hello_ce, "first_name", sizeof("first_name") -1, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_bool(hello_ce, "sex", sizeof("sex") -1, 1, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_double(hello_ce, "score", sizeof("score") -1, 12.50, ZEND_ACC_PUBLIC TSRMLS_CC);

    // zval *arr;
    // MAKE_STD_ZVAL(arr);
    // array_init(arr);
    // add_assoc_string(arr, "e", "hello", 1);
    // zend_declare_property(hello_ce, "persons", sizeof("persons") -1, arr, ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(objects1)
{

	return SUCCESS;
}

PHP_RINIT_FUNCTION(objects1)
{
	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(objects1)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(objects1)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "objects1 support", "enabled");
	php_info_print_table_end();

}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
