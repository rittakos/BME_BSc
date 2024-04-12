import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:tic_tac_toe/model/logic.dart';
import 'package:tic_tac_toe/model/player.dart';

import 'coord.dart';

class Cell extends StatelessWidget {

  final Coord coord;
  final Function(Coord coord) tap;
  final Player player;


  Cell({this.coord, this.tap, this.player});


  void _handleTap() {
    if (player == Logic.nobody)
      tap(coord);
  }
  
  final BorderSide _line = BorderSide(
      color: Colors.blue,
      width: 2.0,
      style: BorderStyle.solid
  );

  final BorderSide _noLine = BorderSide(
      width: 0.0,
  );

  Border _setBorder() {

    BorderSide left = _noLine;
    BorderSide right = _noLine;
    BorderSide top = _noLine;
    BorderSide bottom = _noLine;

    if(coord.x == 0 || coord.x == 1)
      right = _line;

    if(coord.y == 0 || coord.y == 1)
      bottom = _line;

    return Border(left: left, right: right, bottom: bottom, top: top);
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: _handleTap,
      child: Container(
        decoration: BoxDecoration(
            border: _setBorder()
        ),
        child: Center(
            child: Text(player.symbol, style: TextStyle(fontSize: 50))
        ),
      ),
    );
  }
}