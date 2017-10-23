<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);

require 'initdb.php';
newHouse();

/**
 * Create a new sale for a house
 */
function newHouse() {
	makeDbConnection();
	global $conn;
	// prepare sql and bind parameters
    $stmt = $conn->prepare("INSERT INTO bostader(lan, objekttyp, adress, area, rum, pris, avgift) 
    	VALUES (:lan, :objekttyp, :adress, :area, :rum, :pris, :avgift)");
    $stmt->bindParam(':lan', $lan);
    $stmt->bindParam(':objekttyp', $objekttyp);
    $stmt->bindParam(':adress', $adress);
    $stmt->bindParam(':area', $area);
    $stmt->bindParam(':rum', $rum);
    $stmt->bindParam(':pris', $pris);
    $stmt->bindParam(':avgift', $avgift);

    // insert a row
    $lan = "Stockholm";
    $objekttyp = "Hyresrätt";
    $adress = "Krassevägen 3";
    $area = "60";
    $rum = "4";
    $pris = "1";
    $avgift = "1";
    $stmt->execute();
}
?>