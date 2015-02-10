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
#include "php_resource.h"


#define PERSON_RESOURCE_TYPE "Person"
static int person_len;
typedef struct _person {
    char *name;
    int name_len;
    int age;
}person;

ZEND_BEGIN_ARG_INFO(person_create_arginfo, 0)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(person_create) {
    char *name;
    int name_len;
    long age;
    person *new_person;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &name, &name_len, &age) == FAILURE) {
        return;
    }

    new_person = emalloc(sizeof(person));
    new_person->name = estrndup(name, name_len);
    new_person->name_len = name_len;
    new_person->age = age;

    ZEND_REGISTER_RESOURCE(return_value, new_person, person_len);
    //RETURN_RESOURCE(zend_list_insert(new_person, person_len TSRMLS_CC));
}


ZEND_BEGIN_ARG_INFO(person_get_name_arginfo, 0)
  ZEND_ARG_INFO(0, person)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(person_get_name) {
    zval *zperson;
    person *p;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zperson) == FAILURE) {
        return;
    }

    ZEND_FETCH_RESOURCE(p, person*, &zperson, -1, PERSON_RESOURCE_TYPE, person_len);
    RETURN_STRING(p->name, 1);
}

ZEND_BEGIN_ARG_INFO(person_set_age_arginfo, 0)
  ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(person_set_age) {
    zval *zperson;
    person *p;
    long age;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &zperson, &age) == FAILURE) {
        return;
    }

    ZEND_FETCH_RESOURCE(p, person*, &zperson, -1, PERSON_RESOURCE_TYPE, person_len);
    p->age = age;
}



const zend_function_entry resource_functions[] = {
	PHP_FE(person_create,	person_create_arginfo)		
  PHP_FE(person_get_name, person_get_name_arginfo)
  PHP_FE(person_set_age, person_set_age_arginfo)
	PHP_FE_END	
};


zend_module_entry resource_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"resource",
	resource_functions,
	PHP_MINIT(resource),
	NULL,
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	NULL,
#if ZEND_MODULE_API_NO >= 20010901
	PHP_RESOURCE_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_RESOURCE
ZEND_GET_MODULE(resource)
#endif

/*释放person资源*/
static void person_dtor(void *pers) {
    php_printf("call person_dtor function...\n");
    person **p = (person**)pers;
    if (p && *p) {
        if ((*p)->name) {
            efree((*p)->name);
        }
        efree(*p);
    }
}


PHP_MINIT_FUNCTION(resource){   
    person_len = zend_register_list_destructors_ex(person_dtor, NULL, PERSON_RESOURCE_TYPE, module_number);
    //person_len = zend_register_list_destructors(person_dtor, NULL, module_number);

	return SUCCESS;
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
