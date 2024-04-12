import 'player.dart';
import 'board.dart';
import 'coord.dart';
import 'logic.dart';

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

    if(Logic.alone) {
      Coord nextMove;
      nextMove = _logic.play(board, Logic.computer);

      board.setPlayer(nextMove, Logic.computer);


      status = board.evaluate();
      if (status != Logic.nobody)
        end(status);

      showMove(nextMove);
    }
  }

  void end(Player winner) {
    showEnd(winner);
  }
}
