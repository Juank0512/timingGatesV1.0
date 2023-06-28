<?php
	include "conexion.php"; 

	$hora = $_GET["hora_inicio"];
    $minutos = $_GET["minutos_inicio"];
    $segundos = $_GET["segundos_inicio"];
    $tiempoCambio = $_GET["milesimas_inicio"];
    
	$mysqli = new mysqli($host, $user, $pw, $db); 
	$sql1 = "INSERT into sensor_inicial  (hora_inicio, minutos_inicio, segundos_inicio, milesimas_inicio) VALUES ('$hora', '$minutos', '$segundos', '$tiempoCambio')";

	echo "sql1...".$sql1; 
	$result1 = $mysqli->query($sql1);
	echo "result es...".$result1;

?>