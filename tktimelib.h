#ifndef tktime_H
#define tktime_H

#include <ctime>
#include <string>

/**
* Library for various time functions
*
* @author  Tom Kane
* @version 1.0
* @since   2016-09-22
*/


/**
* A class for keeping track of times in a useful fashion.
*/
class tktime {
  private:
    int yr, mo, dy, hr, mt, sc;
    void checkvalues();

  public:


    /**
    * Constructor for tktime object, specifying year, month, day, hour, minute, second
    *
    * @param yr Year
    * @param mo Month
    * @param dy Day
    * @param hr Hour
    * @param mt Minute
    * @param sc Second
    */
    tktime(int, int, int, int, int, int);

    /**
    * Constructor for tktime object, specifying year, month, day
    *
    * @param yr Year
    * @param mo Month
    * @param dy Day
    */
    tktime(int, int, int);

    /**
    * Constructor for tktime object, specifying tm struct (ctime)
    *
    * @param tm struct tm
    */
    tktime(struct tm *); /* struct tm */

    /**
    * Get a string representation of the time
    *
    * @param format Format string
    */
    ::std::string strftime(const char *);

    /**
    * Print the time using YYYY-MM-DD HH:mm:ss format
    */
    void printtime();

    /**
    * Increment by some number of seconds (can be negative)
    *
    * @param seconds Number of seconds to increment (can be negative)
    */
    void increment(int);

    /**
    * Return the year
    */
    int getYear();

    /**
    * Return the month
    */
    int getMonth();

    /**
    * Return the day
    */
    int getDay();

    /**
    * Return the hour
    */
    int getHour();
    /**
    * Return the minute
    */
    int getMinute();

    /**
    * Return the second
    */
    int getSecond();


    /*
    * Over ridden operators
    */
    bool operator==(const tktime&);
    bool operator!=(const tktime&);
    bool operator<(const tktime&);
    bool operator>(const tktime&);
    bool operator<=(const tktime&);
    bool operator>=(const tktime&);
};

#endif
