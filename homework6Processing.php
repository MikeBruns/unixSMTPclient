<html>
<body>
<?php

/* Values from yourHomework6.php */
$domainValue = $_POST['domain'];
$fromValue = $_POST['fromEmail'];
$sbjValue = $_POST['subject'];
$msgValue = $_POST['message'];
$toValue = $_POST['toEmail'];

/* Spits out info entered in previous form */
echo "Information you entered... <br><br>";

echo "Domain: " . $domainValue . "<br><br>";
echo "To: " . $toValue . "<br><br>";
echo "From: " . $fromValue . "<br><br>";
echo "Subject: " . $sbjValue . "<br><br>";
echo "Message: " . $msgValue . "<br><br>";

/* Putting together the command to run in cmd line w/form values */
$cmdToRun = "/home/classes/cs3270rk/lib/hw5ExecutableKresmans " . $domainValue . " ". $fromValue . " ".
 $toValue . " \"" .  $sbjValue . "\" \"" . $msgValue . "\"";

echo "Command to run in voyager: " . $cmdToRun . "<br><br><br><br>";

/* Run the command & print it */
$out = shell_exec("$cmdToRun"); 
echo "<pre>$out</pre><br><br><br>";

/* Output the code with tags */
echo "<xmp>";
$echoForm = file_get_contents('homework6.php');
        echo $echoForm;

echo "<xmp>";
$echoFormProcesser = file_get_contents('homework6Processing.php');
        echo $echoFormProcesser;


?>