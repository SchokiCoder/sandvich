# Comments

## Syntax

	# single line comment
	#< multi-
	   line comment
	>#

A single line comment is invoked with a single **#**.  
A spanning comment is started with **#<** and ended with **>#**.

# Values

## Keywords / Formatting

- true (bool)
- false (bool)
- -100 (int)
- 100 (int)
- 1.0 (float)
- 'a' (int)
- "Well, it looks like we arrived." (str)
- [1,2,3] (arr)



# Variables

## Keywords

- var (declare mutable)
- const (declare constant)

## Syntax

	<**var** / **const**> <var_name / CONST_NAME>: <type / value>

**var** or **const** for a mutable or immutable variable respectively.  
A variable name preferebly in all lower case or a constant name preferebly in
all upper case.  
Either way snake case is preferred and will be applied by the sandvich
formatting tool.  
The type can be inferred if a value is given.  
If there is no value, a type is required.

### Constants

A **const** can be declared empty or filled.  
However the first assignement to a **const** will lock it into a readonly
state.  
A constant can be overwritten only when the **const**-keyword is used again
(it gets redeclared).


## Types

### Keywords

- int (32 / 64 bit, built-in pseudo-class)
- uint (32 / 64 bit, built-in pseudo-class)
- float (32 / 64 bit)
- bool (fastest)
- str (built-in class)
- arr (built-in class)
- any (built-in class)

### Implementation

The goal is to implement them as **struct**s.  
For **int**, **uint**, **float** and **bool** the class is merely a wrapper
around the data and works as syntactic sugar for some more value exposition
like **int.max** which just gives the biggest possible value for the current
type.  
For aforementioned types except **bool** it is also preferred to use the biggest
supported representation.  
For example rather using a double than a actual float for the **float**.  
For **bool** the fastes representation is preferred.  
**int** is always a signed integer and **uint** is always a unsigned integer.



# Functions

## Syntax

First the **fn**, then the function name, then in parantheses the parameters.  
If a return type is wished it comes after **->**.  
A parameter is given by name a **:** and then the type, another parameter is
only allowed after a comma.  
A parameter is allowed to be constant by prepending a **const** before the
type.  
Traling commas are allowed.  
After the return type, within curly braces comes the code.

### Example

	fn function_name(param1: const int, param2: const float) -> str {
		# your code
		return "tha_result"
	}

### Keywords

- fn
- return



# Enums



# Structs

## Member access modifiers

### Keywords

- _private_ (default, no keyword exists)
- readonly (only mutable from inside the struct)
- pub
