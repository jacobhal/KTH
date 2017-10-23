<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);

require 'initdb.php';
getHouses();

/**
 * Retrieve all houses
 */
function getHouses() {
	// Initiate connection
	makeDbConnection();
	global $conn;

	// Get post variables
	$sort = (isset($_POST['sort']) ? $_POST['sort'] : 'pris');
	$orderVal = (isset($_POST['order']) ? $_POST['order'] : null);
	$searchQuery = (isset($_POST['searchVal']) ? $_POST['searchVal'] : "");
	$category = (isset($_POST['cat']) ? $_POST['cat'] : "");

	$minArea = (!empty($_POST['minArea']) ? $_POST['minArea'] : 0);
	$maxArea = (!empty($_POST['maxArea']) ? $_POST['maxArea'] : PHP_INT_MAX);
	$minPrice = (!empty($_POST['minPrice']) ? $_POST['minPrice'] : 0);
	$maxPrice = (!empty($_POST['maxPrice']) ? $_POST['maxPrice'] : PHP_INT_MAX);
	$minRoom = (!empty($_POST['minRoom']) ? $_POST['minRoom'] : 0);
	$maxRoom = (!empty($_POST['maxRoom']) ? $_POST['maxRoom'] : PHP_INT_MAX);
	$minFee = (!empty($_POST['minFee']) ? $_POST['minFee'] : 0);
	$maxFee = (!empty($_POST['maxFee']) ? $_POST['maxFee'] : PHP_INT_MAX);


	// Get sort order
	$order = "ASC";
	if($orderVal == 1) {
		$order = "ASC";
	} else {
		$order = "DESC";
	}
	//$prepArr = array($category, $searchQuery, $searchQuery, $searchQuery);

	// SQL query
	$sql = "SELECT * FROM bostader 
			WHERE (lan LIKE ?) AND 
			(lan LIKE ? OR objekttyp LIKE ? OR adress LIKE ?)";

	//if(($minArea != null && $maxArea != null) && ($maxArea > $minArea)){
	    $sql .= " AND (area BETWEEN ? AND ?)";
	//}
	//if(($minPrice != null && $maxPrice != null) && ($maxPrice > $minPrice)) {
		$sql .= " AND (pris BETWEEN ? AND ?)";
	//}
	//if(($minRoom != null && $maxRoom != null) && ($maxRoom > $minRoom)) {
		$sql .=	" AND (rum BETWEEN ? AND ?)";
	//}
	//if(($minFee != null && $maxFee != null) && ($maxFee > $minFee)) {
		$sql .= " AND (avgift BETWEEN ? AND ?)";
	//}

	$sql .= " ORDER BY " . $sort . " " . $order;



	$stmt = $conn->prepare($sql); 
	$stmt->bindValue(1, "%{$category}%"	   	  , PDO::PARAM_STR);
	$stmt->bindValue(2, "%{$searchQuery}%"    , PDO::PARAM_STR);
	$stmt->bindValue(3, "%{$searchQuery}%"    , PDO::PARAM_STR);
	$stmt->bindValue(4, "%{$searchQuery}%"    , PDO::PARAM_STR);

	$stmt->bindValue(5,  $minArea , PDO::PARAM_INT);
	$stmt->bindValue(6,    $maxArea, PDO::PARAM_INT);
	$stmt->bindValue(7,  $minPrice , PDO::PARAM_INT);
	$stmt->bindValue(8,   $maxPrice , PDO::PARAM_INT);
	$stmt->bindValue(9,    $minRoom , PDO::PARAM_INT);
	$stmt->bindValue(10, $maxRoom    , PDO::PARAM_INT);
	$stmt->bindValue(11,   $minFee , PDO::PARAM_INT);
	$stmt->bindValue(12,   $maxFee  , PDO::PARAM_INT);

/*
	echo $minArea . "-" . $maxArea . "<br>";
	echo $minPrice . "-" . $maxPrice . "<br>";
	echo $minRoom . "-" . $maxRoom . "<br>";
	echo $minFee . "-" . $maxFee . "<br>";
*/
    $stmt->execute();



    // set the resulting array to associative
    $rows = $stmt->fetchAll(PDO::FETCH_ASSOC); 
    $count = $stmt->rowCount();
    $output = "";
    if($count != 0) {
	    foreach ($rows as $row) {
		    $output .= "<tr>" 
		    . "<td>" . $row['lan'] . "</td>" 
		    . "<td>" . $row['objekttyp'] . "</td>" 
		    . "<td>" . $row['adress'] . "</td>" 
		    . "<td>" . $row['area'] . "</td>" 
		    . "<td>" . $row['rum'] . "</td>" 
		    . "<td>" . $row['pris'] . "</td>" 
		    . "<td>" . $row['avgift']. "</td>" .
		    "</tr>";
		}
	} else {
		$output = ""; // <div id='nores'><h2>No results</h2></div></tr>
	}
	echo $output;
}
?>