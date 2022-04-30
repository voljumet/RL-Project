from game import DeepAxie
import shutil
import os
import datetime
import random
import numpy as np
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import SGD
from tensorflow.keras.optimizers import Adam

from collections import deque
import matplotlib.pyplot as plt

# from torch.optim import Adam
# import torch
# import torch.nn as nn
# import torch.nn.functional as F
#import torch.optim as optim

player_1 = 7
player_2 = 4


env = DeepAxie(player_1, player_2)
np.random.seed(0)

# class NeuralNet(nn.Module):
#     def __init__(self, state_space, action_space):
#         super(NeuralNet, self).__init__()
#         self.fc1 = nn.Linear(state_space, 6)
#         self.fc2 = nn.Linear(6, 1)
#
#     def forward(self, x):
#         x = self.fc1(x)
#         x = F.relu(x)
#         x = self.fc2(x)
#         x = torch.sigmoid(x)
#         return torch.squeeze(x)


class DQN:

    """ Implementation of deep q learning algorithm """

    def __init__(self, action_space, state_space):

        self.action_space = action_space
        self.state_space = state_space
        self.epsilon = 1
        self.gamma = .95
        self.batch_size = 64
        self.epsilon_min = .01
        self.epsilon_decay = .995
        self.learning_rate = 0.001
        self.memory = deque(maxlen=100000)
        self.model = self.build_model()

    def build_model(self):
        #  to dense layer på siden av hverandre
        model = Sequential()
        model.add(Dense(64, input_shape=(self.state_space,), activation='relu'))
        model.add(Dense(64, activation='relu'))
        model.add(Dense(self.action_space, activation='linear'))
        model.compile(loss='mse', optimizer=Adam(learning_rate=self.learning_rate))
        return model

    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def act(self, state):

        if np.random.rand() <= self.epsilon:
            array = [0, 1, 2, 3, 4, 5, 6, 7, 8]
            ints = random.sample(array, 2)
            string_ints = [str(int) for int in ints]  # Convert each integer to a string
            str_of_ints = "".join(string_ints)  # Combine each string with a comma
            return int(str_of_ints)  # Output: 1,2,3

        act_values = self.model.predict(state)
        
        return np.argmax(act_values[0])

    def replay(self):

        if len(self.memory) < self.batch_size:
            return

        minibatch = random.sample(self.memory, self.batch_size)
        states = np.array([i[0] for i in minibatch])
        actions = np.array([i[1] for i in minibatch])
        rewards = np.array([i[2] for i in minibatch])
        next_states = np.array([i[3] for i in minibatch])
        dones = np.array([i[4] for i in minibatch])

        states = np.squeeze(states)
        next_states = np.squeeze(next_states)

        targets = rewards + self.gamma*(np.amax(self.model.predict_on_batch(next_states), axis=1))*(1-dones)
        targets_full = self.model.predict_on_batch(states)

        ind = np.array([i for i in range(self.batch_size)])
        targets_full[[ind], [actions]] = targets

        self.model.fit(states, targets_full, epochs=1, verbose=0)
        if self.epsilon > self.epsilon_min:
            self.epsilon *= self.epsilon_decay


def train_dqn(episode):

    loss = []
    ratio = []

    action_space = 88
    state_space = 88
    max_steps = 1000
    
    p1 = 0
    calc = 0

    agent = DQN(action_space, state_space)
    for e in range(episode):
        state = env.reset(player_1, player_2)
        state = np.reshape(state, (1, state_space))
        score = 0
        for i in range(max_steps):
            action = agent.act(state)
            reward, reward2, next_state, done, p1win, p2win = env.step(action)
            score += reward
            next_state = np.reshape(next_state, (1, state_space))
            agent.remember(state, action, reward, next_state, done)
            state = next_state
            agent.replay()
            if done:
                if p1win:
                    p1 += 1
                    winner = "player1"
                    
                elif p2win:
                    winner = "player2"

                calc = round((p1+0.0000001)/(e+1), 3)
                ratio.append(calc)
                print("episode: {}/{}, rounds: {}, score: {}, winner: {}, win-ratio: {}".format(e, episode, i, round(score,3), winner, calc))
                break
        loss.append(score)
    return loss, ratio

print("Let's GOOOO")


if __name__ == '__main__':

    ep = 10000
    loss, ratio = train_dqn(ep)
    
    time = str(datetime.datetime.today())
    os.chdir('log')
    os.mkdir(time)

    
    fig = plt.figure(figsize=(12, 6))
    plt.plot([i for i in range(ep)], loss)
    plt.xlabel('episodes')
    plt.ylabel('reward')
    fig.savefig(time +"/training" +  '.jpg', bbox_inches='tight', dpi=150)
    plt.show()
    
    fig2 = plt.figure(figsize=(12, 6))
    plt.plot([i for i in range(ep)], ratio)
    plt.xlabel('episodes')
    plt.ylabel('win-ratio')
    fig2.savefig(time +"/win-loss" +  '.jpg', bbox_inches='tight', dpi=150)
    plt.show()
    
    # save files to save the configuration
    shutil.copy('../DQN.py', time+'/DQN.txt')
    shutil.copy('../game.py', time+'/game.txt')