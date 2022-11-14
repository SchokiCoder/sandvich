# Comments

## Syntax

A single line comment is invoked with a single **#**.
A spanning comment is started with **#<**  
and ended with **>#**.

# Values

## Keywords

- true
- false



# Variables

## Keywords

- var (by default mutable, for immutable see **const**)

## Types

### Keywords

- int
- uint
- float
- bool
- str
- arr

### Implementation

The goal is to implement them as **struct**s.  
For **int**, **uint**, **float** and **bool** the class is merely a wrapper around the
data and works as syntactic sugar for some more value exposition like **int.max** which just
gives the biggest possible value for the current type.  
For aforementioned types except **bool** it is also preferred to use the biggest supported
representation.  
For example rather using a double than a actual float for the **float**.  
For **bool** the fastes representation is preferred.  
**int** is always a signed integer and **uint** is always a unsigned integer.


## Constants

### Keywords

- const

### Implementation

A **const** can be declared empty or filled.  
However the first assignement to a **const** will lock it into a readonly state.  
A constant can be overwritten only when the **const**-keyword is used again.



# Functions

## Syntax

First the **fn**, then the function name, then in parantheses the parameters.  
If a return type is wished it comes after **->**.  
A parameter is given by name a **:** and then the type, another parameter is only allowed after a
comma.  
A parameter is allowed to be constant by prepending a **const** before the type. 
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
