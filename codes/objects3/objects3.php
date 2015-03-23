<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('objects3')) {
	dl('objects3.' . PHP_SHLIB_SUFFIX);
}


$obj = new Hello("leon", 32);
//var_dump($obj);
$obj->foo = "bar";
//var_dump($obj);


//echo "obj: "; 
//$obj->greet();
//echo $obj."_abc";
//echo "obj count:" . count($obj)."\n";


$obj1 = clone $obj;
// echo "obj1: ";
// $obj1->greet();


//var_dump($obj1);

$obj2 = new Hello("jacky", 30);

echo "compare:".bool2str($obj == $obj2)."\n";


function bool2str($bool){
    if ($bool === false) {
        return 'FALSE';
    } else {
        return 'TRUE';
    }
}
?>
