<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);

require 'initdb.php';
getCourses();


function getCourses() {
	makeDbConnection();
	global $conn;
   
    // SQL query
    $sql = "SELECT * FROM courses";
    $xml = new SimpleXMLElement("<CourseList/>");
    
    if ($result = $conn->query($sql)) {
        // fetch object array
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {

            // One course
            $course = $xml->addChild('Course');
            $course->addAttribute('id', $row['coursecode']);
            // Name tag
            $name = $course->addChild('Name', $row['name']);
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
        $xslDoc->load("excelStylesheet.xsl");

        $xslTransformer = new XSLTProcessor();
        $error1 = $xslTransformer->importStyleSheet($xslDoc);
        if (!$error1) {
            echo "failed to load stylesheet";
        }

        $error2 = $xslTransformer->transformToURI($xml, 'file:///Applications/MAMP/htdocs/project/tmp/courses.xml');
        if (!$error2 || $error2 == 0) {
            echo "Could not perform XSLT, refresh please.";
        }

        /* free result set */
        $result->close();
        // Prompt the user to download the Excel file
        header('Content-Type: text/xml');
        header('Content-Disposition: attachment; filename="YourCourses.xml"');
        readfile('tmp/courses.xml');
        exit;
    }
}
?>