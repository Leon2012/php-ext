<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('globalss')) {
	dl('globalss.' . PHP_SHLIB_SUFFIX);
}

test_sapi_global();
test_zend_global();
test_php_global();
?>
