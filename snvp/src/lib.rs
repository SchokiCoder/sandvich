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

// a error kind that contains a true bool, is critical
// or it would if rust would support this... hmmm find alternative
pub enum ParseErrorKind {
	UnexpectedSymbol(true),
	//UnexpectedModifier(true),
	//ExpectedModifier(true),
}

pub struct ParseError {
	kind: ParseErrorKind,
	row_begin: u32,
	col_begin: u32,
	row_end: u32,
	col_end: u32,
}

impl ParseError {
	pub fn new(
		kind: ParseErrorKind,
		row_begin: u32,
		col_begin: u32,
		row_end: u32,
		col_end: u32)
		-> ParseError
	{
		return ParseError {
			kind, row_begin, col_begin, row_end, col_end;
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
			errors: vec![];
		};
	}
}

pub struct Parser {
	files: Vec<SrcFiles>,
}

impl Parser {
	pub fn new() -> Parser {
		return Parser {
			files: vec![];
		};
	}
	
	pub fn parse_file(
		&mut self, name: &str, src: &str)
		-> Result<&Vec<ParseError>, &Vec<ParseError>>
	{
		// register file
		self.files.push(SrcFile::new(name));
		
		// parse file
		let lines = src.split('\n').collect();
		
		for line in &lines {
			self.parse_line(line);
		}
	}

	pub fn parse_line(&mut self, src: &str) {
		let words = Vec::<&str>::new();
		
		// for every character, collect words (numbers, symbols, keywords, operators etc)
		let mut begin: usize;
		let mut cur_is_word: bool = false;

		let mut i: usize = 0;
		
		while i < src.len() {
			// if currently collecting word, look for end
			if cur_is_word {
				match src[i] {
					'0' || '1' || '2' || '3' || '4' ||
					'5' || '6' || '7' || '8' || '9' => (),
					
					'+' || '-' || '*' || '/' => {
						words.push(&src[begin..i]);
						cur_is_word = false;
						continue
					},
					
					' ' || '\t' => {
						words.push(&src[begin..i]);
						cur_is_word = false;
					},
				}
			}
			
			// look for beginning of a word
			else {
				match src[i] {
					'0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' => {
						begin = i;
						cur_is_word = true;
					},
					
					'+' || '-' || '*' || '/' => {
						words.push(&src[i..i]);
					},
					
					' ' || '\t' => (),
				}
			}
			
			i++;
		}
		
		// parse words
		impl me;
	}
}
