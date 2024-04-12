"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var game_board_1 = require("./game-board");
var $ = require("jquery");
var board;
$(function () {
    board = new game_board_1.GameBoard($(".game-board-table"));
    var restartButton = $(".restart-current-game");
    restartButton.click(function () {
        board.restartGame();
    });
    var restartButton = $(".clear-results");
    restartButton.click(function () {
        board.restartGame();
        board.clearResults();
    });
    var playerOneName = $(".player-one-info");
    playerOneName.dblclick(function () {
        var input = $("<input></input>");
        var ok = $("<Button>OK</Button>");
        playerOneName.append(input);
        playerOneName.append(ok);
        ok.click(function () {
            board.playerOne.name = (input.val()).toString();
            input.remove();
            ok.remove();
            board.updatePlayerData(playerOneName, board.playerOne);
        });
    });
    var playerTwoName = $(".player-two-info");
    playerTwoName.dblclick(function () {
        var input = $("<input></input>");
        var ok = $("<Button>OK</Button>");
        playerTwoName.append(input);
        playerTwoName.append(ok);
        ok.click(function () {
            board.playerTwo.name = (input.val()).toString();
            input.remove();
            ok.remove();
            playerTwoName.children(".player-name").remove();
            board.updatePlayerData(playerTwoName, board.playerTwo);
        });
    });
});
//# sourceMappingURL=data:application/json;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoibWFpbi5qcyIsInNvdXJjZVJvb3QiOiIiLCJzb3VyY2VzIjpbIm1haW4udHMiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6Ijs7QUFBQSwyQ0FBeUM7QUFDekMsMEJBQTRCO0FBQzVCLElBQUksS0FBZ0IsQ0FBQztBQUNyQixDQUFDLENBQUM7SUFDRSxLQUFLLEdBQUcsSUFBSSxzQkFBUyxDQUFDLENBQUMsQ0FBQyxtQkFBbUIsQ0FBQyxDQUFDLENBQUM7SUFFOUMsSUFBSSxhQUFhLEdBQUcsQ0FBQyxDQUFDLHVCQUF1QixDQUFDLENBQUM7SUFDL0MsYUFBYSxDQUFDLEtBQUssQ0FBQztRQUNoQixLQUFLLENBQUMsV0FBVyxFQUFFLENBQUM7SUFDeEIsQ0FBQyxDQUFDLENBQUM7SUFFSCxJQUFJLGFBQWEsR0FBRyxDQUFDLENBQUMsZ0JBQWdCLENBQUMsQ0FBQztJQUN4QyxhQUFhLENBQUMsS0FBSyxDQUFDO1FBQ2hCLEtBQUssQ0FBQyxXQUFXLEVBQUUsQ0FBQztRQUNwQixLQUFLLENBQUMsWUFBWSxFQUFFLENBQUE7SUFDeEIsQ0FBQyxDQUFDLENBQUM7SUFFSCxJQUFJLGFBQWEsR0FBRyxDQUFDLENBQUMsa0JBQWtCLENBQUMsQ0FBQztJQUMxQyxhQUFhLENBQUMsUUFBUSxDQUFDO1FBQ25CLElBQUksS0FBSyxHQUFHLENBQUMsQ0FBQyxpQkFBaUIsQ0FBQyxDQUFDO1FBQ2pDLElBQUksRUFBRSxHQUFHLENBQUMsQ0FBQyxxQkFBcUIsQ0FBQyxDQUFDO1FBQ2xDLGFBQWEsQ0FBQyxNQUFNLENBQUMsS0FBSyxDQUFDLENBQUM7UUFDNUIsYUFBYSxDQUFDLE1BQU0sQ0FBQyxFQUFFLENBQUMsQ0FBQztRQUN6QixFQUFFLENBQUMsS0FBSyxDQUFDO1lBQ0wsS0FBSyxDQUFDLFNBQVMsQ0FBQyxJQUFJLEdBQUcsQ0FBQyxLQUFLLENBQUMsR0FBRyxFQUFFLENBQUMsQ0FBQyxRQUFRLEVBQUUsQ0FBQztZQUNoRCxLQUFLLENBQUMsTUFBTSxFQUFFLENBQUM7WUFDZixFQUFFLENBQUMsTUFBTSxFQUFFLENBQUM7WUFDWixLQUFLLENBQUMsZ0JBQWdCLENBQUMsYUFBYSxFQUFFLEtBQUssQ0FBQyxTQUFTLENBQUMsQ0FBQztRQUMzRCxDQUFDLENBQUMsQ0FBQztJQUNQLENBQUMsQ0FBQyxDQUFDO0lBR0gsSUFBSSxhQUFhLEdBQUcsQ0FBQyxDQUFDLGtCQUFrQixDQUFDLENBQUM7SUFDMUMsYUFBYSxDQUFDLFFBQVEsQ0FBQztRQUNuQixJQUFJLEtBQUssR0FBRyxDQUFDLENBQUMsaUJBQWlCLENBQUMsQ0FBQztRQUNqQyxJQUFJLEVBQUUsR0FBRyxDQUFDLENBQUMscUJBQXFCLENBQUMsQ0FBQztRQUNsQyxhQUFhLENBQUMsTUFBTSxDQUFDLEtBQUssQ0FBQyxDQUFDO1FBQzVCLGFBQWEsQ0FBQyxNQUFNLENBQUMsRUFBRSxDQUFDLENBQUM7UUFDekIsRUFBRSxDQUFDLEtBQUssQ0FBQztZQUNMLEtBQUssQ0FBQyxTQUFTLENBQUMsSUFBSSxHQUFHLENBQUMsS0FBSyxDQUFDLEdBQUcsRUFBRSxDQUFDLENBQUMsUUFBUSxFQUFFLENBQUM7WUFDaEQsS0FBSyxDQUFDLE1BQU0sRUFBRSxDQUFDO1lBQ2YsRUFBRSxDQUFDLE1BQU0sRUFBRSxDQUFDO1lBQ1osYUFBYSxDQUFDLFFBQVEsQ0FBQyxjQUFjLENBQUMsQ0FBQyxNQUFNLEVBQUUsQ0FBQztZQUNoRCxLQUFLLENBQUMsZ0JBQWdCLENBQUMsYUFBYSxFQUFFLEtBQUssQ0FBQyxTQUFTLENBQUMsQ0FBQztRQUMzRCxDQUFDLENBQUMsQ0FBQztJQUNQLENBQUMsQ0FBQyxDQUFDO0FBQ1AsQ0FBQyxDQUFDLENBQUMifQ==