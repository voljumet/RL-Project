# Load the cpp library libjuice.so
import DeepAxie
import numpy as np

# Prints working directory, should be in the same directory as this file e.g. inside "Game-engine"
print(DeepAxie.PrintWorkingDir())

# Create a new game instance with player1 and player2 as the team numbers (1,2) from the file "axie_teams.json"
gameState = DeepAxie.GameState(1,5)
roundCounter = 0

while True:
    roundCounter += 1
    print(gameState.printGameBoard(roundCounter))
    # Presenting cards from the deck of cards for players inside the gameState.
    drawCardsFromDeck = gameState.drawCardsFromDeck(1)
    print("cards that can be chosen: ",drawCardsFromDeck)

    # use rand to pick two random numbers from an array.
    # Choose cards among the cards drawn from deck for both players.
    rand1 = np.random.randint(0,drawCardsFromDeck.__len__())
    rand2 = np.random.randint(0,drawCardsFromDeck.__len__())
    
    while rand1 == rand2:
        rand2 = np.random.randint(0,4)


    print("card1 index chosen: ",rand1)
    print("card2 index chosen: ",rand2)
    print("card1 chosen: ",drawCardsFromDeck[ rand1 ])
    print("card2 chosen: ",drawCardsFromDeck[ rand2 ])
    gameState.chooseCards(1, [ drawCardsFromDeck[ rand1 ], drawCardsFromDeck[ rand2 ] ])

    # Presenting cards from the deck of cards for players inside the gameState.
    drawCardsFromDeck = gameState.drawCardsFromDeck(2)
    # use rand to pick two random numbers from an array.
    # Choose cards among the cards drawn from deck for both players.
    rand = np.random.randint(0,4,2)
    gameState.chooseCards(2, [drawCardsFromDeck[rand[0]], drawCardsFromDeck[rand[1]]])


    # Run attackstate for the gameState, returns an int.
    state = gameState.attack()
    print("Round: ",roundCounter)
    # The int returned by attackstate is like the if else statement 
    if state == 1:
        print("Player 1 wins")
    elif state == 2:
        print("Player 2 wins")


    # Returns gameState with a matrix containing players represented as decimal numbers.
    # (see the file bits_meaning.txt for further explaination)
    playersMatrixDecimal = gameState.playersMatrixDecimal()

    # Returns gameState with a matrix containing players represented as Bits.
    # (see the file bits_meaning.txt for further explaination)
    playersMatrixBits = gameState.playersMatrixBits()

