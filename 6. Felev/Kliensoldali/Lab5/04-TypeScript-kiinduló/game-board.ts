import * as $ from "jquery";
import { Tile, TileState } from "./tile";
import { Player } from './player';
import { SaveData } from "./save-data";

export class GameBoard {
    readonly x = 10;
    readonly y = 10;
    board: Tile[][];
    playerOne = new Player('Player one', 1);
    playerTwo = new Player('Player two', 2);
    currentPlayer: Player;
    winner: Player;
    steps = 0;
    constructor(public tableElement: JQuery) {
        this.startGame();
    }

    startGame() {
        if (!this.loadState()) {
            this.initializeBoard(this.tableElement, this.board = []);
            this.currentPlayer =
                this.winner === this.playerOne ? this.playerTwo : this.playerOne;
        }
        this.registerHandlers(this.board);
    }

    restartGame()
    {
        this.steps = 0;
        for(let i = 0; i < this.x; ++i)
        {
            for(let j = 0; j < this.y; ++j)
            {
                this.board[i][j].setState(TileState.Empty);
            }
        }
        this.saveState();
        this.initializeBoard(this.tableElement, this.board = []);
        this.currentPlayer = this.winner === this.playerOne ? this.playerTwo : this.playerOne;
        this.registerHandlers(this.board);
    }

    clearResults()
    {
            this.playerOne.gamesWon = 0;
            this.playerTwo.gamesWon = 0;
    }

    initializeBoard(tableElement: JQuery, board: Tile[][]) {
        //this.restartGame();
        tableElement.children().remove();
        let tBody = $("<tbody></tbody>");
        tableElement.append(tBody);
        console.log(tableElement.children());
        for (let i = 0; i < this.y; i++) {
            var rowTiles: Tile[] = [];
            let row = $("<tr></tr>");
            tBody.append(row);
            for (let j = 0; j < this.x; j++) {
                let column = $("<td></td>");
                row.append(column);
                rowTiles.push(new Tile(column));
            }
            this.board.push(rowTiles);
        }
        let body = $("<body></body>");
        tableElement.append(body);
        //let button = $("")
        //body.append
        this.update();
    }

    loadState() {
        let data = <SaveData>JSON.parse(localStorage.getItem("amoeba-table"));
        if (!data)
            return false;
        if (this.x !== data.x || this.y !== data.y) {
            localStorage.removeItem("amoeba-table");
            return false;
        }
        this.initializeBoard(this.tableElement, this.board = []);
        for (let i = 0; i < data.x; i++) {
            for (let j = 0; j < data.y; j++) {
                this.board[i][j].setState(data.tileStates[i][j]);
            }
        }
        this.playerOne = data.playerOne;
        this.playerTwo = data.playerTwo;
        this.currentPlayer =
            (data.current === 'player-one') ? this.playerOne : this.playerTwo;
        
        this.update();

        return true;
    }

    saveState() {
        localStorage.setItem("amoeba-table", JSON.stringify(<SaveData>{
            playerOne: this.playerOne,
            playerTwo: this.playerTwo,
            x: this.x,
            y: this.y,
            tileStates: this.board.map(row => row.map(tile => tile.state))
        }));
    }

    onTileClicked(tile: Tile) {
        if (tile.state === TileState.Empty && this.winner === undefined) {
            if (this.currentPlayer === this.playerOne) {
                tile.setState(TileState.X);
                this.currentPlayer = this.playerTwo;
            } else if (this.currentPlayer === this.playerTwo) {
                tile.setState(TileState.O);
                this.currentPlayer = this.playerOne;
            }
            this.checkWinner();
            this.saveState();
        }
        ++this.steps;
        this.update();
    }

    checkWinner() {
        var points = 0;
        for (let fun of [
            (i: number, j: number) => this.board[i][j],
            (i: number, j: number) => this.board[j][i]
        ]) {
            for (let i = 0; i < this.x; i++) {
                let state = TileState.Empty;
                points = 1;
                for (let j = 0; j < this.y; j++) {
                    let tile = fun(i, j);
                    console.log(`${i}, ${j}, ${tile.state}, ${state}, ${points}`);
                    if (tile.state !== TileState.Empty && tile.state == state) {
                        if (++points >= 5) {
                            this.won(tile.state === TileState.X ?
                                this.playerOne : this.playerTwo);
                        }
                    } else {
                        points = 1;
                    }
                    state = tile.state;
                }
            }
        }

    }

    won(player: Player) {
        alert("Player " + player.id + " won! Congrats, " + player.name + "!");
        player.gamesWon++;
        var continueButton = $(".continue-game");
        continueButton.removeAttr("disabled").click(() => {
            continueButton.attr("disabled", "disabled");
            this.winner = undefined;
            this.startGame();
        });
        this.winner = player;
        this.update();
    }

    registerHandlers(board: Tile[][]) {
        for (let i = 0; i < board.length; i++) {
            for (let j = 0; j < board[i].length; j++) {
                let tile = board[i][j];
                tile.element.click(() => this.onTileClicked(tile));
            }
        }
    }

    update()
    {
        this.updatePlayerData($(".player-one-info"), this.playerOne);
        this.updatePlayerData($(".player-two-info"), this.playerTwo);

        let gameOverview = $(".game-overview");
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

    }

    updatePlayerData(element: JQuery, player: Player)
    {
        var playerData = element;
        playerData.children(".won-rounds").remove();
        playerData.append($("<h3>" + player.gamesWon + " of won rounds" + "</h3>").addClass("won-rounds"));
        playerData.children(".player-name").remove();
        playerData.append($("<b>" + player.name + "</b>").addClass("player-name"));
    }
}