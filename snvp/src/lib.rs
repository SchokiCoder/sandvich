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

// a error kind that contains a true bool, is critical
// or it would if rust would support this... hmmm find alternative
pub mod parse_error_kind {
	pub type ParseErrorKind = u32;
	
	// every error equal or above is critical
	pub const CRITICAL_THRESHOLD: ParseErrorKind = 1000;
	
	// warnings
	
	// errors
	pub const UNEXPECTED_SYMBOL: ParseErrorKind = 1000;
}

pub struct ParseError {
	kind: parse_error_kind::ParseErrorKind,
	row_begin: usize,
	col_begin: usize,
	row_end: usize,
	col_end: usize,
}

impl ParseError {
	pub fn new(
		kind: parse_error_kind::ParseErrorKind,
		row_begin: usize,
		col_begin: usize,
		row_end: usize,
		col_end: usize)
		-> ParseError
	{
		return ParseError {
			kind,
			row_begin,
			col_begin,
			row_end,
			col_end,
		};
	}
}

pub struct SrcFile {
	name: String,
	//variables: Vec<>,
	errors: Vec<ParseError>,
}

impl SrcFile {
	pub fn new(name: &str) -> SrcFile {
		return SrcFile {
			name: name.to_string(),
			errors: vec![],
		};
	}
}

pub struct Parser {
	files: Vec<SrcFile>,
}

impl Parser {
	pub fn new() -> Parser {
		return Parser {
			files: vec![],
		};
	}
	
	pub fn parse_file(
		&mut self, name: &str, src: &str)
		-> Result<&Vec<ParseError>, &Vec<ParseError>>
	{
		// register file
		self.files.push(SrcFile::new(name));
		
		// split into lines
		let lines: Vec<&str> = src.split('\n').collect();

		// parse lines		
		let mut criticals = false;
		
		for i in 0..lines.len() {
			// if critical error occured, flag
			if self.parse_line(lines[i], i).is_ok() == false {
				criticals = true;
			}
		}
		
		// return wether or not critical errors occurred
		if criticals {
			return Err(&self.files[self.files.len() - 1].errors);
		}
		else {
			return Ok(&self.files[self.files.len() - 1].errors);
		}
	}

	pub fn parse_line(&mut self, src: &str, row: usize) -> Result<(), ()> {
		let file = self.files.len();
		let mut words = Vec::<&str>::new();
		
		// for every character, collect words (numbers, symbols, keywords, operators etc)
		let mut begin: usize = 0;
		let mut cur_is_word: bool = false;

		let mut i: usize = 0;
		
		while i < src.len() {
			// if currently collecting word, look for end
			if cur_is_word {
				match src.chars().nth(i).unwrap() {
					'0' | '1' | '2' | '3' | '4' |
					'5' | '6' | '7' | '8' | '9' => (),
					
					'+' | '-' | '*' | '/' => {
						words.push(&src[begin..i]);
						cur_is_word = false;
						continue
					},
					
					' ' | '\t' => {
						words.push(&src[begin..i]);
						cur_is_word = false;
					},
					
					_ => {
						// unexpected symbol, error
						let err_kind = parse_error_kind::UNEXPECTED_SYMBOL;
						
						self.files[file].errors.push(
							ParseError::new(
								err_kind,
								row,
								i,
								row,
								i,
							),
						);
						
						if err_kind >= parse_error_kind::CRITICAL_THRESHOLD {
							return Err(());
						}
					},
				}
			}
			
			// look for beginning of a word
			else {
				match src.chars().nth(i).unwrap() {
					'0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' => {
						begin = i;
						cur_is_word = true;
					},
					
					'+' | '-' | '*' | '/' => {
						words.push(&src[i..i]);
					},
					
					' ' | '\t' => (),
					
					_ => {
						// unexpected symbol, error
						let err_kind = parse_error_kind::UNEXPECTED_SYMBOL;
						
						self.files[file].errors.push(
							ParseError::new(
								err_kind,
								row,
								i,
								row,
								i,
							),
						);
						
						if err_kind >= parse_error_kind::CRITICAL_THRESHOLD {
							return Err(());
						}
					},
				}
			}
			
			i += 1;
		}
		
		// parse words
		panic!("impl me");
		
		return Ok(());
	}
}
