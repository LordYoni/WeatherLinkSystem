<?php
$mysqli = new mysqli('localhost', 'adminSQL', 'StationSQL', 'station');

$dataQuery = $mysqli->query("SELECT * FROM valeur_station ORDER BY id DESC LIMIT 12");
$data = $dataQuery->fetch_assoc();
echo json_encode($data);
?>