<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('objects2')) {
	dl('objects2.' . PHP_SHLIB_SUFFIX);
}

$obj = new Hello("leon", 32);
echo $obj->greet();

echo $obj->var;
?>
