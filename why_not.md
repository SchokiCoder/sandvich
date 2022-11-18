# Significant indentation

It suffers from the tabs vs spaces problem.  
Jumping multiple indentations in one line causes readability problems.



# Integer sizes

Fine grained control over integer sizes is not that necessary in a modern script
language.



# Integer signedness (consideration)

A 64 bit integer has 18_446_744_073_709_551_616 possible combinations.  
That is quite a lot.  
So as soon as the implementation of variable types shows that signedness is
causing too much trouble, i'll be casting it aside.



# C implementation

This was originally a "why no Rust" but there is an update.  
So first, here are some of the cons of C:

 - memory management
 - undefined behavior
 - strings are just painful to work with
 - memory management x2
 - Wextra and Wall are nothing compared to just vanilla rustc
 - macros haunt me since the days of old
 - fun with excessive use of pointers
 - no standardized way of inline assembly

## Rust implementation

I currently shelved my plans to implement the entire project with Rust.  
This is because:

 - C has nicer enums (very important)
 - can reach more platforms than Rust (nice bonus)

### Update

Actually in Rust i could get C-like enums with this:  

	mod number {
		pub type Number = u8;
		pub const ZERO: Number = 0;
		pub const ONE: Number = 1;
		// ...
	}

	fn main() {
		let myno: number::Number = number::ONE;
	}

With this i can do everything that a C-enum can do,  
plus now i can precisely restrict the size of my enum in bytes.  
Also the names are neatly organized in my namespace.

This is all important for the bytecode.  
I would have needed a way of converting integers (read from the bytecode file)
into the Command-enum's values.  
I could do that with a match statement but this would mean i had to MANUALLY
define which value matches what enum-member.  

This

 - highly increases maintenance cost
 - if done wrong at any point introduces bugs, that are probably hard to catch
 - all must also happen at runtime

The above presented mod-method makes my little enum to nothing more that an
integer... just like an enum in C is.  
It is an integer with specially named values.
