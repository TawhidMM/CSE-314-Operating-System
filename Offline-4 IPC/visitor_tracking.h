#ifndef VISITOR_TRACKING_H
#define VISITOR_TRACKING_H

#include <string> // For standard C++ types like std::string

// Delay Constants
#define VISITOR_DELAY       3
#define STEP_NUM            3
#define STEPS_DELAY         5e5
#define CORRIDOR_DELAY      2
#define GALLERY1_CAPACITY   5
#define CORRIDOR_CAPACITY   2

// ID Constants
#define STANDARD_ID         1000
#define PREMIUM_ID          2000

// Messages
#define ARRIVAL(at)            "has arrived at " #at
#define AT_STEP(step)          "is at step " #step
#define AT_GALLERY(at, num)    "is at " #at " (entered Gallery " #num ")"
#define EXIT_GALLERY(at, num)  "is at " #at " (exiting Gallery " #num ")"
#define ENTER_BOOTH            "is about to enter the photo booth"
#define AT_BOOTH               "is inside the photo booth"
#define LEFT                   "has left the museum"

// Enum for visitor state
typedef enum {
    PREMIUM, 
    STANDARD
} State;

// Visitor class definition
class Visitor {
public:
    int id;       // Visitor ID
    State state;  // Visitor state (PREMIUM or STANDARD)
};

#endif // VISITOR_TRACKING_H
