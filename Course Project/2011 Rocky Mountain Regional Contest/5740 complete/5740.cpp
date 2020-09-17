// Author: Tyler Siwy
// Date: March 6, 2020
// Approach: Fill a vector of our range with 0's. Then index using our
// citizenshipDay to fill in 1's for residence days and 2's for landing days.
// For each vacation trip, add 0's in the appropriate indices This allows us to
// count half days since once we count the array we simply divide by 2. If we
// haven't found the answer, offset the next check by the difference between the
// count and 1095.
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using namespace std::rel_ops;

struct Date {

  int yyyy;
  int mm;
  int dd;

  // no dates before 1753
  static int const BASE_YEAR = 1753;

  // Enumerated type for names of the days of the week
  enum dayName { SUN, MON, TUE, WED, THU, FRI, SAT };

  // Is a date valid
  static bool validDate(int yr, int mon, int day) {
    return yr >= BASE_YEAR && mon >= 1 && mon <= 12 && day > 0 &&
           day <= daysIn(mon, yr);
  }

  bool isValid() const { return validDate(yyyy, mm, dd); }

  // Constructor to create a specific date.  If the date is invalid,
  // the behaviour is undefined
  Date(int yr = 1970, int mon = 1, int day = 1) {
    yyyy = yr;
    mm = mon;
    dd = day;
  }

  // Returns the day of the week for this
  dayName dayOfWeek() const {
    int a = (14 - mm) / 12;
    int y = yyyy - a;
    int m = mm + 12 * a - 2;
    return (dayName)((dd + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7);
  }

  // comparison operators
  bool operator==(const Date &d) const {
    return dd == d.dd && mm == d.mm && yyyy == d.yyyy;
  }

  bool operator<(const Date &d) const {
    return yyyy < d.yyyy || (yyyy == d.yyyy && mm < d.mm) ||
           (yyyy == d.yyyy && mm == d.mm && dd < d.dd);
  }

  // Returns true if yr is a leap year
  static bool leapYear(int y) {
    return (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));
  }

  // number of days in this month
  static int daysIn(int m, int y) {
    switch (m) {
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
    case 2:
      if (leapYear(y)) {
        return 29;
      } else {
        return 28;
      }
    default:
      return 31;
    }
  }

  void addDay(int n = 1) {
    dd += n;
    while (dd > daysIn(mm, yyyy)) {
      dd -= daysIn(mm, yyyy);
      if (++mm > 12) {
        mm = 1;
        yyyy++;
      }
    }

    while (dd < 1) {
      if (--mm < 1) {
        mm = 12;
        yyyy--;
      }
      dd += daysIn(mm, yyyy);
    }
  }

  // add n months to the date: complexity is about n/12 iterations
  void addMonth(int n = 1) {
    mm += n;
    while (mm > 12) {
      mm -= 12;
      yyyy++;
    }

    while (mm < 1) {
      mm += 12;
      yyyy--;
    }

    if (dd > daysIn(mm, yyyy)) {
      dd = daysIn(mm, yyyy);
    }
  }

  // add n years to the date
  void addYear(int n = 1) {
    yyyy += n;
    if (!leapYear(yyyy) && mm == 2 && dd == 29) {
      dd = 28;
    }
  }

  // number of days since 1753/01/01, including the current date
  int dFSt() const {
    int c = 0;
    Date d(BASE_YEAR, 1, 1);
    Date d2(d);

    d2.addYear(1);
    while (d2 < *this) {
      c += leapYear(d.yyyy) ? 366 : 365;
      d = d2;
      d2.addYear(1);
    }

    d2 = d;
    d2.addMonth(1);
    while (d2 < *this) {
      c += daysIn(d.mm, d.yyyy);
      d = d2;
      d2.addMonth(1);
    }
    while (d <= *this) {
      d.addDay();
      c++;
    }
    return c;
  }
};

// Reads a date in yyyy/mm/dd format, assumes date is valid and in the
// right format
istream &operator>>(istream &is, Date &d) {
  char c;
  return is >> d.mm >> c >> d.dd >> c >> d.yyyy;
}

// print date in yyyy/mm/dd format
ostream &operator<<(ostream &os, const Date &d) {
  os << d.mm << '/' << d.dd << '/' << d.yyyy;
  return os;
}
int check(const Date &residenceD, const Date &landDay, Date citizenshipDay,
          vector<pair<Date, Date>> &trips);

int main() {
  Date residenceD;
  while (cin >> residenceD && cin) {
    // Preprocess input
    Date landD;
    cin >> landD;
    int travels;
    cin >> travels;
    vector<pair<Date, Date>> trips;
    for (int i = 0; i < travels; i++) {
      Date d1, d2;
      cin >> d1 >> d2;
      trips.push_back(make_pair(d1, d2));
    }

    Date citizenshipDay = landD;
    // Try best case scenario first
    citizenshipDay.addDay(1095 - (((landD.dFSt() - residenceD.dFSt()) / 2)));
    // Used to offset our day for the next iteration since we know that we will
    // have to increase by at least our difference.
    int daysLeft = 0;
    while (true) {
      daysLeft = check(residenceD, landD, citizenshipDay, trips);
      if (daysLeft <= 0)
        break;
      // Skip ahead to the next possible case by adding the daysLeft
      citizenshipDay.addDay(daysLeft);
    }
    cout << citizenshipDay << endl;
  }
  return 0;
}

int check(const Date &residenceD, const Date &landDay, Date citizenshipDay,
          vector<pair<Date, Date>> &trips) {
  vector<int> days(1460, 0);
  Date startDate = citizenshipDay;
  startDate.addDay(-1460);
  int landingDate = landDay.dFSt() - startDate.dFSt();
  int residenceDate = residenceD.dFSt() - startDate.dFSt();

  // Fill the graph with days at 1 and 2 for residence days and landing days
  for (int i = max(residenceDate, 0); i < days.size(); i++) {
    if (i < landingDate)
      days[i] = 1;
    else
      days[i] = 2;
  }
  // Process trips
  for (auto t : trips) {
    int start = t.first.dFSt() - startDate.dFSt();
    int end = t.second.dFSt() - startDate.dFSt();
    if (start < 0) {
      // If both sides are too small, disregard this case
      if (end < 0)
        continue;
      start = 0;
    }
    if (end >= days.size()) {
      // If both sides are too large, disregard this case
      if (start > days.size())
        continue;
      end = days.size() - 1;
    }
    // Add our zeros for the vacation dates at our valid date locations
    for (int i = start; i <= end; i++)
      days.at(i) = 0;
  }
  int count = 0;
  // Count the values in the int array, divide by 2 to account for half days in
  // the residence period.
  for (unsigned int i = 0; i < days.size(); i++)
    count += days.at(i);
  count /= 2;
  return 1095 - count;
}
