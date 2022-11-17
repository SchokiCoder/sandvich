/*
	The Sandvich programming language and all contained packages
	Copyright (C) 2022	Andy Frank Schoknecht

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#[allow(dead_code)]

// interprets a single line
fn interpret(line: &str) -> i64 {
    // split into words
    let words: Vec<&str> = line.split(" ").collect();
    
    // first assignment
    let mut result: i64 = words[0].parse::<i64>().unwrap();
    
    // for each word
    for i in 1..words.len() {
        // if word matches arith op, exec asm
        match words[i] {
            "+" => {
                result += words[i + 1].parse::<i64>().unwrap();
            },
            
            "-" => {
                result -= words[i + 1].parse::<i64>().unwrap();
            },
            
            "*" => {
                result *= words[i + 1].parse::<i64>().unwrap();
            },
            
            "/" => {
                result /= words[i + 1].parse::<i64>().unwrap();
            },
            
            _ => {},
        }
    }

	return result;
}

struct ByteProgram {
    pub vars: Vec<i64>,
    pub seq: Vec<ByteStatement>,
}

impl ByteProgram {
    // compiles a single line to a sequence of bytecode statements
    pub fn compile(line: &str) -> ByteProgram {
        let mut result = ByteProgram {
            vars: vec![],
            seq: vec![],
        };
        
        // split into words
        let words: Vec<&str> = line.split(" ").collect();
        
        // create one variable
        result.vars.push(words[0].parse::<i64>().unwrap());
        
        // for each word
        for i in 1..words.len() {
            // if word matches arith op, add cmd
            match words[i] {
                "+" => {
                    result.seq.push(
                        ByteStatement::new_arith(
                            ByteCommand::Add,
                            0,
                            words[i + 1].parse::<i64>().unwrap()
                        )
                    );
                },
                
                "-" => {
                    result.seq.push(
                        ByteStatement::new_arith(
                            ByteCommand::Sub,
                            0,
                            words[i + 1].parse::<i64>().unwrap()
                        )
                    );
                },
                
                "*" => {
                    result.seq.push(
                        ByteStatement::new_arith(
                            ByteCommand::Mul,
                            0,
                            words[i + 1].parse::<i64>().unwrap()
                        )
                    );
                },
                
                "/" => {
                    result.seq.push(
                        ByteStatement::new_arith(
                            ByteCommand::Div,
                            0,
                            words[i + 1].parse::<i64>().unwrap()
                        )
                    );
                },
                
                _ => {},
            }
        }
        
        return result;
    }
    
    pub fn run(&mut self) {
        // exec every statement
        for stmt in &self.seq {
            match stmt.cmd {
                ByteCommand::Add => {
                    let dest = match stmt.vals[0] {
                        ByteValue::Variable(var) => var,
                        
                        _ => {
                            panic!("tried to use value as variable index");
                        }
                    };
                    
                    let val =  match stmt.vals[1] {
                        ByteValue::Value(val) => val,
                        
                        ByteValue::Variable(var) => self.vars[var],
                    };
                    
                    self.vars[dest] += val;
                },
				
				ByteCommand::Sub => {
                    let dest = match stmt.vals[0] {
                        ByteValue::Variable(var) => var,
                        
                        _ => {
                            panic!("tried to use value as variable index");
                        }
                    };
                    
                    let val =  match stmt.vals[1] {
                        ByteValue::Value(val) => val,
                        
                        ByteValue::Variable(var) => self.vars[var],
                    };
                    
                    self.vars[dest] -= val;
                },
				
				ByteCommand::Mul => {
                    let dest = match stmt.vals[0] {
                        ByteValue::Variable(var) => var,
                        
                        _ => {
                            panic!("tried to use value as variable index");
                        }
                    };
                    
                    let val =  match stmt.vals[1] {
                        ByteValue::Value(val) => val,
                        
                        ByteValue::Variable(var) => self.vars[var],
                    };
                    
                    self.vars[dest] *= val;
                },
				
				ByteCommand::Div => {
                    let dest = match stmt.vals[0] {
                        ByteValue::Variable(var) => var,
                        
                        _ => {
                            panic!("tried to use value as variable index");
                        }
                    };
                    
                    let val =  match stmt.vals[1] {
                        ByteValue::Value(val) => val,
                        
                        ByteValue::Variable(var) => self.vars[var],
                    };
                    
                    self.vars[dest] /= val;
                },
            }
        }
    }
}

struct ByteStatement {
    cmd: ByteCommand,
    vals: Vec<ByteValue>,
}

impl ByteStatement {
    pub fn new_arith(cmd: ByteCommand, var_index: usize, val: i64) -> ByteStatement {
        return ByteStatement {
            cmd: cmd,
            vals: vec![ByteValue::Variable(var_index), ByteValue::Value(val)],
        };
    }
}

enum ByteValue {
    Value(i64),         // straight value
    Variable(usize),    // index into var register
}
















Problem:
I can't have an enum like in c,
where i can cast int to enum and vice versa,
which is what I NEED for saving muh bytes to file!

enum ByteCommand {
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
}

Fix:
Use C or Asm, at least for the part:
-int to enum

Enum to int works flawlessly in rust.
File read and write is also still done by rust!
























fn main() {
	speed::direct_interp();
	speed::bytecode_all();
	speed::bytecode_runonly();
	speed::rust();
}

// SpeedTest 2
mod speed {
	use super::{interpret, ByteProgram};
	
	// If you change the code,
	//   DO ALSO change the manually converted rust code !!!
	const CODE: &'static str = "1 + 2 / 3 * 4 - 5 + 11 * 2 - 4 / 8 - 1";
	
	const RESULT: i64 = 1;
	
	pub fn direct_interp() {
		let begin = std::time::Instant::now();
		
		assert_eq!(interpret(CODE), RESULT);
		
		let elapsed = begin.elapsed().as_nanos();
		println!("{} nanos | direct interp", elapsed);
	}

	pub fn bytecode_all() {
		let begin = std::time::Instant::now();
		
		let mut bytec = ByteProgram::compile(CODE);
		bytec.run();
		assert_eq!(bytec.vars[0], RESULT);
		
		let elapsed = begin.elapsed().as_nanos();
		println!("{} nanos | bytecode (compile, run)", elapsed);
	}

	pub fn bytecode_runonly() {
		let mut bytec = ByteProgram::compile(CODE);
		
		let begin = std::time::Instant::now();
		
		bytec.run();
		assert_eq!(bytec.vars[0], RESULT);
		
		let elapsed = begin.elapsed().as_nanos();
		println!("{} nanos | bytecode (run)", elapsed);
	}

	pub fn rust() {
		let begin = std::time::Instant::now();
		
		let mut result: i64 = 1;
		result += 2;
		result /= 3;
		result *= 4;
		result -= 5;
		result += 11;
		result *= 2;
		result -= 4;
		result /= 8;
		result -= 1;
		assert_eq!(result, RESULT);
		
		let elapsed = begin.elapsed().as_nanos();
		println!("{} nanos | rust", elapsed);
	}
}


/*
// SpeedTest 1

fn speed_direct_interp() {
    let begin = std::time::Instant::now();
    
    interpret("22 + 66");
    interpret("102 - 44");
    interpret("1 + 2 - 3 + 4 * 5 + 6");
    interpret("102 / 12");
    
    let elapsed_interp = begin.elapsed().as_nanos();
    println!("interp took {} nanos", elapsed_interp);
}

fn speed_rust() {
    let begin = std::time::Instant::now();
    
    println!("{}", 22 + 66);
    println!("{}", 102 - 44);
    println!("{}", 1 + 2 - 3 + 4 * 5 + 6);
    println!("{}", 102 / 12);
    
    let elapsed_native = begin.elapsed().as_nanos();
    println!("native took {} nanos", elapsed_native);
}
*/
