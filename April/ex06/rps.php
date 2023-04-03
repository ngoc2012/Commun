<?php

$options = array("rock", "paper", "scissors");

// Get the user's choice
$user_choice = "";
while (!in_array($user_choice, $options)) {
    echo "Choose rock, paper, or scissors: ";
    $user_choice = strtolower(trim(fgets(STDIN)));
}

// Generate the computer's choice
$computer_choice = $options[array_rand($options)];

// Determine the winner
if ($user_choice == $computer_choice) {
    echo "It's a tie!\n";
} elseif ($user_choice == "rock" && $computer_choice == "scissors" ||
          $user_choice == "paper" && $computer_choice == "rock" ||
          $user_choice == "scissors" && $computer_choice == "paper") {
    echo "Congratulations! You won! The computer chose $computer_choice.\n";
} else {
    echo "Sorry, you lost. The computer chose $computer_choice.\n";
}

?>
