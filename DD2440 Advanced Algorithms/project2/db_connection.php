<?php header("Content-type: text/xml; charset=utf-8"); ?>
<?php
    // Connect using host, username, password and databasename
    $link = mysqli_connect('localhost', 'jacobhal', 'jacobhal-xmlpub16', 'jacobhal');

    // Check connection
    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

?>