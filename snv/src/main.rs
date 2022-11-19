/*
	The Sandvich programming language
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

use snvp::*;

fn str_get_pos(string: &str, row: usize, col: usize) -> Option<usize> {
	let mut y: usize = 0;
	let mut x: usize = 0;
	let mut i: usize = 0;
	
	for ch in string.chars() {
		x += 1;
		
		if ch == '\n' {
			y += 1;
			x = 0;
		}
		
		if y == row && x == col {
			return Some(i);
		}
		
		i += 1;
	}
	
	return None;
}

fn main() {
	use parse_error_kind::*;
	
	// example code
	let name = "main";
	let code = "1 + 5";
	
	// parse
	let mut parser = Parser::new();
	let parse_ok = parser.parse_file(name, code).is_ok();
	
	// if parse went wrong, print errors
	let mut critical_count: usize = 0;
	
	for err in &parser.files[parser.files.len() - 1].errors {
		let prepend: &str;
		
		if err.kind >= CRITICAL_THRESHOLD {
			prepend = "error";
			critical_count += 1;
		}
		else {
			prepend = "warning";
		}
		
		match err.kind {
			UNEXPECTED_SYMBOL => {
				let a = str_get_pos(code, err.row_begin, err.col_begin).unwrap();
				let b = str_get_pos(code, err.row_end, err.col_end).unwrap();
				let span = code.get(a..b);
				
				if span.is_none() {
					panic!("error outside of file scope");
				}
				
				println!(
					"{}: {}: `{}`",
					prepend,
					"unexpected symbol",
					span.unwrap(),
				);
			},
			
			_ => {
				panic!(
					"unknown parse error, please check the validity of your installation"
				);
			},
		}
	}
	
	// if parse had any errors, print error count for that file
	if parser.files[parser.files.len() - 1].errors.len() > 0 {
		if parse_ok {
			println!(
				"error: `{}` generated {} errors and {} warnings",
				name,
				critical_count,
				(parser.files[parser.files.len() - 1].errors.len() - critical_count),
			);
		}
		else {
			println!(
				"warning: `{}` generated {} warnings",
				name,
				parser.files[parser.files.len() - 1].errors.len(),
			);
		}
	}
	
	// compile to bytecode
	
	// interpret bytecode
}
