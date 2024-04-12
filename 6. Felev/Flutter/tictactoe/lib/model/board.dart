import 'player.dart';

import 'coord.dart';
import 'logic.dart';

class Board{

  static const rows = 3;
  static const columns = 3;

  List<Player> board;

  Board(){
    init();
  }

  Player getPlayer(Coord coord){
    return board[coord.x + 3 * coord.y];
  }

  void init(){
    board = List.generate(9, (idx) => Logic.nobody);
  }

  void setPlayer(Coord coord, Player currentPlayer) {
    board[coord.x + 3 * coord.y] = currentPlayer;
  }

  Player evaluate(){

    if(this.getPlayer(Coord(0, 0)) != Logic.nobody && this.getPlayer(Coord(0, 0)) == this.getPlayer(Coord(1, 1)) && this.getPlayer(Coord(0, 0)) == this.getPlayer(Coord(2, 2)))
      return this.getPlayer(Coord(0, 0));

    if(this.getPlayer(Coord(2, 0)) != Logic.nobody && this.getPlayer(Coord(2, 0)) == this.getPlayer(Coord(1, 1)) && this.getPlayer(Coord(2, 0)) == this.getPlayer(Coord(0, 2)))
      return this.getPlayer(Coord(2, 0));

    for(int i = 0; i < 3; ++i){

      if (this.getPlayer(Coord(i, 0)) != Logic.nobody &&
          this.getPlayer(Coord(i, 0)) == this.getPlayer(Coord(i, 1)) &&
          this.getPlayer(Coord(i, 0)) == this.getPlayer(Coord(i, 2)))
        return this.getPlayer(Coord(i, 0));

      if (this.getPlayer(Coord(0, i)) != Logic.nobody &&
          this.getPlayer(Coord(0, i)) == this.getPlayer(Coord(1, i)) &&
          this.getPlayer(Coord(0, i)) == this.getPlayer(Coord(2, i)))
        return this.getPlayer(Coord(0, i));

    }

    if (isFull()) {
      return null;
    }

    return Logic.nobody;
  }

  bool isFull(){
    for (Player val in board)
      if (val == Logic.nobody)
        return false;

    return true;
  }
}