//
// Matrix.cpp for cipher in /home/bauren_a/Work/Tek1/Maths/102cipher
// 
// Made by Arthur
// Login   <bauren_a@epitech.net>
// 
// Started on  Sat Nov 28 05:02:30 2015 Arthur
// Last update Sat Nov 28 16:32:14 2015 Arthur
//

#include "Utils.h"
#include "Matrix.h"
#include <stdio.h>
#include <cmath>

Matrix::Matrix(const char *str, int w)
{
  int len = String::getStrLen(str);
  double tmp;

  if (w == 0)
    {
      tmp = sqrt(len);
      if ((tmp - (int)tmp) == 0)
	this->sx = (int)tmp;
      else
	this->sx = (int)(tmp + 1);
      this->sy = this->sx;
    }
  else
    {
      this->sx = w;
      tmp = (double)len / (double)this->sx;
      if (((tmp - (int)tmp)) == 0)
	this->sy = (int)tmp;
      else
	this->sy = (int)(tmp + 1);
    }
  this->size = this->sx * this->sy;
  this->values = new double*[this->sx];
  for (int i = 0; i < this->sx; i++)
    this->values[i] = new double[this->sy];

  for (int i = 0; i < this->sx; i++)
    for (int j = 0; j < this->sy; j++)
      this->values[i][j] = 0.0;

  for (int i = 0; i < len; i++)
    {
      int x = i % this->sx;
      int y = i / this->sx;
      this->values[x][y] = (double)str[i];
    }
}

Matrix::Matrix(int w, int h)
{
  this->sx = w;
  this->sy = h;
  this->size = this->sx * this->sy;
  this->values = new double*[this->sx];
  for (int i = 0; i < this->sx; i++)
    this->values[i] = new double[this->sy];

  for (int i = 0; i < this->sx; i++)
    for (int j = 0; j < this->sy; j++)
      this->values[i][j] = 0.0;
}

Matrix::~Matrix()
{
  for (int i = 0; i < this->sx; i++)
    delete[] this->values[i];
  delete[] this->values;
}

void Matrix::showMatrix(bool floating)
{
  for (int y = 0; y < this->sy; y++)
    {
      for (int x = 0; x < this->sx; x++)
	{
	  double tmp = this->values[x][y];
	  if (floating)
	    printf("%.3f", tmp);
	  else
	    printf("%d", (int)tmp);
	  if (x + 1 != this->sx)
	    printf("\t");
	}
      printf("\n");
    }
}

void Matrix::showMatrixLineary()
{
  for (int y = 0; y < this->sy; y++)
    {
      for (int x = 0; x < this->sx; x++)
	{
	  double tmp = this->values[x][y];
	  printf("%d", (int)tmp);
	  if (y != this->sy - 1 || x != this->sx - 1)
	    printf(" ");
	}
    }
  printf("\n");
}

void Matrix::showMatrixChars()
{
  for (int y = 0; y < this->sy; y++)
    {
      for (int x = 0; x < this->sx; x++)
	{
	  double tmp = this->values[x][y];
	  if (((int)(tmp * 10) % 10) == 0)
	    printf("%c", (int)tmp);
	  else
	    printf("%c", (int)(tmp + 1));
	}
    }
  printf("\n");
}

int Matrix::getWidth()
{
  return (this->sx);
}

int Matrix::getHeight()
{
  return (this->sy);
}

int Matrix::getSize()
{
  return this->size;
}

double **Matrix::getTab()
{
  return this->values;
}

double Matrix::getValueAt(int x, int y)
{
  return (this->values[x][y]);
}

void Matrix::setValue(int x, int y, double value)
{
  this->values[x][y] = value;
}

void Matrix::setValue(int i, double value)
{
  int x = i % this->sx;
  int y = i / this->sx;
  this->values[x][y] = value;
}

Matrix *Matrix::mul(Matrix *b)
{
  Matrix *a = this;
  if (a->sx != b->sy)
    return (NULL);
  Matrix *result = new Matrix(b->sx, a->sy);
  for (int y = 0; y < this->sy; y++)
    {
      for (int x = 0; x < this->sx; x++)
	{
	  double value = 0;
	  for (int i = 0; i < a->sx; i++)
	    {
	      double va = a->values[i][y];
	      double vb = b->values[x][i];
	      value += (va * vb);
	    }
	  result->values[x][y] = value;
	}
    }
  return (result);
}
