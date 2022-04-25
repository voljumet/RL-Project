import DeepAxie as axie

import turtle as t
import numpy as np

class DeepAxie():
    def __init__(self, player1, player2):
        self.done = False
        self.energy = 0
        # init game
        self.GameState = axie.GameState(player1, player2)

        # window setup
        self.win = t.Screen()
        self.win.title('DeepAxie')
        self.win.bgcolor('black')
        self.win.setup(width=900, height=400)

        # print game board
        self.board = t.Turtle()
        self.board.speed(0)
        self.board.color('white')
        self.board.penup()
        self.board.hideturtle()
        self.board.goto(0, 0)
        # self.score.write("Hit: {}   Missed: {}".format(self.hit, self.miss), align='center', font=('Courier', 24, 'normal'))
        self.board.write("{}".format(self.GameState.printGameBoard(1)), align='center', font=('Courier', 24, 'normal'),)
        print("hold on")

    def round(self):

        # attack
        attack = self.GameState.attack()

        if attack == 1:
            # player 1 wins
            self.reward += 3
            self.done = True
        
        if attack == 2:
            # player 2 wins
            self.reward -= 3
            self.done = True
        
        self.board.clear()
        self.board.write("{}".format(self.GameState.printGameBoard(1)), align='center', font=('Courier', 24, 'normal'),)


    def reset(self, player1, player2):
        # "restarts" the game
        self.GameState = axie.PState(player1, player2)


    def pickCards(self, player, action):
        # 
        # selectable_cards = self.GameState.drawCardsFromDeck(player)

        action_array = np.array([0,1,2,3,4,5,6,7,8])
        mask_array = np.zeros(9)
        reward_array = np.array([-100,-100,-100,-100,-100,-100,-100,-100,-100])

        for i in range(len(action_array)):
            for j in range(len(selectable_cards)):
                if selectable_cards[i] == action_array[j]:
                    mask_array[i] = 1
                    reward_array[i] = 0
        
        self.reward += (action*reward_array).sum()
    

    def step(self, action, player):
        self.reward = 0
        self.done = 0

        # give players cards to pick from
        selectable_cards = self.GameState.drawCardsFromDeck(player[0])
        selectable_cards = self.GameState.drawCardsFromDeck(player[1])

        gameState.chooseCards(player[0], action[0])
        gameState.chooseCards(player[1], action[1])

        # evaluate action + give rewards
        pickCards(1, action)
        # if action == # use card not usable:
        #     self.reward = -1

        # attack = gameState.attack()
        self.round()
        state = gameState.playersMatrixDecimal()

        return self.reward, state, self.done


env = DeepAxie(1,5)



print("Done!")