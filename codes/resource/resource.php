<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('resource')) {
	dl('resource.' . PHP_SHLIB_SUFFIX);
}

$person = person_create("leon", 35);
var_dump($person);


echo person_get_name($person)."\n";

?>
