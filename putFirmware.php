<?php
/** Spark RGB Library Firmware Flaher
 *
 * Description Uses the Spark Cloud API to send firmware to a 
 * Spark Core designated by a device id and using a given 
 * accessToken
 *
 * Usage: Issue a GET request to putFirmware.php with parameters
 * "accessToken" and "deviceID". 
 * Example url: http://example.com/putFirmware?accessToken=X&deviceID=Y
 *
 * Author: Harrison H. Jones (harrison@hhj.me)
 *
 * Date: Jan 27, 2015
 *
 * Git Url: https://github.com/harrisonhjones/RGBEffect
 **/

// Grab the access token and device ID from the GET request 
$accessToken = $_GET['accessToken'];
$deviceID = $_GET['deviceID'];

// Construct the URL for the Spark Cloud API
$url = "https://api.spark.io/v1/devices/" . $deviceID . "?access_token=" . $accessToken;

// Initialize curl and grab a session for later interaction
$request = curl_init($url);

// Set the required curl options to PUT the file to the Spark Cloud endpoint
curl_setopt($request, CURLOPT_POST, true);
curl_setopt(
    $request,
    CURLOPT_POSTFIELDS,
    array(
      'file' => '@' . realpath('rgbAPI.bin')
    ));
curl_setopt($request, CURLOPT_CUSTOMREQUEST, "PUT");
curl_setopt($request, CURLOPT_RETURNTRANSFER, true);

// Output the response from the Spark Cloud
echo curl_exec($request);

// Close the curl session
curl_close($request);
?>