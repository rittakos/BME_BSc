"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var $ = require("jquery");
var tile_1 = require("./tile");
var player_1 = require("./player");
var GameBoard = (function () {
    function GameBoard(tableElement) {
        this.tableElement = tableElement;
        this.x = 10;
        this.y = 10;
        this.playerOne = new player_1.Player('Player one', 1);
        this.playerTwo = new player_1.Player('Player two', 2);
        this.steps = 0;
        this.startGame();
    }
    GameBoard.prototype.startGame = function () {
        if (!this.loadState()) {
            this.initializeBoard(this.tableElement, this.board = []);
            this.currentPlayer =
                this.winner === this.playerOne ? this.playerTwo : this.playerOne;
        }
        this.registerHandlers(this.board);
    };
    GameBoard.prototype.restartGame = function () {
        this.steps = 0;
        for (var i = 0; i < this.x; ++i) {
            for (var j = 0; j < this.y; ++j) {
                this.board[i][j].setState(tile_1.TileState.Empty);
            }
        }
        this.saveState();
        this.initializeBoard(this.tableElement, this.board = []);
        this.currentPlayer = this.winner === this.playerOne ? this.playerTwo : this.playerOne;
        this.registerHandlers(this.board);
    };
    GameBoard.prototype.clearResults = function () {
        this.playerOne.gamesWon = 0;
        this.playerTwo.gamesWon = 0;
    };
    GameBoard.prototype.initializeBoard = function (tableElement, board) {
        //this.restartGame();
        tableElement.children().remove();
        var tBody = $("<tbody></tbody>");
        tableElement.append(tBody);
        console.log(tableElement.children());
        for (var i = 0; i < this.y; i++) {
            var rowTiles = [];
            var row = $("<tr></tr>");
            tBody.append(row);
            for (var j = 0; j < this.x; j++) {
                var column = $("<td></td>");
                row.append(column);
                rowTiles.push(new tile_1.Tile(column));
            }
            this.board.push(rowTiles);
        }
        var body = $("<body></body>");
        tableElement.append(body);
        //let button = $("")
        //body.append
        this.update();
    };
    GameBoard.prototype.loadState = function () {
        var data = JSON.parse(localStorage.getItem("amoeba-table"));
        if (!data)
            return false;
        if (this.x !== data.x || this.y !== data.y) {
            localStorage.removeItem("amoeba-table");
            return false;
        }
        this.initializeBoard(this.tableElement, this.board = []);
        for (var i = 0; i < data.x; i++) {
            for (var j = 0; j < data.y; j++) {
                this.board[i][j].setState(data.tileStates[i][j]);
            }
        }
        this.playerOne = data.playerOne;
        this.playerTwo = data.playerTwo;
        this.currentPlayer =
            (data.current === 'player-one') ? this.playerOne : this.playerTwo;
        this.update();
        return true;
    };
    GameBoard.prototype.saveState = function () {
        localStorage.setItem("amoeba-table", JSON.stringify({
            playerOne: this.playerOne,
            playerTwo: this.playerTwo,
            x: this.x,
            y: this.y,
            tileStates: this.board.map(function (row) { return row.map(function (tile) { return tile.state; }); })
        }));
    };
    GameBoard.prototype.onTileClicked = function (tile) {
        if (tile.state === tile_1.TileState.Empty && this.winner === undefined) {
            if (this.currentPlayer === this.playerOne) {
                tile.setState(tile_1.TileState.X);
                this.currentPlayer = this.playerTwo;
            }
            else if (this.currentPlayer === this.playerTwo) {
                tile.setState(tile_1.TileState.O);
                this.currentPlayer = this.playerOne;
            }
            this.checkWinner();
            this.saveState();
        }
        ++this.steps;
        this.update();
    };
    GameBoard.prototype.checkWinner = function () {
        var _this = this;
        var points = 0;
        for (var _i = 0, _a = [
            function (i, j) { return _this.board[i][j]; },
            function (i, j) { return _this.board[j][i]; }
        ]; _i < _a.length; _i++) {
            var fun = _a[_i];
            for (var i = 0; i < this.x; i++) {
                var state = tile_1.TileState.Empty;
                points = 1;
                for (var j = 0; j < this.y; j++) {
                    var tile = fun(i, j);
                    console.log(i + ", " + j + ", " + tile.state + ", " + state + ", " + points);
                    if (tile.state !== tile_1.TileState.Empty && tile.state == state) {
                        if (++points >= 5) {
                            this.won(tile.state === tile_1.TileState.X ?
                                this.playerOne : this.playerTwo);
                        }
                    }
                    else {
                        points = 1;
                    }
                    state = tile.state;
                }
            }
        }
    };
    GameBoard.prototype.won = function (player) {
        var _this = this;
        alert("Player " + player.id + " won! Congrats, " + player.name + "!");
        player.gamesWon++;
        var continueButton = $(".continue-game");
        continueButton.removeAttr("disabled").click(function () {
            continueButton.attr("disabled", "disabled");
            _this.winner = undefined;
            _this.startGame();
        });
        this.winner = player;
        this.update();
    };
    GameBoard.prototype.registerHandlers = function (board) {
        var _this = this;
        for (var i = 0; i < board.length; i++) {
            var _loop_1 = function (j) {
                var tile = board[i][j];
                tile.element.click(function () { return _this.onTileClicked(tile); });
            };
            for (var j = 0; j < board[i].length; j++) {
                _loop_1(j);
            }
        }
    };
    GameBoard.prototype.update = function () {
        this.updatePlayerData($(".player-one-info"), this.playerOne);
        this.updatePlayerData($(".player-two-info"), this.playerTwo);
        var gameOverview = $(".game-overview");
        gameOverview.children(".step-number").remove();
        gameOverview.prepend($("<h4>" + this.steps + "</h4>").addClass("step-number"));
        // gameOverview.children(".restart-current-game").remove();
        // gameOverview.append($("<button>Restart current game </button>")
        //     .addClass("col-xs-2 col-xs-push-3 btn btn-danger restart-current-game")
        //     .append($("<i></i>").addClass("glyphicon glyphicon-refresh")));
        // gameOverview.children(".clear-results").remove();
        // gameOverview.append($("<button>Clear results </button>")
        //     .addClass("col-xs-2 col-xs-push-3 btn btn-danger clear-results")
        //     .append($("<i></i>").addClass("glyphicon glyphicon-trash")));
        // gameOverview.children(".continue-game").remove();
        // gameOverview.append($("<button>Continue game </button>")
        //     .attr("disabled", "disabled")
        //     .addClass("col-xs-2 col-xs-push-3 btn btn-danger continue-game")
        //     .append($("<i></i>").addClass("glyphicon glyphicon-play-circle")));
    };
    GameBoard.prototype.updatePlayerData = function (element, player) {
        var playerData = element;
        playerData.children(".won-rounds").remove();
        playerData.append($("<h3>" + player.gamesWon + " of won rounds" + "</h3>").addClass("won-rounds"));
        playerData.children(".player-name").remove();
        playerData.append($("<b>" + player.name + "</b>").addClass("player-name"));
    };
    return GameBoard;
}());
exports.GameBoard = GameBoard;
//# sourceMappingURL=data:application/json;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoiZ2FtZS1ib2FyZC5qcyIsInNvdXJjZVJvb3QiOiIiLCJzb3VyY2VzIjpbImdhbWUtYm9hcmQudHMiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6Ijs7QUFBQSwwQkFBNEI7QUFDNUIsK0JBQXlDO0FBQ3pDLG1DQUFrQztBQUdsQztJQVNJLG1CQUFtQixZQUFvQjtRQUFwQixpQkFBWSxHQUFaLFlBQVksQ0FBUTtRQVI5QixNQUFDLEdBQUcsRUFBRSxDQUFDO1FBQ1AsTUFBQyxHQUFHLEVBQUUsQ0FBQztRQUVoQixjQUFTLEdBQUcsSUFBSSxlQUFNLENBQUMsWUFBWSxFQUFFLENBQUMsQ0FBQyxDQUFDO1FBQ3hDLGNBQVMsR0FBRyxJQUFJLGVBQU0sQ0FBQyxZQUFZLEVBQUUsQ0FBQyxDQUFDLENBQUM7UUFHeEMsVUFBSyxHQUFHLENBQUMsQ0FBQztRQUVOLElBQUksQ0FBQyxTQUFTLEVBQUUsQ0FBQztJQUNyQixDQUFDO0lBRUQsNkJBQVMsR0FBVDtRQUNJLEVBQUUsQ0FBQyxDQUFDLENBQUMsSUFBSSxDQUFDLFNBQVMsRUFBRSxDQUFDLENBQUMsQ0FBQztZQUNwQixJQUFJLENBQUMsZUFBZSxDQUFDLElBQUksQ0FBQyxZQUFZLEVBQUUsSUFBSSxDQUFDLEtBQUssR0FBRyxFQUFFLENBQUMsQ0FBQztZQUN6RCxJQUFJLENBQUMsYUFBYTtnQkFDZCxJQUFJLENBQUMsTUFBTSxLQUFLLElBQUksQ0FBQyxTQUFTLEdBQUcsSUFBSSxDQUFDLFNBQVMsR0FBRyxJQUFJLENBQUMsU0FBUyxDQUFDO1FBQ3pFLENBQUM7UUFDRCxJQUFJLENBQUMsZ0JBQWdCLENBQUMsSUFBSSxDQUFDLEtBQUssQ0FBQyxDQUFDO0lBQ3RDLENBQUM7SUFFRCwrQkFBVyxHQUFYO1FBRUksSUFBSSxDQUFDLEtBQUssR0FBRyxDQUFDLENBQUM7UUFDZixHQUFHLENBQUEsQ0FBQyxJQUFJLENBQUMsR0FBRyxDQUFDLEVBQUUsQ0FBQyxHQUFHLElBQUksQ0FBQyxDQUFDLEVBQUUsRUFBRSxDQUFDLEVB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