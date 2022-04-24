import libjuice as lj
from DQN import Agent

import numpy as np

class AxieJuiced():
    def __init__(self):
        self.done = False
        self.score = 0
        self.energy = 0

    def round(self):
        # choose cards

        # attack
        self.attack = gameState.attack()

        if self.attack == 1:
            # player 1 wins
            self.reward = 3
            self.done = True
            pass
        
        if self.attack == 2:
            # player 2 wins
            self.reward = -3
            self.done = True
            pass



    def reset(self, player1, player2):
        self.gameState = lj.PState(player1, player2)

    def step(self, action, player):
        self.reward = 0
        self.done = 0


        self.gameState.chooseCards(player, action)
        # if action == # use card not usable:
        #     self.reward = -1


        state = np.concatenate((self.gameState.playerMat(1), self.gameState.playerMat(2)))

        return self.reward, state, self.done



# Prints working directory, should be in the same directory as this file e.g. inside "Game-engine"
# print(lj.PrintWorkingDir())

# create a new game instance
# gameState = lj.PState(1,5)


# save the state for player1 and player2
# p1_Mat = gameState.playerMat(1)
# p2_Mat = gameState.playerMat(2)

#  give cards ability to be chosen

#  -------------------- Game Loop --------------------

# Choose cards for players
# gameState.chooseCards(1, [1,2])
# gameState.chooseCards(2, [1,2])

# run attackstate with player1 and player2 states
# state = gameState.attack()
# if state == 1:
    # print("Player 1 wins")
# elif state == 2:
    # print("Player 2 wins")

# check the state for player1 and player2
# p1_Mat = gameState.playerMat(1)
# p2_Mat = gameState.playerMat(2)

# give rewards









print("Done!")