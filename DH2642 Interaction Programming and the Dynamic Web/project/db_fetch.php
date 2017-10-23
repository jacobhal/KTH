<?php
session_start();
ini_set('display_errors', 1);
error_reporting(E_ALL);

require 'initdb.php';

makeDbConnection();
global $conn;

$isSearching = false;
$sql = "SELECT * FROM courses WHERE user_id=?";
if (isset($_GET['search']) && $_GET['search'] != "") {
    $sql = $sql . " AND coursecode LIKE ? OR year LIKE ? OR name LIKE ?";
    $isSearching = true;
    $searchTerm = '%' . $_GET['search'] . '%';
}

if (isset($_GET['sortBy'])) {
    $sql = $sql . " ORDER BY " . $_GET['sortBy'];
}
$stmt = $conn->prepare($sql);
if ($isSearching) {
	$stmt->bind_param('dsss',$_SESSION['login_user'], $searchTerm, $searchTerm, $searchTerm);
}

$xml = new SimpleXMLElement("<CourseList/>");
if ($stmt->execute()) {
    $result = $stmt->get_result();
    while ($row = $result->fetch_assoc()) {

        // One course
        $course = $xml->addChild('Course');
        $course->addAttribute('id', $row['coursecode']);
        // Name tag
        $name = $course->addChild('Name', $row['name']);
        // Link tag
        $link = $course->addChild('Link', $row['link']);
        // Year tag
        $year = $course->addChild('Year', $row['year']);
        // Periods tag
        $periods = $course->addChild('Periods');
        // The four period tags
        $period1 = $periods->addChild('P1', $row['p1']);
        $period2 = $periods->addChild('P2', $row['p2']);
        $period3 = $periods->addChild('P3', $row['p3']);
        $period4 = $periods->addChild('P4', $row['p4']);
        
    }

    $xslDoc = new DOMDocument();
    $xslDoc->load("courseListStyle.xsl");

    $xslTransformer = new XSLTProcessor();
    $error1 = $xslTransformer->importStyleSheet($xslDoc);
    if (!$error1) {
        echo "failed to load stylesheet";
    }

    $error2 = $xslTransformer->transformToXML($xml);
    if (!$error2) {
        echo "Could not perform XSLT, refresh please.";
    } else {
        echo $error2;
    }

    /* free result set */
    $result->close();
}
?>