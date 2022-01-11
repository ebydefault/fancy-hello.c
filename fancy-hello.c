/*
 * fancy-hello.c
 *
 * Fancy Hello World, with countdown, spinning bar, and sliding text;
 * hacky and may not be portable;
 * inspired by Michael Parker's "Learning D" (Packt Publishing, 2017);
 *
 * Copyleft 2022 Ellam ByDefault <ellam.bydefault@gmail.com>
 *
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// everyone loves magic, especially numbers :D
#define COUNTDOWN_NUM   9     // 1 digit max,
#define COUNTDOWN_DELAY 1000
#define SPIN_DELAY      100000
#define SLIDETEXT_DELAY 30000

void countdown(unsigned int count, unsigned int delay);
void spin(clock_t duration, unsigned int delay);
void slidetext(char *text, unsigned int delay);

int main(void)
{
  char opening[]   = "Greeting in ...     "; // trailing spaces to compensate countdown digit and spinning bar.
  int  opening_len = strlen(opening);

  printf("\n%s", opening);
  countdown(COUNTDOWN_NUM, COUNTDOWN_DELAY);

  // clear printed text
  for (int i = 0; i < opening_len; i++) printf("%s","\b");  // move cursor to the left margin,
  for (int i = 0; i < opening_len; i++) printf("%s"," ");   // smash all text with spaces,
  for (int i = 0; i < opening_len; i++) printf("%s","\b");  // move cursor again to the left margin.

  slidetext("<<<  Hello, World!  >>>", SLIDETEXT_DELAY);
}

/*** Count down & spinning bar ***/

void countdown(unsigned int count, unsigned int delay)
{
  for (int i = count; i > 0; i--)
  {
    printf("\b\b\b\b%d   ", i); // much compensation for opening text, countdown digit, spinning bar, and spaces between them.
    fflush(stdout);
    spin(delay, SPIN_DELAY); // spin the bar and handle sleep.
  }
}

/*** Spinning bar ***/

void spin(clock_t duration, unsigned int delay)
{
  char propeller[]   = "/-\\|"; // the spinning bar.
  int  propeller_pos = strlen(propeller);
  int  mod_count     = 0;

  duration += clock();
  do
  {
    printf("\b\b%c ", propeller[mod_count % propeller_pos]);  // trailing space to separate propeller from terminal cursor.
    fflush(stdout);
    mod_count++;
    usleep(delay);
  }
  while (clock() < duration);
}

/*** Slide text: right to left ***/

void slidetext(char *text, unsigned int delay)
{
  int len = strlen(text);

  for (int i = 0; i <= len; i++)
  {
    // clear printed text
    for (int j = 0; j < len; j++) printf("%s","\b");  // move cursor to the left margin,
    for (int j = 0; j < len; j++) printf("%s"," ");   // smash all text with spaces,
    for (int j = 0; j < len; j++) printf("%s","\b");  // move cursor again to the left margin.

    for (int j = len - i; j > 0; j--) printf("%s", " ");      // print spaces at left,
    for (int j = 0      ; j < i; j++) printf("%c", text[j]);  // print text chars.

    fflush(stdout);
    usleep(delay);
  }
  puts("\n");
}
