/* PLT Racket extension for selecting "raw" TTY mode */

#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

#define STDIN_FD 0

static int is_raw = 0;
static struct termios saved;

int ttyraw(void)
{
  /* Based on the settings given in http://www.minek.com/files/unix_examples/raw.html */
  struct termios t;

  if (is_raw) return 0;

  if (tcgetattr(STDIN_FD, &saved) < 0) return -1;
  t = saved;

  t.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  t.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  t.c_cflag &= ~(CSIZE | PARENB);
  t.c_cflag |= CS8;
  t.c_oflag &= ~(OPOST);
  t.c_cc[VMIN] = 1;
  t.c_cc[VTIME] = 0;

  if (tcsetattr(STDIN_FD, TCSAFLUSH, &t) < 0) return -1;

  is_raw = 1;
  return 0;
}

int ttyrestore(void)
{
  if (!is_raw) return 0;

  if (tcsetattr(STDIN_FD, TCSAFLUSH, &saved) < 0) return -1;

  is_raw = 0;
  return 0;
}
