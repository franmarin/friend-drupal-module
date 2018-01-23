<?php

/**
 * Script to read Friend data from a JSON file and create the corresponding
 * Drupal nodes.
 */

$json = file_get_contents(_get_module_path_file('dummy' . DIRECTORY_SEPARATOR . 'friends.dummy.json'));

foreach (drupal_json_decode($json) as $json_friend) {

    $node = new stdClass();
    $node->type = 'friend';
    $node->status = 1;
    $node->active = 1;
    $node->promote = 0;
    $node->revision = 0;
    $node->language = LANGUAGE_NONE;
    $node->title  = t($json_friend['title']);
    $node->friend_name[$node->language][]['value'] = $json_friend['friend_name'];
    $node->friend_first_name[$node->language][]['value'] = $json_friend['friend_first_name'];
    $node->friend_email[$node->language][]['value'] = $json_friend['friend_email'];
    $node->friend_birthday[$node->language][]['value'] = $json_friend['friend_birthday'];

    if ($node = node_submit($node)) {
        node_save($node);
    } else {
        var_dump($node);
    }

}
