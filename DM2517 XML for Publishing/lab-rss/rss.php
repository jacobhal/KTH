<?php header("Content-type: text/xml; charset=utf-8"); ?>
<?xml version="1.0" encoding="UTF-8"?>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns="http://purl.org/rss/1.0/" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:syn="http://purl.org/rss/1.0/modules/syndication/">
<?php
    // Connect using host, username, password and databasename
    $link = mysqli_connect('localhost', 'rsslab', 'rsslab', 'rsslab');

    // Check connection
    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

    // The SQL query
    $query = "SELECT link, title, description, creator, feeddate
            FROM exjobbsfeed
            ORDER BY title DESC";

    // Execute the first query
    if (($result = mysqli_query($link, $query)) === false) {
       printf("Query failed: %s<br />\n%s", $query, mysqli_error($link));
       exit();
    }

    // The SQL query
    $query = "SELECT link FROM exjobbsfeed";
    
    // Execute the second query
    if (($result2 = mysqli_query($link, $query)) === false) {
       printf("Query failed: %s<br />\n%s", $query, mysqli_error($link));
       exit();
    }

    $returnstring = '<channel rdf:about="' . 'http://www.nada.kth.se/media/Theses/' . '">';
    
    $returnstring .= '<title>Examensarbeten medieteknik</title>';
    $returnstring .= '<link>http://www.nada.kth.se/media/Theses/</link>';
    $returnstring .= '<description>Examensarbeten inom medieteknik.</description>';
    $returnstring .= '<dc:language>sv</dc:language><dc:rights>Copyright KTH/Nada/Media</dc:rights>';
    

    // Generate date
    date_default_timezone_set('Europe/Stockholm');
    $date = date('Y-m-d\TH:i:sP');
    $returnstring .= '<dc:date>' . $date . '</dc:date>';


    $returnstring .= '<dc:publisher>KTH/Nada/Media</dc:publisher>
    <dc:creator>bjornh@kth.se</dc:creator>
    <syn:updatePeriod>daily</syn:updatePeriod>
    <syn:updateFrequency>1</syn:updateFrequency>
    <syn:updateBase>2006-01-01T00:00+00:00</syn:updateBase>';
    

    $returnstring .= '<items><rdf:Seq>';

    // Fill rdf:Seq
    while ($line = $result2->fetch_object()) {
        $link = $line->link;
        $link = str_replace(' ', '%20', $link);
        $returnstring .= '<rdf:li rdf:resource="' . $link . '"/>';
    }
    $returnstring .= '</rdf:Seq></items>';

    $returnstring .= '<image rdf:resource="http://www.nada.kth.se/media/images/kth.png"/></channel>';

    // Loop over the resulting lines
    while ($line = $result->fetch_object()) {
        // Store results from each row in variables
        $link = $line->link;
        $title = $line->title;
        $description = $line->description;
        $creator = $line->creator;
        $feeddate = $line->feeddate;

        $link = str_replace(' ', '%20', $link);


        // Store the result we want by appending strings to the variable $returnstring
       
       
        $returnstring .= '<item rdf:about="' . $link . '">';
        $returnstring .= '<title>' . $title . '</title>';
        $returnstring .= "<link>$link</link>";
        $returnstring .= "<description>$description</description>";
        $returnstring .= "<dc:creator>$creator</dc:creator>";

        $date = strtotime($feeddate);
        $returnstring .= '<dc:date>' . date('Y-m-d\TH:i:sP', $date) . '</dc:date>';
        $returnstring .= "</item>";
        
    }
    $returnstring .= '</rdf:RDF>';
    $returnstring = str_replace('&', '&amp;', $returnstring);

    // Free result and just in case encode result to utf8 before returning
    mysqli_free_result($result);
    print utf8_encode($returnstring);
?>