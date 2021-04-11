# Function Targets
Function targets provide a way to customize the behavior of stumpless,
providing your own logic and functionality in situations where the provided
target types don't meet your needs. This isn't limited to writing logs to a
special format though, you could do anything! In this example, we'll use it
to increment a counter for events that meet a certain criteria.

Our example application counts the balls of each color found in a ball pit.
Each ball is logged as it is processed, and at the end a count for all of the
colors is displayed. We'll use a custom function to keep track of them as they
are logged, so that our ball processing logic can focus on whatever it's doing.

First, we need to write our counting function itself. This is pretty
straightforward for us - we grab the ball color from the entry, and increment
the appropriate counter.

```c
int
count_balls( const struct stumpless_target *target,
             const struct stumpless_entry *entry ) {
  const char *color;

  color = stumpless_get_entry_param_value_by_name( entry, "ball", "color" );
  if( strcmp( color, "red" ) ) {
    return ++red_count;
  } else if( strcmp( color, "green" ) ) {
    return ++green_count;
  } else if( strcmp( color, "blue" ) ) {
    return ++blue_count;
  } else {
    return -1;
  }
}
```
