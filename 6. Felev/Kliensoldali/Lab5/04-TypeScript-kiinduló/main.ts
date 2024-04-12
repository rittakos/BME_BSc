import { GameBoard } from './game-board';
import * as $ from 'jquery';
var board: GameBoard;
$(() => {
    board = new GameBoard($(".game-board-table"));

    var restartButton = $(".restart-current-game");
    restartButton.click(() => {
        board.restartGame();
    });

    var restartButton = $(".clear-results");
    restartButton.click(() => {
        board.restartGame();
        board.clearResults()
    });

    var playerOneName = $(".player-one-info");
    playerOneName.dblclick(() => {
        let input = $("<input></input>");
        let ok = $("<Button>OK</Button>");
        playerOneName.append(input);
        playerOneName.append(ok);
        ok.click(() => {
            board.playerOne.name = (input.val()).toString(); 
            input.remove();
            ok.remove();
            board.updatePlayerData(playerOneName, board.playerOne);
        });
    });


    var playerTwoName = $(".player-two-info");
    playerTwoName.dblclick(() => {
        let input = $("<input></input>");
        let ok = $("<Button>OK</Button>");
        playerTwoName.append(input);
        playerTwoName.append(ok);
        ok.click(() => {
            board.playerTwo.name = (input.val()).toString(); 
            input.remove();
            ok.remove();
            playerTwoName.children(".player-name").remove();
            board.updatePlayerData(playerTwoName, board.playerTwo);
        });
    });
});