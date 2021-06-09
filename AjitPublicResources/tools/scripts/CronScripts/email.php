<?php
require 'PHPMailer/PHPMailerAutoload.php';
 
// Script to send a mail using SMTP
// Written by : Ashfaque Ahammed

// Function to send a mail
function sendMail($to, $subject, $body, $attach)
{
	$from = " AJIT VERIFICATION <ajit_admin@iitb.ac.in>";
	//echo "sending email";
	$host = "smtp-auth.iitb.ac.in";
	$username = "ashfaque";
	$password = "ashfa 1987";

	//Create a new PHPMailer instance
	$mail = new PHPMailer();
	//Tell PHPMailer to use SMTP
	$mail->isSMTP();
	//Enable SMTP debugging
		// 0 = off (for production use)
		// 1 = client messages
		// 2 = client and server messages
	$mail->SMTPDebug = 0;
	//Ask for HTML-friendly debug output
	$mail->Debugoutput = 'html';
	//Set the hostname of the mail server
	$mail->Host = $host;
	//Set the SMTP port number - likely to be 25, 465 or 587
	$mail->Port = 25;
	//Whether to use SMTP authentication
	$mail->SMTPAuth = true;
	$mail->SMTPSecure = "tls";
	//Username to use for SMTP authentication
	$mail->Username = $username;
	//Password to use for SMTP authentication
	$mail->Password = $password;
	//Set who the message is to be sent from
	$mail->setFrom('ajit_admin@ajitrepo.in', 'AJIT - Verification');
	//Set who the message is to be sent to
	$mail->addAddress($to, '');
	//Set the subject line
	$mail->Subject = $subject;
	//Read an HTML message body from an external file, convert referenced images to embedded,
	//convert HTML into a basic plain-text alternative body
	//$mail->msgHTML(file_get_contents('contents.html'), dirname(__FILE__));
	//Replace the plain text body with one created manually
	$mail->Body = $body;
	//Attach an image file
	$mail->addAttachment($attach);

	//send the message, check for errors
	if (!$mail->send()) 
	{
		echo "PHP : Mailer Error: " . $mail->ErrorInfo ;
	}
	else
	{
		echo "PHP : Message sent!\n";
	}

}

// Obtain the message body and attachment file
$message_body = $argv[1];
$attachment = $argv[2];

sendMail("tittoambadan@gmail.com", "AJIT - Verification Log", file_get_contents($message_body),$attachment);

?>
