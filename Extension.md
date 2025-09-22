
# Extend with a feature

Try _any one_ of these extensions on your code.
Mention the extension(s) you select in your `README.md` file.

### Extension 1: Early Warning

Care-givers need _early warnings_ to take action,
in addition to the alarm that you print after the limit is breached.
Introduce a 'warning' level with a tolerance of 1.5% of the upper-limit.

Example: If the body-temperature extremeties are 95 and 102, the warning-tolerance is `1.5% of 102` = `1.53`.
Warnings need to be displayed in these ranges:
- `95` to `95+1.53` Warning: Approaching hypothermia
- `102-1.53` to `102` Warning: Approaching hyperthermia

Same for pulse-rate and SPO2.

### Extension 2: Support a language in addition to English

Our market has expanded to German-speaking countries!
Switch the language of the printed user-messages based on a global variable.

Use [Google translate](https://translate.google.com/?sl=en&tl=de&op=translate)
if you aren't familiar with German.

Keep in mind: We could add more languages in future. Minimize the code-change required.

### Extension 3: Accept input in different units

Some sensors report the temperature in Celcius.
Make provision to express the unit along with the measurement.
Avoid repeating the limits in different units.

## The starting point

Write a failing test. The asserts will specify the data-models (inputs and outputs). Imagine a care-giver and ensure that the asserts reflect their need.

Experience the places where test / code gets more complex. Think of refactoring opportunities.

## Recommended Approach

Treat the problem as a series of data-transformations.
A chain of transformations is suggested below.

- Translate to common units

- Map the breach to the ranges. Keep the code common across parameters and vary the data.
    
    Example: Design a data-structure with a series of numbers representing the boundary of each condition.
    In the example above: 
    - `upto 95`: `HYPO_THERMIA`
    - `95 to 96.53`: `NEAR_HYPO`
    - `96.54 to 100.47`: `NORMAL`
    - `100.48 to 102`: `NEAR_HYPER`
    - `102 and above`: `HYPER_THERMIA`

- Translate the condition to a message in the appropriate language

- Output the resulting message

- Infer overall vitals. Make logical assumptions in case of warning and error combinations.

Each transformation is one function (or more).
Do not mix different transformations in the same function.
Have one function to chain ('compose') these transformation-functions.
