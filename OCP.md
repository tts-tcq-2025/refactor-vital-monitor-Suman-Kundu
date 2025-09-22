# Switch Case: Usage and Extensibility Issues

## About Switch Case
A `switch` statement is a control flow construct that executes different branches of code based on the value of a variable.

### Advantages
- Easy to read for small, fixed sets of conditions.
- Compiler can optimize into efficient jump tables.
- Useful for enums or constant-based branching.

---

## Issues with Switch Case (Extensibility Concerns)

### 1. Violation of Open/Closed Principle (OCP)
- **OCP**: "Software entities should be open for extension but closed for modification."
- Adding a new `PaymentMode` requires:
  - Updating the enum.
  - Modifying the `switch` statement.
- This forces modification of existing code → risk of introducing bugs.

---

### 2. Scattering of Logic
- Switch statements often appear in multiple places:
  - Example: `checkout`, `refund`, `logging`.
- Adding a new option means updating **all switch cases** → high maintenance.

---

### 3. Code Duplication
- Each case may contain similar boilerplate logic.
- Encourages copy-paste → harder to refactor later.

---

### 4. Harder Testing
- Logic is embedded directly inside cases.
- Unit testing becomes harder as the number of cases grows.

---

### 5. Poor Extensibility
- Domain changes (e.g., new payment methods) require modifying existing switches.
- Contradicts principles of modular and scalable design.

---

### Assignment

[Accept](https://classroom.github.com/a/WS0e5r_g)

