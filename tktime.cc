#include <cstdio>
#include <ctime>
#include <iostream>

#include "tktimelib.h"



int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


::tktime::tktime(int _yr, int _mo, int _dy, int _hr, int _mt, int _sc) {  /* Month (1-12), Day (1-31) */
    yr = _yr;
    mo = _mo - 1; /* Stored as 0-11 */
    dy = _dy - 1; /* Stored as 0-30 */
    hr = _hr;
    mt = _mt;
    sc = _sc;
    ::tktime::checkvalues();
  }


::tktime::tktime(int _yr, int _mo, int _dy) { /* Month (1-12), Day (1-31) */
    yr = _yr;
    mo = _mo - 1;
    dy = _dy - 1;
    hr = 0;
    mt = 0;
    sc = 0;
    ::tktime::checkvalues();
  }


::tktime::tktime(struct tm *t) {
    yr = t->tm_year + 1900; /* struct year is since 1900 */
    mo = t->tm_mon; /* struct month is 0-11 */
    dy = t->tm_mday - 1;  /* Stored as 0-30 */
    hr = t->tm_hour;
    mt = t->tm_min;
    sc = t->tm_sec;
    ::tktime::checkvalues();
  }



bool ::tktime::operator==(const tktime& rhs)
{
  return (yr == rhs.yr && mo == rhs.mo && dy == rhs.dy && hr == rhs.hr && mt == rhs.mt && sc == rhs.sc);
}

bool ::tktime::operator!=(const tktime& rhs)
{
  return !(yr == rhs.yr && mo == rhs.mo && dy == rhs.dy && hr == rhs.hr && mt == rhs.mt && sc == rhs.sc);
}

bool ::tktime::operator>(const tktime& rhs)
{
    if (yr != rhs.yr) return yr > rhs.yr;
    if (mo != rhs.mo) return mo > rhs.mo;
    if (dy != rhs.dy) return dy > rhs.dy;
    if (hr != rhs.hr) return hr > rhs.hr;
    if (mt != rhs.mt) return mt > rhs.mt;
    return sc > rhs.sc;
}

bool ::tktime::operator<(const tktime& rhs)
{
    if (yr != rhs.yr) return yr < rhs.yr;
    if (mo != rhs.mo) return mo < rhs.mo;
    if (dy != rhs.dy) return dy < rhs.dy;
    if (hr != rhs.hr) return hr < rhs.hr;
    if (mt != rhs.mt) return mt < rhs.mt;
    return sc < rhs.sc;
}

bool ::tktime::operator>=(const tktime& rhs)
{
    if (yr != rhs.yr) return yr > rhs.yr;
    if (mo != rhs.mo) return mo > rhs.mo;
    if (dy != rhs.dy) return dy > rhs.dy;
    if (hr != rhs.hr) return hr > rhs.hr;
    if (mt != rhs.mt) return mt > rhs.mt;
    return sc >= rhs.sc;
}

bool ::tktime::operator<=(const tktime& rhs)
{
    if (yr != rhs.yr) return yr < rhs.yr;
    if (mo != rhs.mo) return mo < rhs.mo;
    if (dy != rhs.dy) return dy < rhs.dy;
    if (hr != rhs.hr) return hr < rhs.hr;
    if (mt != rhs.mt) return mt < rhs.mt;
    return sc <= rhs.sc;
}





int ::tktime::getYear()
{
  return yr;
}


int ::tktime::getMonth()
{
  return mo+1;
}


int ::tktime::getDay()
{
  return dy+1;
}


int ::tktime::getHour()
{
  return hr;
}


int ::tktime::getMinute()
{
  return mt;
}


int ::tktime::getSecond()
{
  return sc;
}


::std::string tktime::strftime(const char *fmt)
{
  char ptr[64];
  struct tm tmp;
  tmp.tm_year = yr - 1900;
  tmp.tm_mon = mo;
  tmp.tm_mday = dy + 1;
  tmp.tm_hour = hr;
  tmp.tm_min = mt;
  tmp.tm_sec = sc;
  ::std::strftime(ptr, 64, fmt, &tmp);
  return ::std::string(ptr);
}


void ::tktime::printtime() {
  ::std::fprintf(stderr, "%04d-%02d-%02d %02d:%02d:%02d\n", yr, (mo+1), (dy+1), hr, mt, sc);
}


void ::tktime::increment(int s) {
  sc += s;
  ::tktime::checkvalues();
}



void ::tktime::checkvalues() { /* TODO: Write a script (probably python which calls a c++ program) to test that this behaves as expected */
  if ((yr / 4) * 4 == yr )
    daysInMonth[1] = 29; /* If is leap year */
  else
    daysInMonth[1] = 28;

  while (sc > 59) /* If too many seconds */
  {
    sc -= 60;
    mt++;
  }

  while (mt > 59) /* If too many minutes */
  {
    mt-=60;
    hr++;
  }

  while (hr > 23) /* If too many hours */
  {
    hr -= 24;
    dy++;
  }

  /* Need to treat year, month and day together */
  while (mo > 11 || dy > daysInMonth[mo] - 1) {
    while (mo > 11) {
      mo -= 12;
      yr++;
      if ((yr / 4) * 4 == yr)
        daysInMonth[1] = 29;
      else
        daysInMonth[1] = 28;
    }
    if (dy>daysInMonth[mo] - 1) {
      dy -= daysInMonth[mo];
      mo++;
    }
  }

  /* Check all the negative values */
  while (sc < 0) { /* If too few seconds */
    sc += 60;
    mt--; }
  while (mt < 0) { /* If too few minutes */
    mt += 60;
    hr--; }
  while (hr < 0) { /* If too few hours */
    hr += 24;
    dy--; }

  /* Need to treat months and days together */
  while (mo < 0 || dy < 0 || dy > daysInMonth[mo]-1) {
    while (mo < 0) {
      mo += 12;
      yr--;
      if ((yr / 4) * 4 == yr)
        daysInMonth[1] = 29;
      else
        daysInMonth[1] = 28;
    }
    if (dy < 0) {
      if (mo == 0) {
        dy += daysInMonth[11];
        mo = 11;
        yr--;
        if ((yr / 4) * 4 == yr)
          daysInMonth[1] = 29;
        else
          daysInMonth[1] = 28;
      } else {
        dy += daysInMonth[mo-1];
        mo--;
      }
    }
    if (dy > daysInMonth[mo]-1) {
      dy -= daysInMonth[mo];
      mo++;
    }
  }
};
