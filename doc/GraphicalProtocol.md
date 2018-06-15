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
|nhe|Number of hatched eggs in the game|nb|Number of players in the game|
|nue|Number of unhatched eggs in the game|nic|Number of incantations underway in the game|
## Commands

| Server | Client | Details |[Comments]|Done|
|-|-|-|-|-|
|tgt T\n|-|timer info|At the connection|x|
|msz X Y\n|-|Map size|At the connection|x|
|bct X Y q0 q1 q2 q3 q4 q5 q6\n \* X \* Y|-|Content of the map (all the tiles)|At the connection (line by line, from left to right)|x|
|pnw n X Y O L N q0 q1 q2 q3 q4 q5 q6\n \* nb||List players already in the game|At the connection|x|
|neg X Y N e\n \* nb|-|List eggs already in the game|At the connection|x|
|heg e\n \* nhe|-|List hatched eggs already in the game|At the connection|x|
|pic n [...]\n * nic| - | List incantations already underway|At the connection|x|
|tst T\n|tst T\n|time unit modification||x|
|rsp X Y i\n|-|Ressource server pop|||
|pdr n i\n|-|Player drop ressource|||
|pgt n i\n|-|Player get ressource|||
|pnw n X Y O L N q0 q1 q2 q3 q4 q5 q6\n|-|Connection of a new player|||
|pet n\n|-|Player eat|||
|pmf n\n|-|Player move forward|||
|ptu n O\n|-|Player turn|||
|pex n\n|-|Expulsion|||
|pbc n M\n|-|Broadcast|||
|pic n [...]\n|-|Incantation|||
|pie n R\n|-|Incantation finish|||
|neg X Y N e\n|-|New egg|||
|heg e\n|-|Hatching egg|||
|edi e\n|-|Egg death|||
|pdi n\n|-|Player death|||
|seg\n|-|End of game|||
