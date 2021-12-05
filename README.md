<h1 align="center">Welcome to ESE224 Final Project 👋</h1>
<p>
</p>

> The user will be playing a Text-Based Adventure Game. They will have to go through 4 different floors and defeat the main boss of each to move forward.

## Author

👤 **Noam Cicurel, Emily Zheng, and Ashley Marie Estrada**


## Main File

>Here we have the main function that will have an infinite loop using a switch to see what the program will do. By default the switch is given a value so it can enter the main menu to start the game. Once there, the user has many choices to go through: Check the scoreboard, view the avg score. create a new game, load a new game or quit the game entirely. When creating a new game we have a password radomly generated for the player to use if they ever choose o return to their current game.

## Player Class

> When the player enters a new floor, a weapon list will be generated and it will update at each new floor. It's default stats are as follows: Max health-25, Current Health- 25, Attack damage-0, and Currency-0. It will have functions to print their weapons, to attack the enemy, to get and set their name, health attack, password, difficulty, score, currency, to buy a weapon, and to print all of the player's information.

## Enemy Class

> An enemy will appear at every floor, but there will also be smaller enemies the player can fight to gain extra currency or to complete side quests. A defualt enemy is as follows: Max health-10, Current Health- 10, Attack damage-1, and Currency-1. The class will also have functions that sets and gets an enemy's name, helath, damage, level, and currency, and to modify its health and damage.

## Weapon Class
> The player will have the option to purchase a weapon on each floor to help them defeat the main enemy of the floor. A default weapon is the player's fist and its attack damage is 5, and the price is 0. This file will get and set the weapon's amount, damage, cost, and name.

##ScoreNode Class
> This class will keep track of the players score 
