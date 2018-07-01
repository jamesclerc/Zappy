
from enum import Enum
import sys
import json
from math import sqrt


ressources = ["linemate", "deraumere", "sibur",
              "mendiane", "phiras", "thystame"]
MAX_LEVEL = 8


class Direction(Enum):
    def __lt__(self, b):
        print("Direction __lt__: self:", self, "| b:", b)
        if isinstance(b, Direction):
            b = b.value
        if b == 0:
            ret = self.value == 1
        elif b == 1:
            ret = self.value == 2
        elif b == 2:
            ret = self.value == 3
        else:
            ret = self.value == 0
        print(ret)
        return ret

    def __gt__(self, b):
        return ((self == 3 and b == 0) or
                (self + 1 == b))

    def __add__(self, b):
        if isinstance(b, int):
            val = self.value + b
            if val < 0:
                val = 3
            val = val % 4
            if val == 0:
                ret = Direction.NORTH
            elif val == 1:
                ret = Direction.WEST
            elif val == 2:
                ret = Direction.SOUTH
            else:
                ret = Direction.EAST
            return ret

    NORTH = 0
    WEST = 1
    SOUTH = 2
    EAST = 3


class Player:

    conn = None
    team = None
    id = None
    size_map = None
    inventory = [0] * 6
    direction = Direction.NORTH
    level = 1
    last_action = None
    last_action_succeded = False
    last_look = None
    is_ejected = False
    is_ejected_from = 0
    next_target = None
    elevating = False
    drop_ressources = False
    turn_around = 0
    move_n_case = 0
    msg_received = []
    go_to_incantation = None
    friends_incantation = []
    moving_to_incantation = False
    asking_lvl_up = False
    arrived = False
    tmp = 0
    moving_action = False
    random_dir = None

    def __init__(self, conn, team):
        self.conn = conn
        self.team = team
        self.actions = {"move_forward": self.move_forward,
                        "turn_left": self.turn_left,
                        "turn_right": self.turn_right,
                        "get_inventory": self.get_inventory,
                        "look_around": self.look_around,
                        "broadcast": self.broadcast,
                        "get_unused_slots": self.get_unused_slots,
                        "eject": self.eject,
                        "take_object": self.take_object,
                        "drop_object": self.drop_object,
                        "start_incantation": self.start_incantation,
                        "do_nothing": self.do_nothing,
                        "send_message": self.send_message,
                        "fork": self.fork,
                        }

    def __del__(self):
        pass

    def connect(self):
        buffer = self.conn.next()
        if buffer != "WELCOME":
            sys.stderr.write("Error: Wrong welcoming message\n")
            sys.exit(84)
        self.conn.send(self.team)
        self.id = int(self.conn.next())
        self.size_map = self.conn.next().split(" ")

    def __repr__(self):
        return "Player:\n\tid: " + str(self.id) + "\n\tteam: " + self.team

    def has_ressources_needed(self):
        r_needed = self.ressources_needed()
        for i, nb in enumerate(r_needed):
            if self.inventory[i] < nb:
                return False
        return True

    def ressources_needed(self):
        ressources_needed = [[1, 0, 0, 0, 0, 0],
                             [1, 1, 1, 0, 0, 0],
                             [2, 0, 1, 0, 2, 0],
                             [1, 1, 2, 0, 1, 0],
                             [1, 2, 1, 3, 0, 0],
                             [1, 2, 3, 0, 1, 0],
                             [2, 2, 2, 2, 2, 1]]
        return ressources_needed[self.level - 1]

    def get_nb_players_needed(self):
        nb_players_needed = [1, 2, 2, 4, 4, 6, 6]
        return nb_players_needed[self.level - 1]

    def get_inventory(self, response=False):
        print("get_inventory(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "get_inventory"
            self.conn.send("Inventory")
        else:
            for i, res in enumerate(response[1:-1].split(",")[1:]):
                res = res.split(" ")
                res.remove("")
                self.inventory[i] = int(res[1])
            self.last_action_succeded = True
            print("Inventory:", self.inventory)

    def look_around(self, response=False):
        print("look_around(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "look_around"
            self.conn.send("Look")
        else:
            self.direction = Direction.NORTH
            self.x = 0
            self.y = 0
            self.last_look = []
            for i, tile in enumerate(response[1:-1].split(",")):
                self.last_look.append([])
                tile = tile.split(" ")
                tile = [elem for elem in tile if elem != ""]
                for elem in tile:
                    self.last_look[i].append(elem)
            self.last_action_succeded = True
            print("Look:", self.last_look)

    def broadcast(self, response=False, text=""):
        print("broadcast(" + str(response) + ", " + text + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "broadcast"
            self.conn.send("Broadcast " + text)
        else:
            self.last_action_succeded = True

    def get_unused_slots(self, response=False):
        print("get_unused_slots(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "get_unused_slots"
            self.conn.send("Connect_nbr")
        else:
            self.unused_slots = int(response)
            self.last_action_succeded = True

    def eject(self, response=False):
        print("eject(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "eject"
            self.conn.send("Eject")
        else:
            self.last_action_succeded = True if response == "ok" else False

    def ejected(self, message):
        print("ejected(" + message + ")")
        self.is_ejected = True
        self.is_ejected_from = int(message[7:])

    def die(self):
        print("die()")
        print("You're dead lvl " + str(self.level) + " !\n")
        sys.exit(0)

    def take_object(self, response=False, obj=""):
        print("take_object(" + str(response) + ", " + obj + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "take_object"
            self.conn.send("Take " + obj)
            self.last_object = obj
        else:
            self.last_action_succeded = True if response == "ok" else False
            if self.last_action_succeded and self.last_object != "food":
                self.inventory[ressources.index(self.last_object)] += 1

    def drop_object(self, response=False, obj=""):
        print("drop_object(" + str(response) + ", " + obj + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "drop_object"
            self.conn.send("Set " + obj)
            self.last_object = obj
        else:
            self.last_action_succeded = True if response == "ok" else False
            if self.last_action_succeded and self.last_object != "food":
                self.inventory[ressources.index(self.last_object)] -= 1

    def start_incantation(self, response=False):
        print("start_incantation(" + str(response) + ")")
        if response == "Elevation underway" and self.elevating:
            pass
        elif not(response):
            self.last_action_succeded = False
            self.last_action = "start_incantation"
            self.elevating = True
            self.conn.send("Incantation")
        else:
            print("ELSE START INCANTATION:", response)
            if self.last_action == "start_incantation":
                self.last_action_succeded = True if response != "ko" else False
            if response != "ko":
                self.level = int(response[15:])
            self.last_look = None
            self.next_target = None
            self.elevating = False
            self.moving_to_incantation = False
            self.go_to_incantation = None
            self.arrived = False
            self.asking_lvl_up = False

    def turn_left(self, response=False):
        print("turn_left(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "turn_left"
            self.conn.send("Left")
        else:
            self.direction = self.direction + (-1)
            self.last_action_succeded = True
            self.moving_action = False

    def turn_right(self, response=False):
        print("turn_right(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "turn_right"
            self.conn.send("Right")
        else:
            self.direction = self.direction + 1
            self.last_action_succeded = True
            self.moving_action = False

    def move_forward(self, response=False):
        print("move_forward(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "move_forward"
            self.conn.send("Forward")
        else:
            if not self.moving_to_incantation:
                (self.last_look[self.get_nb_case(self.x, self.y)]
                    .remove("player"))
            if self.direction == Direction.NORTH:
                self.y += 1
            elif self.direction == Direction.SOUTH:
                self.y -= 1
            elif self.direction == Direction.EAST:
                self.x -= 1
            else:
                self.x += 1
            if not self.moving_to_incantation:
                (self.last_look[self.get_nb_case(self.x, self.y)]
                    .append("player"))
            self.last_action_succeded = True
            self.moving_action = False

    def fork(self, response=False):
        print("fork(" + str(response) + ")")
        if not response:
            self.last_action = "fork"
            self.last_action_succeded = False
            self.conn.send("Fork")
        else:
            self.last_action_succeded = response == "ok"

    def find_empty_tile(self):
        print("---find_empty_tile()")
        for nb_case, case in enumerate(self.last_look):
            count = case.count("food")
            nb_elem = len(case)
            if nb_elem == 0 or (nb_elem > 0 and nb_elem == count):
                y = int(sqrt(nb_case))
                x = int(nb_case - y**2 - y)
                if (self.next_target is None or x + y <
                        self.next_target["x"] + self.next_target["y"]):
                    self.next_target = {"what": "empty", "x": x, "y": y}
        print("next target:", self.next_target)

    def find_next_target(self):
        print("---find_next_target()")
        self.next_target = None
        for i, nb_res in enumerate(self.ressources_needed()):
            if self.inventory[i] < nb_res:
                for nb_case, case in enumerate(self.last_look):
                    nb_players = case.count("player")
                    if ((nb_case == 0 and nb_players > 1) or
                            (nb_case != 0 and nb_players > 0) or
                            (nb_case < self.get_nb_case(self.x, self.y))):
                        continue
                    if ressources[i] in case:
                        y = int(sqrt(nb_case))
                        x = int(nb_case - y**2 - y)
                        if (self.next_target is None or x + y <
                                self.next_target["x"] + self.next_target["y"]):
                            self.next_target = {"what": ressources[i],
                                                "x": x, "y": y}
        print("next target:", self.next_target)

    def move_to_target(self):
        print("---move_to_target()")
        if self.next_target is None:
            return False
        print("x:", self.x, "y:", self.y, "target.x:",
              self.next_target["x"], "target.y:", self.next_target["y"])
        if self.y == self.next_target["y"] and self.x == self.next_target["x"]:
            return True
        elif self.y < self.next_target["y"]:
            self.move_forward()
        elif self.direction == Direction.NORTH:
            if self.next_target["x"] < self.x:
                self.turn_left()
            else:
                self.turn_right()
        else:
            self.move_forward()
        return False

    def get_nb_case(self, x, y):
        i = y**2
        if x < 0:
            i += y - (-x)
        elif x > 0:
            i += y + x
        else:
            i += y
        return i

    def can_level_up(self):
        print("---can_level_up()")
        if self.level == 8:
            print("False")
            return False
        self.ressources_ok = False
        r_needed = self.ressources_needed()
        print("pos:", [self.x, self.y])
        print("get nb case:", self.get_nb_case(self.x, self.y))
        for i, r in enumerate(r_needed):
            print(ressources[i], "\t\t" if i in [2, 4] else "\t", self.last_look[self.get_nb_case(self.x, self.y)]
                    .count(ressources[i]), "/", r)
            c_res = self.last_look[self.get_nb_case(self.x, self.y)].count(ressources[i])
            if (r != c_res):
                print("False")
                if r < c_res:
                    self.drop_ressources = False
                self.ressources_ok = False
                return False
        self.drop_ressources = False
        self.ressources_ok = True
        nb_p_needed = self.get_nb_players_needed()
        ret = (nb_p_needed == self.last_look
               [self.get_nb_case(self.x, self.y)].count("player"))
        print(ret)
        if ret:
            self.friends_incantation = []
        return ret

    def do_nothing(self, response=False):
        print("do_nothing(" + str(response) + ")")
        if not(response):
            self.last_action_succeded = False
            self.last_action = "do_nothing"
            self.conn.send("do_nothing")
        else:
            self.last_action_succeded = True

    def has_enough_people(self):
        return True

    def drop_ressources_needed(self):
        for i, res in enumerate(self.ressources_needed()):
            count = self.last_look[self.get_nb_case(self.x, self.y)].count(ressources[i])
            if count < res:
                self.drop_object(False, ressources[i])
                break

    def is_on_empty_tile(self):
        print("---is_on_empty_tile()")
        case = self.last_look[self.get_nb_case(self.x, self.y)]
        count = case.count("food")
        count_players = case.count("player")
        nb_elem = len(case)
        print(nb_elem == 0 or (nb_elem > 0 and nb_elem == count +
                               count_players and count_players == 1))
        return (nb_elem == 0 or (nb_elem > 0 and nb_elem == count +
                                 count_players and count_players == 1))

    def manage_messages(self):
        msg = self.msg_received[0]
        self.msg_received.pop(0)
        print(str(self.id), "Traite:", msg)
        direction = msg["direction"]
        msg = msg["message"]
        print("go_to_incantation:", self.go_to_incantation)
        if "ASK" in msg and msg["ASK"] == "incantation" and self.go_to_incantation is None and len(self.friends_incantation) == 0:
            if "LVL" in msg and int(msg["LVL"]) == self.level and (not self.asking_lvl_up or (self.asking_lvl_up and self.id > int(msg["FROM"]))):
                print("SEND OK")
                self.send_message("TO:" + msg["FROM"] + " FROM:" + str(self.id) + " ANSWER:incantation_ok")
                self.go_to_incantation = msg["FROM"]
                self.asking_lvl_up = False
                self.last_look = None
                self.next_target = None
                self.turn_around = 0
            else:
                print("SEND KO")
                self.send_message("TO:" + msg["FROM"] + " FROM:" + str(self.id) + " ANSWER:incantation_ko")
        elif self.go_to_incantation:
            if "ANSWER" in msg and msg["ANSWER"] == "incantation_okok":
                print("RECU OKOK")
                self.do_nothing()
            elif "ANSWER" in msg and msg["ANSWER"] == "incantation_koko":
                print("RECU KOKO")
                self.go_to_incantation = None
#                self.look_around()
                self.do_nothing()
            elif "INFO" in msg and msg["INFO"] == "come_here" and not self.go_to_incantation is None:
                print("RECU come_here")
                self.moving_to_incantation = True
                print("move to", direction)
                if self.arrived:
                    print("DO_NOTHING ARRIVED")
                    self.do_nothing()
                elif direction in [1, 2, 8]:
                    self.moving_action = True
                    self.move_forward()
                elif direction in [3, 4]:
                    self.moving_action = True
                    self.turn_left()
                elif direction in [5, 6, 7]:
                    self.moving_action = True
                    self.turn_right()
                else:
                    print("SEND im_here")
                    self.send_message("TO:" + self.go_to_incantation + " FROM:" + str(self.id) + " INFO:im_here")
                    self.arrived = True
                    self.last_look = None
        else:
            if "ANSWER" in msg and msg["ANSWER"] == "incantation_ok":
                print("RECU OK")
                if len(self.friends_incantation) < self.get_nb_players_needed() - 1:
                    print("SEND OKOK")
                    self.friends_incantation.append(msg["FROM"])
                    self.send_message("TO:" + msg["FROM"] + " FROM:" + str(self.id) + " ANSWER:incantation_okok")
                else:
                    print("SEND KOKO")
                    self.send_message("TO:" + msg["FROM"] + " FROM:" + str(self.id) + " ANSWER:incantation_koko")
            elif "ANSWER" in msg and msg["ANSWER"] == "incantation_ko":
                print("RECU KO")
                self.do_nothing()
            elif "INFO" in msg and msg["INFO"] == "im_here":
                print("RECU im_here")
                self.look_around()
            else:
                self.do_nothing()
        if self.last_action_succeded:
            self.do_nothing()

    def runAi(self):
        print("runAi")
        if self.msg_received:
            self.manage_messages()
        elif self.is_ejected:
            print("react to ejected, from", self.is_ejected_from)
        elif self.go_to_incantation is None:
            if self.last_action in ["take_object"]:
                self.get_inventory()
            elif self.last_action in ["drop_object"]:
                self.look_around()
            elif self.move_n_case > 0:
                self.move_forward()
                self.move_n_case -= 1
                if self.move_n_case == 0:
                    self.turn_around = 0
            elif self.last_look:
                if self.level < MAX_LEVEL:
                    if self.can_level_up():
                        self.start_incantation()
                        return
                    elif not self.ressources_ok:
                        if self.has_ressources_needed():
                            if self.is_on_empty_tile():
                                self.drop_ressources = True
                            else:
                                if self.next_target is None:
                                    self.find_empty_tile()
                    else:
                        print("****************************TAMER**************************", self.id)
                        print("friends_incantation:", self.friends_incantation)
                        if self.tmp == 4:
                            self.tmp = 0
                            if self.go_to_incantation is None and len(self.friends_incantation) < self.get_nb_players_needed() - 1:
                                self.asking_lvl_up = True
                                self.send_message("TO:all FROM:" + str(self.id) + " ASK:incantation LVL:" + str(self.level))
                            else:
                                self.send_message("TO:" + str(self.friends_incantation) + " FROM:" + str(self.id) + " INFO:come_here")
                        else:
                            self.do_nothing()
                            self.tmp += 1
                        return
                    if self.drop_ressources:
                        self.drop_ressources_needed()
                        return
                if self.next_target is None:
                    self.find_next_target()
                if self.next_target is None:
                    if self.random_dir is None:
                        from random import choice
                        self.random_dir = choice(["left", "right"])
                    print("turn")
                    if self.turn_around < 3:
                        self.turn_around += 1
                        self.turn_left() if self.random_dir == "left" else self.turn_right()
                        self.last_look = None
                    else:
                        self.move_n_case = self.level
                        self.look_around()
                        self.random_dir = None
                else:
                    self.turn_around = 0
                    self.random_dir = None
                    if self.has_food_on_tile(self.x, self.y):
                        self.take_object(False, "food")
                        nb_case = self.get_nb_case(self.x, self.y)
                        self.last_look[nb_case].remove("food")
                    elif self.move_to_target():
                        if self.next_target["what"] != "empty":
                            self.take_object(False, self.next_target["what"])
                        self.last_look = None
                        if self.next_target["what"] == "empty":
                            self.look_around()
                        self.next_target = None
            else:
                self.look_around()
        elif not self.elevating:
            print("DO_NOTHING LAST")
            self.do_nothing()

    def has_food_on_tile(self, x, y):
        tile = self.last_look[self.get_nb_case(x, y)]
        return "food" in tile

    def send_message(self, message):
        print("---send_message(" + message + ")")
        if message == "ok":
            self.last_action_succeded = True
        else:
            self.last_action_succeded = False
            self.last_action = "send_message"
            self.conn.send("Broadcast " + message)

    def transform_messages(self, message):
        print("---transform_messages(" + message + ")")
        case = int(message[0])
        message = message[3:]
        if message[3] == "[":
            for i, c in enumerate(message[4:]):
                if c == "]":
                    break
                if c == " ":
                    message = message.replace(" ", "", 1)
        message = message.split(" ")
        msg = {"direction": case, "message": {}}
        print("message:", message)
        for elem in message:
            elem = elem.split(":")
            print("elem:", elem)
            msg["message"].update({elem[0]: elem[1]})
        if msg["message"]["TO"][0] == '[':
            msg["message"]["TO"] = json.loads(msg["message"]["TO"].replace("'", '"'))
            if str(self.id) in msg["message"]["TO"]:
                msg["message"]["TO"] = str(self.id)
        return msg

    def run(self):
        print("Player.run")
        self.look_around()
        while self.conn.has_next or self.conn.wait_message():
            msg = self.conn.next()
            print("[" + str(self.id) + "] lvl[" + str(self.level) + "] last_action:", self.last_action, "| succeded:", self.last_action_succeded, "| msg:", msg)
            if not msg in ["dead", "Elevation underway"] and msg[:5] != "eject" and msg[:7] != "message":
                print("elevating:", self.elevating, " | last_action:", self.last_action)
                if self.elevating and self.last_action != "start_incantation" and msg[:15] == "Current level: ":
                    succeded = self.last_action_succeded
                    self.actions["start_incantation"](msg)
                    self.elevating = False
                    if not succeded:
                        continue
                else:
                    self.actions[self.last_action](msg)
            elif msg == "dead":
                self.die()
            elif msg[:5] == "eject":
                self.ejected(msg)
            elif msg[:7] == "message":
                if self.last_action == "send_message" and not self.last_action_succeded and self.moving_to_incantation:
                    print("continue before")
                    continue
                msg = self.transform_messages(msg[8:])
                if msg["message"]["TO"] in ["all", str(self.id)] and not self.elevating and (not self.moving_to_incantation or (self.moving_to_incantation and not self.moving_action)):
                    self.msg_received.append(msg)
                    print("added:", len(self.msg_received), "moving_to_incantation:", self.moving_to_incantation, "elevating:", self.elevating)
                if not self.last_action_succeded:
                    if len(self.msg_received) > 0:
                        msg2 = self.msg_received[-1]["message"]
                        print("STARF", msg2, not("INFO" in msg2 and msg2["INFO"] in ["come_here"]))
                        if not("INFO" in msg2 and msg2["INFO"] in ["come_here"]):
                            print("continue after1")
                        else:
                            self.msg_received = [self.msg_received[-1]]
                        continue
                    else:
                        print("continue after2")
                        continue
                print("suce")
            elif msg == "Elevation underway":
                print("ICI TA MERE")
                self.elevating = True
                continue
            self.runAi()
            print("end")
