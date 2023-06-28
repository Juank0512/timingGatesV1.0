<?php
	include "conexion.php"; 

	$hora = $_GET["hora_final"];
    $minutos = $_GET["minutos_final"];
    $segundos = $_GET["segundos_final"];
    $tiempoCambio = $_GET["milesimas_final"];
    
	$mysqli = new mysqli($host, $user, $pw, $db); 
	$sql1 = "INSERT into sensor_final  (hora_final, minutos_final, segundos_final, milesimas_final) VALUES ('$hora', '$minutos', '$segundos', '$tiempoCambio')";

	echo "sql1...".$sql1; 
	$result1 = $mysqli->query($sql1);
	echo "result es...".$result1;

?>