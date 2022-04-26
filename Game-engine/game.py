import DeepAxie as axie

import turtle as t
import numpy as np

class DeepAxie():
    def __init__(self, player1, player2):
        self.done = False
        self.energy = 0
        self.reward1 = 0
        self.reward2 = 0
        # init game
        self.GameState = axie.GameState(player1, player2)

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


    def predict(self, observation, action_mask=None):
        q_values = self.q(observation)  # [0.11, 0.44, 0.36, 0.77, 0.33, 0.55]
        q_values_masked = q_values if not action_mask else q_values + ([-100, -100, -100, -100] * action_mask)
        
        # epsilon = how much randomness, 0.05 is good

        if epislon > random.random():
           # nb sjekk rekkefølge
            action = random.randint(0, 8)
        else:
            action = np.argmax(q_values)
        return action


    def reset(self, player1, player2):
        # "restarts" the game
        self.GameState = axie.PState(player1, player2)


    def pickCards(self, player, action):
        # agent has to be able to chose all cards everytime, 
        # the pickcards array should be the same every round, even if the cards cannot be chosen

        # This function checks how good the agent has understood what cards can be chosen
        selectable_cards = self.GameState.drawCardsFromDeck(player)

        action_array = np.array([0,1,2,3,4,5,6,7,8])
        mask_array = np.zeros(9)
        reward_array = np.array([-100,-100,-100,-100,-100,-100,-100,-100,-100])

        for i in range(len(action_array)):
            for j in range(len(selectable_cards)):
                if selectable_cards[i] == action_array[j]:
                    mask_array[i] = 1
                    reward_array[i] = 0
        
        # player 
        gameState.chooseCards(player, action)
        
        return (action*reward_array).sum()
    

    def step(self, action, player):
        #  action is an array of two actions
        # self.reward = 0
        self.done = 0

        self.reward1 += pickCards(player[0], action[0])
        self.reward2 += pickCards(player[1], action[1])

        # evaluate action + give rewards
        pickCards(1, action)
        # if action == # use card not usable:
        #     self.reward = -1

        #  attack is run inside round()
        self.round()
        state = gameState.playersMatrixDecimal()

        return self.reward, state, self.done


env = DeepAxie(1,5)



print("Done!")