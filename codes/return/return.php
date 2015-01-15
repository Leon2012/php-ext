<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('return')) {
	dl('return.' . PHP_SHLIB_SUFFIX);
}
$module = 'return';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";

$func = "return_bool";
echo call_user_func($func)."\n";

$func = "return_string";
echo call_user_func($func)."\n";

$func = "return_string1";
echo call_user_func($func)."\n";

$func = "return_long";
echo call_user_func($func)."\n";

$func = "return_array";
print_r(call_user_func($func));

$func = "return_object";
print_r(call_user_func($func));

$func = "return_null";
echo (is_null(call_user_func($func))?"is null":"not null")."\n";

$func = "return_double";
echo call_user_func($func)."\n";

?>
