#include <iostream>
#include <exception>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <string>
#include "new.h"
using namespace std;

function<unsigned int(void)> random = []() -> unsigned int
{
  unsigned int num = static_cast<unsigned int>(time(nullptr));
  srand(num);
  num = (num % 987 + 7436 - 89 + rand() * 258 / 7 + num % 45 / 47 * 1963) % 10;
  return num;
};

void Guess::set_num(const unsigned int& number) {num = number;}

unsigned int Guess::get_num() {return num;}

void Guess::hint(const unsigned int& x)
{
  if (x > Guess::get_num()) throw runtime_error("Too high");
  else if (x < Guess::get_num()) throw runtime_error("Too low");
  else cout << "Nice, well done";
}

function<void(const unsigned int&)> hundle = [](const unsigned int& attempt)
{
  if (attempt > 0) throw runtime_error("---------------------\nhave attempts: ");
  cout << "---------------------\nYou attempts: " << attempt << endl;
};

function<void(void)> ban = []() -> void
{
  ofstream outban("Ban.txt");
  outban << "1" << endl;
  for (int i = 60; i >= 0; --i)
  {
    cout << "\rTry again after: " << i << " ";
    Sleep(1000);
  }
  cout << "\n---------------------" << endl;
  outban << "0" << endl;
};

int main()
{
  start:
  ifstream inban("Ban.txt");
  string read_ban;
  bool check_ban;
  while(getline(inban, read_ban))
  check_ban = ((read_ban == "1") ? true : false);
  if (check_ban)
  {
    cout << "Ban!\n";
    ban();
  }
  game.set_num(random());
  int number, attempt = 3;
  attempt:
  cout << "Enter guess number: ";
  cin >> number;
  while(number > 9 || number < 0)
  {
    cerr << "Error!, The guess number >= 0 && <= 9\n";
    cout << "Enter guess number: ";
    cin >> number;
  }
  try
  {
    game.hint(number);
    bool success = true;
    if (success)
    {
      cout << "\ndo you want play again? \n";
      cout << "1 ? Yes, 0 ? No: ";
      cin >> success;
      if (success) goto start;
      const char end[] = "See you soon";
      for (int i = 0; i < 13; ++i)
      {
        cout << end[i];
        Sleep(100);
      }
      return 1;
    }
  } catch(exception& msg) {cerr << "Error!, " << msg.what() << endl;}
  
  try
  {
    hundle(--attempt);
    cout << "The correct guess number: " << game.get_num() << endl;
    ban();
    goto start;
  } catch(exception& msg) {cerr << msg.what() << attempt << endl; goto attempt;}
  return 0;
}