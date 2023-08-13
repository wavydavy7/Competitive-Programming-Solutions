import enum

class GridPosition(enum.Enum):
    EMPTY = 0
    RED = 1 
    YELLOW = 2
    
class Board:
    def __init__(self, rows, cols):
        self.grid = None
        self.rows = rows
        self.cols = cols
        self.initGrid()

    def initGrid(self):
        self.grid = [[GridPosition.EMPTY for _ in range(self.cols)] for _ in range(self.rows)]
    
    def getGrid(self):
        return self.grid

    def getColCnt(self):
        return self.cols

    def placePiece(self, c, piece):
        if c < 0 or c >= self.cols:
            raise ValueError("Not a valid column")
        if piece == GridPosition.EMPTY:
            raise ValueError("Can't play this piece")
        for row in range(self.rows - 1, -1, -1):
            if self.grid[row][c] == GridPosition.EMPTY:
                self.grid[row][c] = piece
                return row
    def winRound(self, row, col, piece, connectN):

        #win horizontal
        count = 0
        for c in range(self.cols):
            if self.grid[row][c] == piece:
                count += 1
            else:
                count = 0
            if count == connectN:
                return True 
        #win vertical
        count = 0
        for r in range(self.rows):
            if self.grid[r][col] == piece:
                count += 1
            else:
                count = 0
            if count == connectN:
                return True
        #win left to right diagonal
        count = 0
        for r in range(self.rows):
            c = row + col - r
            if c >= 0 and c < self.cols and self.grid[r][c] == piece:
                count += 1
            else:
                count = 0
            if count == connectN:
                return True 
        
        #win right to left diagonal
        count = 0
        for r in range(self.rows):
            c = col - row + r
            if c >= 0 and c < self.rows and self.grid[r][c] == piece:
                count += 1
            else:
                count = 0
            if count == connectN:
                return True 
        return False



class Player:
    def __init__(self, name, piece):
        self.name = name
        self.piece = piece
    def getName(self):
        return self.name
    def getPiece(self):
        return self.piece

class Game:
    def __init__(self, connectN, winBy, grid):
        self.connectN = connectN
        self.winBy = winBy
        self.grid = grid
        self.players = [Player("player1", GridPosition.YELLOW), Player("player2", GridPosition.RED)]
        self.score = {}
        for player in self.players:
            self.score[player.getName()] = 0
    
    def printBoard(self):
        print("Board: \n")
        grid = self.grid.getGrid()
        for i in range(len(grid)):
            row = ''
            for slot in grid[i]:
                if slot == GridPosition.EMPTY:
                    row += "0 "
                elif slot == GridPosition.YELLOW:
                    row += "Y "
                else:
                    row += "R "
            print(row)
        print('')
    def playMove(self, player):
        self.printBoard()
        print(player.getName() + "'s turn!")
        colCnt = self.grid.getColCnt()
        moveColumn = int(input(f"Enter column between {0} and {colCnt - 1}: "))
        moveRow = self.grid.placePiece(moveColumn, player.getPiece())
        return (moveRow, moveColumn)
    
    def playRound(self):
        while True:
            for player in self.players:
                row, col = self.playMove(player)
                piece = player.getPiece()
                if self.grid.winRound(row, col, piece, self.connectN):
                    self.score[player.getName()] += 1
                    return player
    def play(self):
        winner = False
        maxScore = 0 
        while maxScore < self.winBy:
            res = self.playRound()
            print(f"{res.getName()} won the round!")
            maxScore = max(maxScore, self.score[res.getName()])
            self.grid.initGrid()
        print(f"{res.getName()} won the game!")
        


grid = Board(6, 7)
game = Game(4, 2, grid)
game.play()



