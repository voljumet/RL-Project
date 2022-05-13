from game import DeepAxie
import shutil
import os
import datetime
import random
import numpy as np
import pandas as pd

from numpy import asarray
from numpy import savetxt


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
        self.gamma = .98
        self.batch_size = 64
        self.epsilon_min = .01
        self.epsilon_decay = .995
        self.learning_rate = 0.0001
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

def post_process_state(state, state_space):
    return np.reshape(state, (1, state_space))/1200

def train_dqn(episode):

    returnrewards = []
    ratio = []
    tot_rounds = []

    action_space = 88
    state_space = 88
    max_steps = 100
    
    p1 = 0
    calc = 0
    selected_player = "player_1"
    agent = DQN(action_space, state_space)
    for e in range(episode):
        states = env.reset()
        states = {k: post_process_state(v, state_space) for k, v in states.items()}
        score = 0
        for rounds in range(max_steps):

            actions = dict(
                #player_0 = random.randint(0,8),
                player_0 = agent.act(states["player_0"]),
                player_1 = random.randint(0,8)
            )
            
            next_states, rewards, dones, infos = env.step(actions)
            next_states = {k: post_process_state(v,state_space) for k, v in next_states.items()}

            score += rewards[selected_player]
            for (agent_name, state), (_, action), (_, reward), (_, next_state), (_, done) in zip(states.items(), actions.items(), rewards.items(), next_states.items(), dones.items()):  
                agent.remember(state, action, reward, next_state, done)
            states = next_states
            agent.replay()
            if any(dones.values()):
                if rewards["player_0"] > rewards["player_1"]:
                    winner = "player_0"
                    p1 += 1
                else:
                    winner = "player_1"
                # todo legge til player til info i step function

                calc = round((p1+0.0000001)/(e+1), 3)
                ratio.append(calc)
                print("episode: {}/{}, rounds: {}, score: {}, winner: {}, win-ratio: {}".format(e, episode, rounds, round(score,3), winner, calc))
                break
        returnrewards.append(score)
        tot_rounds.append(rounds)
        
    return returnrewards, ratio, tot_rounds

print("Let's GOOOO")


if __name__ == '__main__':
    # define data
    # data = asarray([[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]])
    # save to csv file
    

    time = str(datetime.datetime.today())
    os.chdir('log')
    os.mkdir(time)
    
    # save files to save the configuration
    shutil.copy('../DQN.py', time+'/DQN.txt')
    shutil.copy('../game.py', time+'/game.txt')
    
    os.chdir('..')
    
    ep = 3
    returnrewards, ratio, rounds = train_dqn(ep)
    
    os.chdir('log')
    if ratio.__len__() < ep:
        ratio.append(0)
    
    fig = plt.figure(figsize=(12, 6))
    plt.plot([i for i in range(ep)], ratio, label="win-ratio")    
    plt.xlabel('episodes')
    plt.ylabel('win-ratio')
    fig.savefig(time +"/training" +  '.jpg', bbox_inches='tight', dpi=150)
    # plt.show()
    
    fig = plt.figure(figsize=(12, 6))
    plt.plot([i for i in range(ep)], returnrewards, label="reward")
    plt.xlabel('episodes')
    plt.ylabel('reward')
    fig.savefig(time +"/reward" +  '.jpg', bbox_inches='tight', dpi=150)
    # plt.show()
    
    fig = plt.figure(figsize=(12, 6))
    plt.plot([i for i in range(ep)], rounds, label="rounds")
    plt.xlabel('episodes')
    plt.ylabel('rounds')
    fig.savefig(time +"/rounds" +  '.jpg', bbox_inches='tight', dpi=150)
    # plt.show()
    
    # savetxt(time +"/numbers.csv", (ep, ratio, returnrewards, rounds), delimiter=',')
    # np.savetxt(time +"/numbers.csv", ( ,ratio ,returnrewards, rounds), delimiter=',')
    df = pd.DataFrame({"episode" : np.arange(ep), "win-loss ratio" : ratio, "reward" : returnrewards, "rounds" : rounds})
    df.to_csv(time +"/numbers.csv", index=False)