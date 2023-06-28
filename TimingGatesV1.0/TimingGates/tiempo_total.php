<?php
	include "conexion.php"; 

	$mysqli = new mysqli($host, $user, $pw, $db); 
	$sqltempin = "SELECT  hora_inicial, minutos_inicial, segundos_inicial, milesimas_inicial FROM sensor_inicial ";
    $restempin = $mysqli->query($sqltempin);
    $sqltempfin = "SELECT hora_final, minutos_final, segundos_final, milesimas_final  FROM sensor_final ";
    $restempfin = $mysqli->query($sqltempfin);
    
    while  ($row1 = mysqli_fetch_assoc($restempin) && $row2 = mysqli_fetch_assoc($restempfin)) {
    $reshora_total = $row1['hora_final'] - $row2['hora_inicial'];
    $resminutos_total = $row1['minutos_final'] - $row2['minutos_inicial'];
    $ressegundos_total = $row1['segundos_final'] - $row2['segundos_inicial'];
    $resmilesimas_total = $row1['milesimas_final'] - $row2['milesimas_inicial'];
    }
    $sqltemptot = "INSERT into tiempo_total (hora_total, minutos_total, segundos_total_ milesimas_total) VALUES ($reshora_total,  $resminutos_total,  $ressegundos_total, $resmilesimas_total)";
    
	echo "sqltemptot...".$sqltemptot; 
	$result1 = $mysqli->query($sqltemptot);
	echo "result es...".$result1;

?>