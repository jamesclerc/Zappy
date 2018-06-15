# SERVER - GRAPHICAL CLIENT COMMUNICATION PROTOCOL

## Symbols
|Symbol|Meaning|Symbol|Meaning|
|-|-|-|-|
|X|width or horizontal position|n|player number|
|Y|height or vertical position|O|1 = N / 2 = E / 3 = S / 4 = W|
|q0|ressource 0 (food) quantity|L|player or incantantation level|
|q1|ressource 1 (linemate) quantity|e|egg number|
|q2|ressource 2 (deraumere) quantity|T|time unit|
|q3|ressource 3 (sibur) quantity|N|name of the team|
|q4|ressource 4 (mendiane) quantity|R|incantantation result|
|q5|ressource 5 (phiras) quantity|M|message|
|q6|ressource 6 (thystame) quantity|i|ressource number|
## Commands

| Server | Client | Details |[Comments]|
|-|-|-|-|
|msz X Y\n|-|Map size|At the connection|
|bct X Y q0 q1 q2 q3 q4 q5 q6\n \* X \* Y|-|Content of the map (all the tiles)|At the connection|
|pnw n X Y O L N\n|-|Connection of a new player|At the connection and after|
|pin n q0 q1 q2 q3 q4 q5 q6\n|pin #n\n|Get player inventory||
|pnw n X Y O L N\n \* nb||List players already in the game|At the connection|
|tgt T\n|-|timer request|At the connection|
|tst T\n|tst T\n|time unit modification||
|rsp X Y i\n|-|Ressource server pop||
|pdr n i\n|-|Player drop ressource||
|pgt n i\n|-|Player get ressource||
|pet n\n|-|Player eat||
|pmf n\n|-|Player move forward||
|ptu n O\n|-|Player turn||
|pex n\n|-|Expulsion||
|pbc n M\n|-|Broadcast||
|pic n [...]\n|-|Incantation||
|pie n R\n|-|Incantation finish||
|neg X Y N e\n|-|New egg||
|heg e\n|-|Hatching egg||
|edi e\n|-|Egg death||
|pdi n\n|-|Player death||
|seg\n|-|End of game||