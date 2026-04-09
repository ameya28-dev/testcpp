#include <stdio.h>

#define ALL_EVENTS \
    X(EVENT_1)     \
    X(EVENT_2)     \
    X(EVENT_3)     \
    X(EVENT_4)

typedef enum _event_ {

#define X(arg) arg,
    ALL_EVENTS
#undef X
} EVENTS;

#define ALL_STATES \
    X(STATE_1)     \
    X(STATE_2)     \
    X(STATE_3)     \
    X(STATE_4)

typedef enum _state_ {

#define X(arg) arg,
    ALL_STATES
#undef X
} STATES;

void print_event_state(EVENTS event, STATES state) {
    switch (event) {
#define X(arg)                   \
    case arg:                    \
        printf("Event = " #arg); \
        break;
        ALL_EVENTS
#undef X
    }

    switch (state) {
#define X(arg)                          \
    case arg:                           \
        printf(", State = " #arg "\n"); \
        break;
        ALL_EVENTS
#undef X
    }
}

int main() {
    print_event_state(EVENT_1, STATE_2);
    print_event_state(EVENT_2, STATE_4);
    print_event_state(EVENT_4, STATE_1);
    print_event_state(EVENT_3, STATE_3);
}
