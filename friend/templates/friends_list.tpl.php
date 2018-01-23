<?php if (!empty($friends_list)): ?>
  <p>Friendly search result: </p>
  <table>
    <thead>
      <th>Name</th>
      <th>Email</th>
    </thead>
    <tbody>
      <?php foreach($friends_list as $friend): ?>
      <tr>
        <td>
          <a href="./node/<?php echo $friend->nid; ?>"><?php echo $friend->friend_name_value; ?></a>
        </td>
        <td>
          <?php echo $friend->friend_email_value; ?>
        </td>
      </tr>
      <?php endforeach; ?>
    </tbody>
  </table>
<?php endif; ?>
