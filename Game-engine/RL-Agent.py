import numpy as np
from DQQN import Agent
from utils import plotLearning
from game import DeepAxie

player1 = 5
player2 = 1

if __name__ == '__main__':
    env = DeepAxie(player1, player2)
    # policy is the action to take at a given state
    # gamma = discount factor, how much we want to discount future rewards
    # epsilon = how much randomness, 0.05 is good
    # epsilon_min = minimum randomness, 0.01 is good
    # epsilon_decay = how much to decay randomness, 0.995 is good
    # lr = learning_rate = how fast to learn, 0.001 is good
    # input_dims = dimensions of the input,
    # n_actions = number of actions
    # batch_size = how many experiences to sample

    agent = Agent(gamma=0.99, epsilon=1.0, lr=0.003, input_dims=[88], batch_size=64, n_actions=88)
    scores, eps_history = [], []
    n_games = 500

    for i in range(n_games):
        score = 0
        done = False
        observation = env.reset(player1,player2)
        while not done:
            action = agent.choose_action(observation)
            observation_, reward, reward2, done = env.step(action)
            score += reward
            agent.store_transition(observation, action, reward, observation_, done)
            agent.learn()
            observation = observation_
        scores.append(score)
        eps_history.append(agent.epsilon)

        avg_score = np.mean(scores[-100:])

        print('episode ', i, 'score %.2f' % score, 
                'average score %.2f' % avg_score, 
                'epsilon %.2f' % agent.epsilon)
    x = [i+1 for i in range(n_games)]
    filename = 'axies.png'
    plot_learning_curve(x, scores, eps_history, filename)


    matrix=[[0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8]]

    for i in range(9):
        for j in range(9):
            pass
    # random number generated



print("hey")