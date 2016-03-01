//
// Main.cpp for cipher in /home/bauren_a/Work/Tek1/Maths/102cipher
//
// Made by Arthur
// Login   <bauren_a@epitech.net>
//
// Started on  Sat Nov 28 05:01:30 2015 Arthur
// Last update Sat Nov 28 16:31:29 2015 Arthur
//

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Utils.h"
#include "Matrix.h"

using namespace std;

int GetMinor(double **src, double **dest, int row, int col, int order)
{
  int colCount = 0, rowCount = 0;

  for (int i = 0; i < order; i++)
    {
      if (i != row)
	{
	  colCount = 0;
	  for (int j = 0; j < order; j++)
	    {
	      if (j != col)
		{
		  dest[rowCount][colCount] = src[i][j];
		  colCount++;
		}
	    }
	  rowCount++;
	}
    }
  return 1;
}

double CalcDeterminant(double **mat, int order)
{
  if (order == 1)
    return mat[0][0];
  double det = 0;
  double **minor;
  minor = new double*[order - 1];
  for (int i = 0; i<order - 1; i++)
    minor[i] = new double[order - 1];
  for (int i = 0; i < order; i++)
    {
      GetMinor(mat, minor, 0, i, order);
      det += (i % 2 == 1 ? -1.0 : 1.0) * mat[0][i] * CalcDeterminant(minor, order - 1);
    }
  for (int i = 0; i<order - 1; i++)
    delete[] minor[i];
  delete[] minor;
  return det;
}

bool MatrixInversion(double **A, int order, double **Y)
{
  if (order == 1)
    {
      Y[0][0] = 1.0 / A[0][0];
      return true;
    }
  bool ret = true;
  double det = CalcDeterminant(A, order);
  if (det == 0)
    ret = false;
  det = 1.0 / det;
  double *temp = new double[(order - 1)*(order - 1)];
  double **minor = new double*[order - 1];
  for (int i = 0; i<order - 1; i++)
    minor[i] = temp + (i*(order - 1));

  for (int j = 0; j<order; j++)
    {
      for (int i = 0; i<order; i++)
	{
	  GetMinor(A, minor, j, i, order);
	  Y[i][j] = det*CalcDeterminant(minor, order - 1);
	  if ((i + j) % 2 == 1)
	    Y[i][j] = -Y[i][j];
	}
    }
  delete[] temp;
  delete[] minor;
  return (ret);
}

char *getFirstWord(const char *str)
{
  char *result;
  int i = 0;

  result = (char *)malloc(String::getStrLen(str, ' ') + 1);
  while (str[i] && str[i] != ' ')
    {
      result[i] = str[i];
      i++;
    }
  result[i] = '\0';
  return (result);
}

bool strToDVec(char *str, vector<double> *vec)
{
  int i = 0;
  char *wrd;
  char *tmp = str;
  while (String::getStrLen(tmp) != 0)
    {
      while (tmp[0] == ' ' && tmp[0])
	tmp = &tmp[1];
      wrd = getFirstWord(tmp);
      double t = String::get_nbr(wrd);
      vec->push_back(t);
      tmp = &tmp[String::getStrLen(wrd)];
      free(wrd);
    }
  return (false);
}

int main(int ac, char **av)
{
  if (ac != 4)
    {
      cerr << "{ SYNTAX ERROR } : Please use ./102cipher [message] [key] [flag].\nYou have entered " << ac - 1 << " parametters." << endl;
      exit(84);
    }

  bool decript;
  if (av[3][0] == '0')
    decript = false;
  else if (av[3][0] == '1')
    decript = true;
  else
    {
      cerr << "{ SYNTAX ERROR } : [" << av[3][0] << "] unknown flag." << endl;
      exit(84);
    }
  bool canDecrypt = true;

  Matrix *key;
  Matrix *revKey;
  Matrix *message;
  Matrix *result;

  key = new Matrix(av[2]);
  revKey = new Matrix(key->getWidth(), key->getHeight());
  if (decript)
    {
      std::vector<double> values;
      strToDVec(av[1], &values);
      int vsize = values.size();
      int dw = key->getWidth();
      int dh;
      double tmp = (double)vsize / (double)dw;
      dh = (((tmp - (int)tmp)) == 0.0 ? (int)tmp : (int)(tmp + 1));
      message = new Matrix(dw, dh);
      for (int i = 0; i < vsize; i++)
	message->setValue(i, values.at(i));
    }
  else
    message = new Matrix(av[1], key->getWidth());

  cout << "Key matrix :" << endl;
  if (decript)
    {
      canDecrypt = MatrixInversion(key->getTab(), key->getWidth(), revKey->getTab());
      if (!canDecrypt)
	{
	  cerr << "Error Cann not inverse the key matrix." << endl;
	  exit(84);
	}
      revKey->showMatrix(true);
    }
  else
    key->showMatrix();
  if (decript)
    {
      result = message->mul(revKey);
      cout << "Decrypted message :" << endl;
      result->showMatrixChars();
    }
  else
    {
      result = message->mul(key);
      cout << "Encrypted message :" << endl;
      result->showMatrixLineary();
    }

  delete key;
  delete revKey;
  delete message;
  return (0);
}
