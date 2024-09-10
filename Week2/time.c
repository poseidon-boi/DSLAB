#include <stdio.h>
#include <stdlib.h>

struct time {
    int hour;
    int min;
    int sec;
};

struct time add(struct time time1, struct time time2) {
    struct time sum;
    sum.sec = time1.sec + time2.sec;
    sum.min = time1.min + time2.min + sum.sec / 60;
    sum.sec %= 60;
    sum.hour = (time1.hour + time2.hour + sum.min / 60) % 24;
    sum.min %= 60;
    return sum;
}

struct time difference(struct time time1, struct time time2) {
    struct time diff, big, small;
    int lesser = 0;
    if (time1.hour < time2.hour)
        lesser = 1;
    if (time1.hour == time2.hour && time1.min < time2.min)
        lesser = 1;
    if (time1.hour == time2.hour && time1.min == time2.min && time1.sec < time2.sec)
        lesser = 1;
    if (lesser == 1) {
        big = time2;
        small = time1;
    }
    else {
        big = time1;
        small = time2;
    }
    diff.hour = big.hour - small.hour;
    diff.min = big.min - small.min;
    if (diff.min < 0) {
        diff.hour--;
        diff.min += 60;
    }
    diff.sec = big.sec - small.sec;
    if (diff.sec < 0) {
        diff.min--;
        diff.sec += 60;
    }
    return diff;
}

int main() {
    printf("Enter time 1(HH MM SS): ");
    struct time time1, time2, sum, diff;
    scanf("%d %d %d", &time1.hour, &time1.min, &time1.sec);
    printf("Enter time 2: ");
    scanf("%d %d %d", &time2.hour, &time2.min, &time2.sec);
    sum = add(time1, time2);
    diff = difference(time1, time2);
    printf("Added time: %.2d %.2d %.2d\nSubtracted time: %.2d %.2d %.2d", sum.hour, sum.min, sum.sec, diff.hour, diff.min, diff.sec);
}
