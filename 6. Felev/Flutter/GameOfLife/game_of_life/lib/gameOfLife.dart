import 'dart:async';

import 'dart:math';

class GameOfLife {
  static const filedsNum = 1000;
  static const columns = 25;
  static const margin = 1;
  var board = List<bool>(filedsNum);
  Timer timer;

  GameOfLife() {
    this.timer = Timer.periodic(Duration(milliseconds: 1000), (timer) {
      this.update();
    });
  }



  void update(){
    if(!paused){
      var newWorld = List<bool>.from(board);
      for (var i = 0; i < filedsNum; i++) {

        var alives = _neighbourFieldCount(i);
        if (alives < 2 || alives > 3)
          newWorld[i] = false;
        else if (board[i] && (alives == 2 || alives == 3))
          newWorld[i] = true;
        else if (!board[i] && alives == 3)
          newWorld[i] = true;
        //else nothing happens
      }
      board = List<bool>.from(newWorld);
      _stateController.add(0);
    }
  }

  final StreamController<double> _stateController = StreamController<double>();
  var paused = true;

  void pauseClick() {
    paused = !paused;
  }

  StreamController<double> get stateController => _stateController;

  void reset() {
    final random = Random();

    for (var i = 0; i < filedsNum; ++i) {
      board[i] = random.nextInt(100) % 2 == 0;
    }
  }

  int _neighbourFieldCount(int idx) {
    int count = 0;

    int row = (idx / 25).toInt();
    int col = (idx % 25);

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {

        int r = row + i;
        int c = col + j;

        if( (r) < 0 ||
            (r) > (filedsNum / columns - 1) ||
            (c) < 0 ||
            (c) > (columns - 1) ||
            !(i != 0 || j != 0))
          continue;


        if (board[r * columns + c])
          count++;
      }
    }

    return count;
  }

}
