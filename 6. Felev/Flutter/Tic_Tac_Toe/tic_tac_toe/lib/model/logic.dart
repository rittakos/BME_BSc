import 'dart:math';

import 'package:tic_tac_toe/model/board.dart';
import 'package:tic_tac_toe/model/coord.dart';
import 'package:tic_tac_toe/model/player.dart';

class Logic {

  Random random = new Random();

  static Player player = new Player("O");
  static Player computer = new Player("X");
  static Player nobody = new Player("");

  static const int emptyCount = 0;

  Coord play(Board board, Player currentPlayer) {
    return _calculateMove(board, currentPlayer);
  }

  Coord _calculateMove(Board board, Player currentPlayer) {

    int x, y;

    while(!board.isFull())
    {
      x = random.nextInt(3);
      y = random.nextInt(3);
      if(board.getPlayer(Coord(x, y)) == Logic.nobody)
      {
        return Coord(x, y);
      }
    }
    return Coord(-1, -1);
  }

}
