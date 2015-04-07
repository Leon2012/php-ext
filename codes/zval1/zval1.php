<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('zval1')) {
	dl('zval1.' . PHP_SHLIB_SUFFIX);
}
echo dump_zval_type("test")."\n";
echo dump_zval_type(1)."\n";
echo dump_zval_type(NULL)."\n";
echo dump_zval_type(0.5)."\n";
echo dump_zval_type(array())."\n";
echo dump_zval_type(new stdClass())."\n";

define("PI", 3.1415926);
echo dump_zval_type(constant("PI"))."\n";


echo "value:". dump_zval_value("test") . "\n";
print_r(dump_zval_value(array("arr1")));
print_r(dump_zval_value(new stdClass()));
echo "value:". dump_zval_value(1.23) . "\n";
//echo "value:". dump_zval_value(array("arr1")) . "\n";


echo convert_zval("10") . "\n";

?>
