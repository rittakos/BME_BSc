import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class Field extends CustomPainter{
  bool alive;

  double x;
  double y;

  Field({this.alive, this.x, this.y});

  final Paint p = Paint();

  @override
  void paint(Canvas canvas, Size size) {
    p.color =  alive ? Colors.blue : Colors.yellow;
    canvas.drawRect(Rect.fromLTWH(x, y, size.width, size.height), p);
  }

  @override
  bool shouldRepaint(CustomPainter oldDelegate) {
    var fieldPainter = (oldDelegate as Field);
    return fieldPainter.alive != this.alive || fieldPainter.x != this.x || fieldPainter.y != this.y;
  }
}