from time import time

import numpy as np
np.random.seed(0)

class FlappyAgent:

    def __init__(self, observation_space_size, action_space, n_iterations):
        self.q_table = np.zeros([*observation_space_size, len(action_space)])
        self.env_action_space = action_space
        self.n_iterations = n_iterations

        self.test = False

    def step(self, state):
        action = 0

        #if not self.test:  # and ...:
        #    action = self.q_table[state][best]
        #else:
            # action =
        #    pass
        action = np.argmax(self.q_table[state])#self.q_table[state]#[np.argmax(self.q_table[state])]

        return action

    def epoch_end(self, epoch_reward_sum):
        pass

    def learn(self, old_state, action, new_state, reward):
        theta = reward + 0.4 * self.q_table[new_state][np.argmax(self.q_table[new_state])] - self.q_table[old_state][action]
        self.q_table[old_state][action] = self.q_table[old_state][action] + 0.5 * theta

    def train_end(self):
        # ...

        #self.q_table = None  # TODO
        self.test = True


#best = np.argmax(self.q_table[new_state])
#target = reward + 0.6 * self.q_table[new_state][best]
#theta = target - self.q_table[old_state][action]
#self.q_table[old_state][action] = self.q_table[old_state][action] + 0.6 * theta
