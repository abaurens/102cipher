/*
** Matrix.h for cipher_bonus in /home/bauren_a/Work/Tek1/Maths/102cipher/Bonus
** 
** Made by Arthur
** Login   <bauren_a@epitech.net>
** 
** Started on  Sat Nov 28 04:39:29 2015 Arthur
** Last update Sat Nov 28 04:40:22 2015 Arthur
*/

#ifndef MATRIX_H_
# define MATRIX_H_

class Matrix
{
 private:
  int size;
  int sx;
  int sy;

  double **values;

 public:
  Matrix(const char *str, int w = 0);
  Matrix(int w, int h);
  ~Matrix();

  void showMatrix(bool floating = false);
  void showMatrixLineary();
  void showMatrixChars();
  int getWidth();
  int getHeight();
  int getSize();
  double getValueAt(int x, int y);
  double **getTab();
  void setValue(int x, int y, double value);
  void setValue(int i, double value);

  Matrix *mul(Matrix *mat2);
};

#endif /* !MATRIX_H_ */
