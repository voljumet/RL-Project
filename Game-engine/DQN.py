import libjuice as lj
import numpy as np

# print(lj.ChooseTeam(1))
# print(lj.ChooseTeam(9))

# if first == second == third:
#     print("same")

# init pet
# newPet = lj.Pet("Alex")

# print name
# print(newPet.getName())
# newPet.setName("Peshang")
# print(newPet.getName())


gameState = lj.PState(2,9)

print(gameState.playerMatTEST(1))
print(gameState.playerMatTEST(2))

gameState.chooseCards(1, [1,2])
gameState.chooseCards(2, [1,2])

print(gameState.playerMatTEST(1))
print(gameState.playerMatTEST(2))

gameState.attack()

print(gameState.playerMatTEST(1))
print(gameState.playerMatTEST(2))






print("hey")