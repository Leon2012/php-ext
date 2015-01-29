<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('array')) {
	dl('array.' . PHP_SHLIB_SUFFIX);
}
// $module = 'array';
// $functions = get_extension_funcs($module);
// echo "Functions available in the test extension:$br\n";
// foreach($functions as $func) {
//     echo $func."$br\n";
// }


array_greet(array("leon", "jack", "mike", "name"=>"dd"), array("hello", "key" => "value"));


?>
