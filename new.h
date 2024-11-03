#ifndef NEW_H
#define NEW_H

class Guess 
{
  unsigned int num;
  public:
  void set_num(const unsigned int&);
  void hint(const unsigned int&);
  unsigned int get_num();
} game;

#endif