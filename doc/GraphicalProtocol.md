# SERVER - GRAPHICAL CLIENT COMMUNICATION PROTOCOL

## Symbols
|Symbol|Meaning|Symbol|Meaning|
|-|-|-|-|
|X|width or horizontal position|n|player number|
|Y|height or vertical position|O|1 = N / 2 = E / 3 = S / 4 = W|
|q0|ressource 0 (food) quantity|L|player or incantantation lvl|
|q1|ressource 1 (linemate) quantity|e|egg number|
|q2|ressource 2 (deraumere) quantity|T|time unit|
|q3|ressource 3 (sibur) quantity|N|name of the team|
|q4|ressource 4 (mendiane) quantity|R|incantantation result|
|q5|ressource 5 (phiras) quantity|M|message|
|q6|ressource 6 (thystame)quantity|i|ressource number|

## Commands

| Server | Client | Details |[Comments]|
|-|-|-|-|
|msz X Y\n|msz\n|map size||
|bct X Y q0 q1 q2 q3 q4 q5 q6\n|bct X Y\n|content of a tile||
|bct X Y q0 q1 q2 q3 q4 q5 q6\n \* X \* Y|mct\n|Content of the map (all the tiles)||
|tna N\n|tna\n|Name of all the teams||
|pnw #n X Y O L N\n|-|Connection of a new player||
|pbn nb\n|pnb\n|Number of players in the game||
|pnw #n X Y O L N\n \* |pls\n|List players already in the game||
|BREF|TU|VOIS|L'IDEE|
# KEVIN FREIRE
