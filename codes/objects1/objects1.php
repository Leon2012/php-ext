<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('objects1')) {
	dl('objects1.' . PHP_SHLIB_SUFFIX);
}


$h = new Hello("leon", 15);
print_r($h);

$h->updateProperties();
print_r($h);

$h->addProperties();
print_r($h);


echo "h:". $h;
?>
