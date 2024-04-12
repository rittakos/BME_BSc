import 'package:flutter/material.dart';

import 'field.dart';

class Board extends StatelessWidget {
  final List<bool> _board;
  final Size fieldSize;
  final int _rowSize;

  const Board(this._board, this._rowSize, {Key key, this.fieldSize}) : super(key: key);

  List<Widget> _buildBoard() {
    final fields = List<Widget>();
    var row = 0;
    for (var i = 0; i < _board.length; ++i) {
      if (i != 0 && i  % _rowSize == 0) row++;

      final left = ((i - (row * _rowSize)) * fieldSize.width)+1;
      final top  = (fieldSize.height * row)+1;
      final marginedSize = Size(fieldSize.width-2*1, fieldSize.height-2*1);
      fields.add(
        CustomPaint(
          size: marginedSize,
          painter: Field(
            alive: _board[i],
            x: left,
            y: top,
          ),
        ),
      );
    }
    return fields;
  }

  @override
  Widget build(BuildContext context) {
    return Stack(children: _buildBoard());
  }
}
