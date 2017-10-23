<?php 
  if (!empty($_SESSION['message'])) {

    echo '<div class="alert alert-success" style="margin-top:20px">';

    // let's show our message to a user
    echo $_SESSION['message'];
    // and don't forget to erase it from session
    unset($_SESSION['message']);
    echo '</div>';
  }
  if (!empty($_SESSION['fail_message'])) {

    echo '<div class="alert alert-danger" style="margin-top:20px">';

    // let's show our message to a user
    echo $_SESSION['fail_message'];
    // and don't forget to erase it from session
    unset($_SESSION['fail_message']);
    echo '</div>';
  }
?>