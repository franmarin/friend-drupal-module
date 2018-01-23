<?php

define('FRIEND_DEFAULT_SITE_NAME', 'Friendliest site ever');

/**
 * Send email with the given parameters.
 *
 * @param $to
 * @param $subject
 * @param $body
 * @param @from
 * @param $cc
 * @return bool
 */
function friend_mail_send($to, $subject, $body, $from = '', $cc = '') {

    if (empty($from)) {
        $from = variable_get('site_mail');
    }

    $message = [
        'from' => $from,
        'to' => $to,
        'subject' => $subject,
        'body' => array($body),
        'headers' => array(),
    ];

    if (!empty($cc)) {
        $message['headers']['Cc'] = $cc;
    }

    return friend_mail_send_extended($message);
}

/**
 * Simple wrapper function for drupal_mail() to avoid extraneous code.
 * This should only be used for internal admin type emails.
 *
 * Based on http://www.midwesternmac.com/blogs/jeff-geerling/wrapper-function-simple
 * @param $message
 * @return bool
 */
function friend_mail_send_extended($message){

    $my_mail_token = microtime();
    $site_name = variable_get('site_name', FRIEND_DEFAULT_SITE_NAME);

    if (!isset($message['from'])) {
        $message['from'] = variable_get('site_mail');
    }

    $message['id'] = FRIEND_CONTENT_TYPE_NAME . '_' . $my_mail_token;
    $message['headers']['From'] = "{$site_name} <{$message['from']}>";
    $message['headers']['Sender'] = "{$site_name} <{$message['from']}>";
    $message['headers']['Return-Path'] = $message['from'];
    $message['headers']['Content-Type'] = 'text/plain';
    $system = drupal_mail_system(FRIEND_CONTENT_TYPE_NAME, $my_mail_token);

    $formatted_message = $system->format($message);
    $result = $system->mail($formatted_message);

    if ($result) {
        watchdog('friend', 'Email sent to !to<br/>Subject: !subject',
        array('!to' => $message['to'], '!subject' => $message['subject']));
    } else {
        watchdog('friend', 'Error sending email to: !to<br/>Subject: !subject',
        array('!to' => $message['to'], '!subject' => $message['subject']), WATCHDOG_ERROR);
    }

    return $result;
}
