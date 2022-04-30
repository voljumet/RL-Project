from sys import platform
if platform == "linux" or platform == "linux2":
    import DeepAxieLinux as axie
elif platform == "darwin":
    import DeepAxie as axie
elif platform == "win32":
    # Windows...
    pass

display_game_window = False
try:
    import turtle as t
    display_game_window = True
except:
    print(" Game-window is not loadable, problem loading turtle (tkinter package)")

import random
import numpy as np

    
class DeepAxie():
    def __init__(self, player1, player2):
        self.done = False
        self.energy = 0
        self.reward1 = 0
        self.reward2 = 0
        self.roundCounter = 1
        self.p1win = False
        self.p2win = False
        # init game
        self.GameState = axie.GameState(player1, player2)
        
        if display_game_window:
            # window setup
            self.window = t.Screen()
            self.window.title('DeepAxie')
            self.window.bgcolor('black')
            self.window.setup(width=900, height=400)

            # print game board
            self.board = t.Turtle()
            self.board.speed(0)
            self.board.color('white')
            self.board.penup()
            self.board.hideturtle()
            self.board.goto(0, 0)
            self.board.write("{}".format(self.GameState.printGameBoard(self.roundCounter)), align='center', font=('Courier', 24, 'normal'),)
        # print("hold on")

    def round(self):
        self.roundCounter += 1
        # attack
        previous_state = self.GameState.playersMatrixDecimal()
        attack = self.GameState.attack()
        state = self.GameState.playersMatrixDecimal()

        # check if the defender axie is defeated then add 1 to the reward
        if (state[62] == 0 and previous_state[62] == 1) or (state[83] == 0 and previous_state[83] == 1):
            self.reward1 += 0.1
            
        # check if the oponents axie's health has decreased and reward
        if (state[64] < previous_state[64]) or (state[85] < previous_state[85]):
            self.reward1 += 0.1
        
        # check if player axie's health has adjusted and reward
        if (state[20] < previous_state[20]) or (state[42] < previous_state[42]):
            self.reward1 -= 0.1
        else:
            self.reward1 += 0.1

        if attack == 1:
            # player 1 wins
            self.reward1 += 1
            self.roundCounter = 1
            self.done = True
            self.p1win = True

        if attack == 2:
            # player 2 wins
            self.reward1 -= 1
            self.roundCounter = 1
            self.done = True
            self.p2win = True

        
            
        if display_game_window:
            self.board.clear()
            self.board.write("{}".format(self.GameState.printGameBoard(self.roundCounter)), align='center', font=('Courier', 24, 'normal'),)


    def reset(self, player1, player2):
        # "restarts" the game
        self.GameState = axie.GameState(player1, player2)
        return self.GameState.playersMatrixDecimal()



    def pickCards(self, player, action):
        # agent has to be able to chose all cards everytime, 
        # the pickcards array should be the same every round, even if the cards cannot be chosen

        # This function checks how good the agent has understood what cards can be chosen
        reward = 0
        selectable_cards = self.GameState.drawCardsFromDeck(player)
        action = [int(a) for a in str(action)]

        action_array = np.array([0,1,2,3,4,5,6,7,8])
        selectable_mask_array = np.zeros(9)
        action_mask_array = np.zeros(9)

        for i in range(len(action_array)):
            for j in range(len(selectable_cards)):
                if selectable_cards[j] == action_array[i]:
                    selectable_mask_array[i] = 1

        for i in range(len(action_array)):
            for j in range(len(action)):
                if action[j] == action_array[i]:
                    action_mask_array[i] = 1

        for i in range(len(action_array)):
            if action_mask_array[i] == 1 and selectable_mask_array[i] == 0:
                reward -= .05
        # player
        self.GameState.chooseCards(player, action)

        return reward
    

    def action_2(self):
        array = [0, 1, 2, 3, 4, 5, 6, 7, 8]
        ints = random.sample(array, 2)
        string_ints = [str(int) for int in ints]  # Convert each integer to a string
        str_of_ints = "".join(string_ints)  # Combine each string with a comma
        return int(str_of_ints)  # Output: 1,2,3


    def step(self, action):
        #  action is an array of two actions
        self.done = 0
        self.reward1 = 0
        self.reward2 = 0
        self.p1win = False
        self.p2win = False

        self.reward1 += self.pickCards(1, action)
        self.reward2 += self.pickCards(2, self.action_2())

        #  attack is run inside round()
        self.round()
        state = self.GameState.playersMatrixDecimal()

        return self.reward1, self.reward2, state, self.done, self.p1win, self.p2win


# env = DeepAxie(1,5)



# print("Done!")