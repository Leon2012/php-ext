<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('objects3')) {
	dl('objects3.' . PHP_SHLIB_SUFFIX);
}


$obj = new Hello("leon", 32);
//var_dump($obj);

echo "obj: "; 
$obj->greet();
//echo $obj."_abc";
//echo "obj count:" . count($obj)."\n";


$obj1 = clone $obj;
echo "obj1: ";
$obj1->greet();


//var_dump($obj1);

?>
