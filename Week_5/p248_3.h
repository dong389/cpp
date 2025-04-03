#ifndef MYTIME_H
#define MYTIME_H

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;

public:
    MyTime() : hours(0), minutes(0), seconds(0) {}
    MyTime(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    // Getter
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }

    // Setter
    void setHours(int h) { hours = h; }
    void setMinutes(int m) { minutes = m; }
    void setSeconds(int s) { seconds = s; }
};

#endif