
import 'package:tic_tac_toe/model/logic.dart';
import 'package:tic_tac_toe/model/board.dart';
import 'package:tic_tac_toe/model/coord.dart';
import 'package:tic_tac_toe/model/player.dart';

class Controller {

  void Function(Coord coord) showMove;
  void Function(Player winningPlayer) showEnd;

  Logic _logic;

  Controller(this.showMove, this.showEnd) {
    _logic = Logic();
  }

  void step(Board board){

    Player status = board.evaluate();
    if (status != Logic.nobody) {
      end(status);
      return;
    }

    Coord aiMove = _logic.play(board, Logic.computer);

    board.setPlayer(aiMove, Logic.computer);

    status =  board.evaluate();
    if (status != Logic.nobody)
      end(status);
    
    showMove(aiMove);
  }

  void end(Player winner) {
    showEnd(winner);
  }
}
